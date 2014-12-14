#!/usr/bin/env python3
# Copyright (c) 2014 Lenwood S. Heath. All rights reserved.
# This program or module is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version. It is provided for educational
# purposes and is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.

"""
This program generates a FASTA file of sequences, each containing an
embedded motif, according to command line arguments.
"""

import argparse
import logging
import math
from random import randrange,random
import sys
from textwrap import wrap

"""
EmbedMotif does the work of generating a list of sequences, embedding a
motif in them, and mutating the resulting sequences.
"""
def EmbedMotif(k,d,n,m,mu,A,C,G,T):
    S = GenerateSequences(n,m,A,C,G,T)
    (S,loci,motif) = InsertMotif(S,k,d,A,C,G,T)
    S = MutateSequences(S,mu,A,C,G,T)
    (profile,actual_motif) = ProfileMotif(S,loci,k,d)
    if motif != actual_motif:
        logging.error("Actual optimal motif " + actual_motif +
                      " differs from generated motif " + motif)
    # Accumulate the actual nucleotide probabilities
    count = {nucleotide:0.0 for nucleotide in ["A","C","G","T"]}
    for sequence in S:
        for nucleotide in sequence:
            count[nucleotide] += 1.0
    total = 0.0
    for nucleotide in ["A","C","G","T"]:
        total += count[nucleotide]
    probability = {x:count[x]/total for x in ["A","C","G","T"]}
    log_likelihood = LogLikelihood(S,loci,motif,profile,probability)
    return S

"""
The basic job of GenerateSequences is to generate a list of sequences of
the appropriate length, with each sequence having length in a range from
0.75*m to 1.25*m and with appropriate nucleotide frequences.
"""
def GenerateSequences(n,m,A,C,G,T):
    # Define lower and upper bounds of range for sequence length
    lower = math.ceil(0.75 * m)
    upper = math.floor(1.25 * m)
    S = []
    for i in range(n):
        my_length = randrange(lower,upper)
        sequence = ""
        for j in range(my_length):
            sequence += RandomNucleotide(A,C,G,T)
        S.append(sequence)
    return S

"""
The job of InsertMotif is to create an appropriate random motif and
to insert it at a random location in each sequence in a list of sequences.
"""
def InsertMotif(S,k,d,A,C,G,T):
    # First generate motif of length k
    motif = ""
    for i in range(k):
        motif += RandomNucleotide(A,C,G,T)
    # Now insert d don't cares
    j = d
    while j > 0:
        i = randrange(1,k-1)    # Do not put a * at either end of motif
        if motif[i] != "*":
            j -= 1
            motif = motif[0:i] + "*" + motif[i+1:k]
    logging.info("Chosen motif is " + motif)
    # Finally, insert motif at a random location in each sequence
    S_prime = []
    loci = list()
    for sequence in S:
        my_length = len(sequence)
        lower = 0
        upper = my_length - k + 1
        my_position = randrange(lower,upper)
        logging.info("Position of motif: " + str(my_position+1))
        loci.append(my_position)
        for i in range(k):
            if motif[i] != "*":
                sequence = (sequence[0:my_position+i] + motif[i] +
                        sequence[my_position+i+1:my_length])
        S_prime.append(sequence)
    return (S_prime,loci,motif)

"""
Start with a list of sequences and mutate a random selection of
nucleotides in those sequences.
"""
def MutateSequences(S,mu,A,C,G,T):
    S_prime = []
    number_mutations = 0
    for sequence in S:
        my_length = len(sequence)
        mutated_sequence = ""
        for my_nucleotide in sequence:
            if random() < mu:
                new_nucleotide = RandomNucleotide(A,C,G,T)
                while new_nucleotide == my_nucleotide:
                    new_nucleotide = RandomNucleotide(A,C,G,T)
                mutated_sequence += new_nucleotide
                number_mutations += 1
            else:
                mutated_sequence += my_nucleotide
        S_prime.append(mutated_sequence)
    logging.info("Total number of mutations is " + str(number_mutations))
    return S_prime

"""
Generate a random nucleotide according to a probability distribution.
"""
def RandomNucleotide(A,C,G,T):
    my_random = random()
    if my_random < A:
        return "A"
    elif my_random < A+C:
        return "C"
    elif my_random < A+C+G:
        return "G"
    else:
        return "T"

"""
The job of ProfileMotif is to determine the best motif and the corresponding
profile for given loci in S.
"""
def ProfileMotif(S,loci,k,d):
    # First generate best motif of length k without don't cares
    motif = ""
    # Profile matrix is just count of nucleotides in each position
    # of alignment corresponding to loci.
    profile = {x:{y:0 for y in range(k)} for x in ["A","C","G","T"]}
    for i in range(len(S)):
        substring = S[i][loci[i]:loci[i]+k]
        for j in range(k):
            profile[substring[j]][j] += 1
    # The best nucleotide in each position is the one with the highest
    # count.
    for j in range(k):
        best_nucleotide = "A"
        best_count = profile["A"][j]
        for nucleotide in ["C","G","T"]:
            count = profile[nucleotide][j]
            if count > best_count:
                best_count = count
                best_nucleotide = nucleotide
        motif += best_nucleotide
    # Now find best loci for d don't cares by counts in profile matrix
    best_list = [[profile[motif[j]][j],j,motif[j]] for j in range(k)]
    best_list.sort()   # Primary sort is by profile matrix count
    dont_cares = 0
    i = 0
    while dont_cares < d:
        if best_list[i][1] not in {0,k-1}:
            best_list[i][2] = "*"    # Lowest counts get the don't cares
            dont_cares += 1
        i += 1
    best_list = [[best_list[i][1],best_list[i][2]] for i in range(k)]
    best_list.sort()    # Sort is now by position
    motif_list = [best_list[j][1] for j in range(k)]    # Select nucleotides
                                                        # and don't cares
    motif = "".join(motif_list)
    return (profile,motif)

"""
LogLikelihood computes the log likelihood of the given motif in the given
loci.
"""
def LogLikelihood(S,loci,motif,profile,probability):
    n = len(S)
    log_likelihood = 0.0
    for j in range(len(motif)):
        nucleotide = motif[j]
        if nucleotide == "*":
            continue
        log_likelihood += math.log2((profile[nucleotide][j]/n)/
                                    probability[nucleotide])
    logging.info("Evaluated motif " + motif)
    logging.info("Log likelihood is " + str(log_likelihood))
    return log_likelihood

def main():
    """
    The main program.
    Uses argparse to parse the command line arguments.
    Uses logging to record progress.
    Then call EmbedMotif to generate sequences.
    Finally, send sequences in FASTA format to output file.
    """

    # Set up basic logging
    logging.basicConfig(filename="EmbedMotif.log",filemode="w",
        level=logging.INFO,format="%(levelname)s: %(asctime)s: %(message)s")
    logging.info("Starting EmbedMotif")

    # Process command line arguments
    argparser = argparse.ArgumentParser(
        description="Generate sequences with an embedded motif.")
    argparser.add_argument("FASTAfile",type=str,help="Output FASTA file")
    argparser.add_argument("-k",dest="k",type=int,default=6,
        help="Motif length")
    argparser.add_argument("-d",dest="d",type=int,default=0,
        help="Number of don't cares")
    argparser.add_argument("-n",dest="n",type=int,default=10,
        help="Number of sequences")
    argparser.add_argument("-m",dest="m",type=int,default=250,
        help="Average sequence length")
    argparser.add_argument("--mu",dest="mu",type=float,default=0.20,
        help="Probability of nucleotide mutation")
    argparser.add_argument("-a","-A",dest="A",type=float,default=0.25,
        help="Target probability for amino acid A")
    argparser.add_argument("-c","-C",dest="C",type=float,default=0.25,
        help="Target probability for amino acid C")
    argparser.add_argument("-g","-G",dest="G",type=float,default=0.25,
        help="Target probability for amino acid G")
    args = argparser.parse_args()
    logging.info("Arguments sucessfully parsed")
    FASTAfile = args.FASTAfile
    out_file = open(FASTAfile,mode="w")
    logging.info("Output FASTA file is " + FASTAfile)
    k = args.k
    logging.info("Motif length is " + str(k))
    if k <= 1:
        raise ValueError("k must be at least 2")
    d = args.d
    logging.info("Number of don't cares is " + str(d))
    if d < 0 or d > k-2:
        raise ValueError("d must be between 0 and k-2")
    n = args.n
    logging.info("Number of sequences is " + str(n))
    if n <= 1:
        raise ValueError("n must be at least 2")
    m = args.m
    logging.info("Average sequence length is " + str(m))
    if math.ceil(0.75 * m) < k:
        raise ValueError("k cannot exceed 0.75*m")
    mu = args.mu
    logging.info("Probability of nucleotide mutation is " + str(mu))
    if mu < 0.0:
        raise ValueError("mu must be non-negative")
    A = args.A
    logging.info("Probability of A is " + str(A))
    if A <= 0.0 or A >= 1.0:
        raise ValueError("A must be strictly between 0 and 1")
    C = args.C
    logging.info("Probability of C is " + str(C))
    if C <= 0.0 or C >= 1.0:
        raise ValueError("C must be strictly between 0 and 1")
    G = args.G
    logging.info("Probability of G is " + str(G))
    if G <= 0.0 or G >= 1.0:
        raise ValueError("G must be strictly between 0 and 1")
    T = 1 - (A+C+G)
    logging.info("Probability of T is " + str(T))
    if T <= 0.0:
        raise ValueError("A+C+G must be strictly less than 1")

    # Generate set of sequences with embedded motif
    S = EmbedMotif(k,d,n,m,mu,A,C,G,T)

    # Counting nucleotides generates some basic statistics
    count = {nucleotide:0.0 for nucleotide in ["A","C","G","T"]}
    # Output FASTA file while accumulating statistics
    for i in range(len(S)):
        sequence = S[i]
        print(">Sequence{0} length {1}".format(i+1,len(sequence)),
              file=out_file)
        print("\n".join(wrap(sequence)),file=out_file)
        for nucleotide in sequence:
            count[nucleotide] += 1.0
    total = 0.0
    for nucleotide in ["A","C","G","T"]:
        logging.info("Count of {0}'s is ".format(nucleotide)
                    + str(int(count[nucleotide])))
        total += count[nucleotide]
    logging.info("Total nucleotide count is " + str(int(total)))
    probability = {x:count[x]/total for x in ["A","C","G","T"]}
    for nucleotide in ["A","C","G","T"]:
        logging.info("Probability of {0} is ".format(nucleotide)
                    + str(probability[nucleotide]))

if __name__ == "__main__":
    main()
