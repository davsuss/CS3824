#ifndef HELPERH
#define HELPERH

#include "Probability.h"
#include "Profile.h"
#include <string.h> 
#include <unistd.h> 
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdlib.h>

typedef struct __motifResults {
	std::vector<int> * locations;
	char*  motif;
	double log_likelyhood;
    Profile * profile;
} motifResults;

void setDontCares(motifResults * motifData, int d);

void startTimer(int seconds);
void printResults(int k, int d, motifResults* results);

double calculateLogLikelyhood(int numberOfSequences,Probability prob,Profile prof, char* motif);
motifResults* randomMotifFinder(std::vector<char*>* sequences,int k, int d);
std::vector<int>* randomLociCalc(std::vector<char*>* sequences,int k);
motifResults*  grabMotif(Probability * prob, std::vector<int>* locations, std::vector<char*>* sequences, int k, int d);
#endif