#include "Probability.h"
#include "Profile.h"
#include <string.h>
#include <string>
#include <vector>
using namespace std;
#ifndef HELPERH

#define HELPERH

typedef struct __motifResults {
	vector<int> * locations;
	char*  motif;
	double log_likelyhood;
    Profile * profile;
} motifResults;

char * setDontCares(motifResults * motifData, int d);

double calculateLogLikelyhood(int numberOfSequences,Probability prob,Profile prof, char* motif);
motifResults* randomMotifFinder(vector<char*>* sequences);
vector<int>* randomLociCalc(vector<char*>* sequences,int k);
vector<char*>* grabMotif(vector<int>* locations, vector<char*>* sequences, int k, int d);
#endif