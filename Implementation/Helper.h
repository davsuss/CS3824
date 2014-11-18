#include "Probability.h"
#include "Profile.h"
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#ifndef HELPERH
//#define DEBUG
#define HELPERH

typedef struct __motifResults {
	vector<int> * locations;
	char*  motif;
	double log_likelyhood;
    Profile * profile;
} motifResults;

void setDontCares(motifResults * motifData, int d);

double calculateLogLikelyhood(int numberOfSequences,Probability prob,Profile prof, char* motif);
motifResults* randomMotifFinder(vector<char*>* sequences,int k, int d);
vector<int>* randomLociCalc(vector<char*>* sequences,int k);
motifResults*  grabMotif(Probability * prob, vector<int>* locations, vector<char*>* sequences, int k, int d);
#endif