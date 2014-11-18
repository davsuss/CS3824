#include "Helper.h"
#include <math.h>
#include <ctime>


vector<int>* randomLociCalc(vector<char*>* sequences,int k) {
	int l = 0;
	vector<int> loci(k);
	for (int i = 0; i < (*sequences).size(); i++)
	{
		srand(time(NULL));
		loci[l] = rand() % (strlen((*sequences)[i]) - k + 1);
	}
	return &loci;
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

motifResults * grabMotif(vector<int>* locations, vector<char*>* sequences, int k, int d) {
    Profile * prof = new Profile(k);
    motifResults * results = (motifResults*) malloc(sizeof(motifResults));
    results->profile = prof;
    int i, size;
    size = sequences->size();
    for (i = 0; i < size; i++) {
        sequences->at(i) = sequences->at(i) + locations->at(i);
    }
    results->profile->processMotifs(sequences);
    char * motif = results->profile->generateMotif();
    motif = setDontCares(results, d);
    return results;
}

char * setDontCares(motifResults * motifData, int d) {
    int i, j, pos;
    char * motif = (char*) malloc(sizeof(strlen(motifData->motif)));
    strcpy(motif, motifData->motif);
    for (i = 0; i < d; i++) {
        pos = -1;
        for (j = 0; j < strlen(motifData->motif); j++) {
            if (motif[j] != '*') {
                if (pos < 0) {
                    pos = j;
                }
                else if (motifData->profile->getHighest(pos) > motifData->profile->getHighest(j)) {
                    pos = j;
                }
            }
        }
        motif[pos] = '*';
    }
    motifData->motif = motif;
    return motif;
}
