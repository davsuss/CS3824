#include "Helper.h"
#include <math.h>


vector<int>* randomLociCalc(vector<string>* sequences,int k) {
	vector<int> * results = new vector<int>();

	for (int i = 0; i < sequences->size(); i++)
	{
		results->push_back(rand() % (sequences->at(i).size() - k));
	}
	return results;

}

double calculateLogLikelyhood(int numberOfSequences,Probability prob,Profile prof, char* motif) {
    double ll = 0;
    int i, prof_val, len;
    double prob_val;
    len = strlen(motif);
    for (i = 0; i < len; i++) {
        if (motif[i] == '*') {
            continue;
        }
        else if (motif[i] == 'A') {
            prof_val = prof.getHighest(i)->number;
            prob_val = prob.getProbability('A');
        }
        else if (motif[i] == 'T') {
            prof_val = prof.getHighest(i)->number;
            prob_val = prob.getProbability('T');
        }
        else if (motif[i] == 'G') {
            prof_val = prof.getHighest(i)->number;
            prob_val = prob.getProbability('G');
        }
        else if (motif[i] == 'C') {
            prof_val = prof.getHighest(i)->number;
            prob_val = prob.getProbability('C');
        }
        else {
            printf("ERROR in calculating loglikelihood\n");
        }
        ll += ((prof_val / numberOfSequences) / prob_val);
    }
    return ll;
}
