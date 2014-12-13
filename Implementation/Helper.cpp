#include "Helper.h"

using namespace std;

void startTimer(int seconds) {
    sleep(seconds);
    // TODO: pass message to queue to indicate a timeout
    printf("time is up\n");
}

void printResults(int k, int d, motifResults* results) {
    cout << "Best Motif of length " << k << " with " << d << " don't cares is " << results->motif << endl;
    cout << "Log likelyhood is " << results->log_likelyhood << endl;
    cout << "Loci of the best motif are here:" << endl;
    for (int i = 0; i < (int)results->locations->size(); i++){
        cout << results->locations->at(i) << endl;
    }
}

vector<int>* randomLociCalc(vector<char*>* sequences,int k) {
	vector<int>* loci = new  vector<int>(sequences->size());
    
    for (int i = 0; i < (*sequences).size(); i++)
    {
		loci->at(i) = (rand() % 100) % (strlen(sequences->at(i)) - k );
        // srand(1);
	}
	return loci;
}

double calculateLogLikelyhood(int numberOfSequences,Probability* prob,Profile* prof, char* motif) {
    double ll = 0;
    int i, len;
	double prob_val, prof_val;
    len = strlen(motif);
    for (i = 0; i < len; i++) {
        if (motif[i] == '*') {
            continue;
        }
        else if (motif[i] == 'A') {
            prof_val = prof->getHighest(i)->number;
            prob_val = prob->getProbability('A');
        }
        else if (motif[i] == 'T') {
			prof_val = prof->getHighest(i)->number;
			prob_val = prob->getProbability('T');
        }
        else if (motif[i] == 'G') {
			prof_val = prof->getHighest(i)->number;
			prob_val = prob->getProbability('G');
        }
        else if (motif[i] == 'C') {
			prof_val = prof->getHighest(i)->number;
			prob_val = prob->getProbability('C');
        }
        else {
            printf("ERROR in calculating loglikelihood\n");
        }
        ll += log2((prof_val / numberOfSequences) / prob_val);
    }
	
    return ll;
}

motifResults * grabMotif(Probability * prob,vector<int>* locations, vector<char*>* sequences, int k, int d) {
    Profile * prof = new Profile(k);
    motifResults * results = (motifResults*) malloc(sizeof(motifResults));

	results->locations = locations;
	results->log_likelyhood = 0.0;
    results->profile = prof;
    int i, size;
    size = sequences->size();
    for (i = 0; i < size; i++) {
        sequences->at(i) = sequences->at(i) + locations->at(i);

    }

    results->profile->processMotifs(sequences);
    results->motif = results->profile->generateMotif();
 

#ifdef DEBUG
	cout << "Profile:" << endl;
	results->profile->print(&cout);
#endif



#ifdef DEBUG
	cout << "MOTIF BEFORE DONT CARES:" << results->motif << endl;
	cout << results->log_likelyhood;
#endif
	
	
setDontCares(results, d);

#ifdef DEBUG
	cout << "MOTIF AFTER DONT CARES:" << results->motif << endl;
	cout << results->log_likelyhood;
#endif
	results->log_likelyhood = calculateLogLikelyhood(sequences->size(), prob, prof, results->motif);
    
    for (i = 0; i < size; i++) {
        sequences->at(i) = sequences->at(i) - locations->at(i);

    }
	
	return results;
}

void setDontCares(motifResults * motifData, int d) {
    int i, j, pos;
    char * motif = (char*) malloc(sizeof(strlen(motifData->motif))+1);
	strcpy(motif, motifData->motif);
	motif[strlen(motifData->motif) + 1] = '\0';
    for (i = 0; i < d; i++) {
        pos = -1;
        for (j = 1; j < strlen(motifData->motif) - 1; j++) {
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

}

motifResults* randomMotifFinder(vector<char*>* sequences,int k , int d){
	vector<int>* loci = randomLociCalc(sequences, k);
	Probability * prob = new Probability();
	prob->processSequences(sequences);
#ifdef DEBUG
	cout << "PROBABILITY: " << endl;
	prob->print(&cout);
#endif

#ifdef DEBUG
	cout << "LOCI:" << endl;
	for (int i = 0; i < loci->size(); i++){
		cout << "SEQUENCE " << i << ": " << loci->at(i) << endl;
	}
#endif
		motifResults * results = grabMotif(prob, loci, sequences, k, d);
		
	return results;
}