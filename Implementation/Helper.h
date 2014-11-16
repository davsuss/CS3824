#include "Probability.h"
#include "Profile.h"
#include <string>
#include <vector>
using namespace std;
#ifndef HELPERH

#define HELPERH

typedef struct __motifResults {
	vector<int> * locations;
	string motif;
	double log_likelyhood;
}motifResults;

double calculateLogLikelyhood(Probability prob,Profile prof, string motif);
motifResults* randomMotifFinder(vector<string>* sequences);
vector<int>* randomLociCalc(vector<string>* sequences,int k);



#endif