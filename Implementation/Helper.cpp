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
        else if (motif[i] == 'a') {
            prof_val = prof.getCount('a', i);
            prob_val = prob.getProbability('a');
        }
        else if (motif[i] == 't') {
            prof_val = prof.getCount('t', i);
            prob_val = prob.getProbability('t');
        }
        else if (motif[i] == 'g') {
            prof_val = prof.getCount('g', i);
            prob_val = prob.getProbability('g');
        }
        else if (motif[i] == 'c') {
            prof_val = prof.getCount('c', i);
            prob_val = prob.getProbability('c');
        }
        else {
            printf("ERROR in calculating loglikelihood\n");
        }
        ll += ((prof_val / numberOfSequences) / prob_val);
    }
    return ll;
}
