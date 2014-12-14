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
This program reads a FASTA file of sequences and the output from a
motif finder program to compute and verify the log likelihood reported.
"""

import argparse
import logging
import math
import re
import sys

"""
EvaluateLogLikelihood does the work of reading the reported log likelihood
and reporting whether it matches the computed log likelihood.
"""
def EvaluateLogLikelihood(FASTAfile,k,d):
    S = ReadFASTA(FASTAfile)
    # Accumulate and log basic statistics
    count = {nucleotide:0.0 for nucleotide in ["A","C","G","T"]}
    for sequence in S:
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
    # Read and parse standard input
    line = sys.stdin.readline()
    re_match = re.match(r"Best motif of length (\d+) with (\d+) "
                        + "don't cares is ([ACGT*]+)",
                        line)
    if re_match is None:
        raise ValueError("Standard input has incorrectly formatted line\n"
                         + line)
    (reported_k,reported_d,reported_motif) = re_match.group(1,2,3)
    reported_k = int(reported_k)
    reported_d = int(reported_d)
    logging.info("Reported k is " + str(reported_k))
    logging.info("Reported d is " + str(reported_d))
    logging.info("Reported motif is " + reported_motif)
    line = sys.stdin.readline()
    re_match = re.match(r"Log likelihood is (.+)",line)
    if re_match is None:
        raise ValueError("Standard input has incorrectly formatted line\n"
                         + line)
    reported_log_likelihood = float(re_match.group(1))
    line = sys.stdin.readline()
    re_match = re.match(r"Loci of the best motif are here:",line)
    if re_match is None:
        raise ValueError("Standard input has incorrectly formatted line\n"
                         + line)
    reported_loci = []
    for line in sys.stdin:
        line = line.rstrip()
        reported_locus = int(line)
        logging.info("Reported locus is " + str(reported_locus))
        reported_loci.append(reported_locus-1)
    # For the reported loci, find the best motif and log likelihood
    loci = reported_loci
    (motif,profile) = ProfileMotif(S,loci,k,d)
    log_likelihood = LogLikelihood(S,
                                    loci,
                                    motif,
                                    profile,
                                    probability)
    if reported_motif == motif:
        print("Reported motif {0} matches computed motif".format(motif))
    else:
        print("Reported motif {0} does not match computed motif {1}".format(
            reported_motif,motif))
    if abs(reported_log_likelihood-log_likelihood) < 0.0001:
        print("Reported log likelihood {0} matches\n".format(
            reported_log_likelihood) +
              "\tcomputed log likelihood {0}".format(log_likelihood))
    else:
        print("Reported log likelihood {0} does not match\n".format(
            reported_log_likelihood) +
              "\tcomputed log likelihood {0}".format(log_likelihood))
    return (motif,loci,log_likelihood)

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
    return (motif,profile)

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

"""
Read a FASTA file and return the sequences as a list.
"""
def ReadFASTA(FASTAfile):
    header = ""         # A header line starts with ">"
    sequence = ""       # Accumulated sequence is initially empty
    list_of_sequences = list()  # Initial empty list of sequences
    for line in open(FASTAfile):
        line = line.rstrip()    # Eliminate new line and trailing white space
        if len(line) == 0:      # Ignore blank lines
            continue
        elif line[0] == ">":    # Process a header line
            if header:
                if sequence:
                    list_of_sequences.append(sequence)
                else:
                    raise ValueError("FASTA header without sequence\n" +
                           header)
            header = line
            logging.info("header line found:\n\t" + header)
            sequence = ""
        elif re.match(r"^[ACGT]*$",line):    # Process a sequence line
            if not header:
                raise ValueError("FASTA sequence without header\n" + line)
            sequence += line
        else:                   # Line not valid FASTA format
            raise ValueError("Unrecognized FASTA format line\n" + line)
    if sequence:
        list_of_sequences.append(sequence)
    else:
        raise ValueError("FASTA file does not end with sequence")
    return list_of_sequences

def main():
    """
    The main program.
    Uses argparse to parse the command line arguments.
    Uses logging to record progress.
    Then call EvaluateLogLikelihood to evaluate the motif and log likelihood
    reported in standard input.
    """

    # Set up basic logging
    logging.basicConfig(filename="EvaluateLogLikelihood.log",filemode="w",
        level=logging.INFO,format="%(levelname)s: %(asctime)s: %(message)s")
    logging.info("Starting EvaluateLogLikelihood")

    # Process command line arguments
    argparser = argparse.ArgumentParser(
        description="Evaluate reported log likelihood from standard input.")
    argparser.add_argument("FASTAfile",type=str,help="Input FASTA file")
    argparser.add_argument("-k",dest="k",type=int,default=6,
        help="Motif length")
    argparser.add_argument("-d",dest="d",type=int,default=0,
        help="Number of don't cares")
    args = argparser.parse_args()
    logging.info("Arguments sucessfully parsed")
    FASTAfile = args.FASTAfile
    logging.info("Input FASTA file is " + FASTAfile)
    k = args.k
    logging.info("Motif length is " + str(k))
    if k <= 1:
        raise ValueError("k must be at least 2")
    d = args.d
    logging.info("Number of don't cares is " + str(d))
    if d < 0 or d > k-2:
        raise ValueError("d must be between 0 and k-2")

    # Evaluate the log likelihood of the motif in standard input
    (motif,loci,log_likelihood) = EvaluateLogLikelihood(FASTAfile,k,d)

    # Print results to standard output
    print("Best motif of length {0} with {1} don't cares is {2}".format(
        k,d,motif))
    print("Log likelihood is {0}".format(log_likelihood))
    print("Loci of the best motif are here:")
    for locus in loci:
          print(locus+1)
    logging.info("Ending EvaluateLogLikelihood")

if __name__ == "__main__":
    main()
