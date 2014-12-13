#include "init.h"

motifResults * gibbsSampling(double * best_log, int length, int d, vector<char*>* sequences, vector<int> * locations);

/* method called by new thread to calculate motif */
void motif_thread_start(ConcurrentQueue<motifResults*> * queue, int length, int dont_cares, vector<char*>* sequences, int seed) {
	motifResults* biggest, *results;
	double best_log = 0;
	for (int i = 0; i < 10; i ++) {
		results = randomMotifFinder(sequences, length, dont_cares);
		//cout << results->motif << " " << results->log_likelyhood << endl;
		if (results->log_likelyhood > best_log) {
			best_log = results->log_likelyhood;
			biggest = results;
			printResults(length, dont_cares, biggest);
		}
		results = gibbsSampling(&best_log, length, dont_cares, sequences, results->locations);
		if (results) {
			if (results->log_likelyhood > best_log) {
				best_log = results->log_likelyhood;
				biggest = results;
				printResults(length, dont_cares, biggest);
			}
		}
	}
	queue->queue_mutex.lock();
	printResults(length, dont_cares, biggest);
	// for (int i = 0; i < sequences->size(); i++) {
	// 	for (int j = 0; j < length; j++) {
	// 		printf("%c", sequences->at(i)[(biggest->locations->at(i)) + j]);
	// 	}
	// 	printf("\n");
	// }
	queue->queue_mutex.unlock();
}

motifResults * gibbsSampling(double * best_log, int length, int d, vector<char*>* sequences, vector<int> * locations) {
	int i, j, old_j;

	motifResults* best_res;

	for (i = 0; i < sequences->size(); i++) {
		for (j = 0; j < strlen(sequences->at(i)) - length; j++) {
			// strncpy(lmer, sequences->at(i), length);
			old_j = locations->at(i);
			locations->at(i) = j;
			motifResults *res = findMotifWithLoci(sequences, locations, length, d);
			if (*best_log < res->log_likelyhood) {
				best_res = res;
				*best_log = best_res->log_likelyhood;
				printf("found a new best\n");
			}
			// else {
			// 	locations->at(i) = old_j;
			// 	break;
			// }
		}
	}
	return best_res;
}

vector<char*>* readFasta(char* filename)
{
	//create a filestream and open the input file
	ifstream infile;
	infile.open(filename);
	
	vector<char*>* sequences = new vector<char*>();

	if (!infile.good())
	{
		printf("System failed to load file.\n");
		return NULL;
	}

	//read the file line by line until the end of file
	int length;
	char * sequence;
	while (!infile.eof())
	{
		//read a line of max sequence length
		char buf[1024];
		infile.getline(buf, 1024, '\n');
		

		//parse the line, ignore blank spaces, check if its a header	
		if (!buf) //ignore blank lines
		{
			continue;
		}
		if (buf[0] == '>') //if the line is a header
		{
			if (sequence != NULL) {
				sequences->push_back(sequence); //any memory issues with strdup are being ignored
			}

			sscanf(buf, ">%*s length %i", &length);
			sequence = (char*)malloc(length + 1);
		}
		else //assume its a sequence
		{
			strcat(sequence, buf);
		}
	}
	if (sequence != NULL) {
		sequences->push_back(sequence); //any memory issues with strdup are being ignored
	}

	//file parse completed
	//printf("Successful load of file.\n");
	return sequences;
}

