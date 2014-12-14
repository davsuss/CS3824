#include "init.h"

motifResults * gibbsSampling(motifResults * random_res, int length, int d, vector<char*>* sequences);

/* method called by new thread to calculate motif */
void motif_thread_start(ConcurrentQueue<motifResults*> * queue, int length,
	int dont_cares,	vector<char*>* sequences, int seed)
{
	motifResults* biggest, *results;
	double best_log = 0;
	for (int i = 0; i < 20; i ++) {
		results = randomMotifFinder(sequences, length, dont_cares);
		//cout << results->motif << " " << results->log_likelyhood << endl;
		if (results->log_likelyhood > best_log) {
			best_log = results->log_likelyhood;
			biggest = results;
			// printResults(length, dont_cares, biggest);
		}
		results = gibbsSampling(results, length, dont_cares, sequences);
		if (results) {
			if (results->log_likelyhood > best_log) {
				best_log = results->log_likelyhood;
				biggest = results;
				// printResults(length, dont_cares, biggest);
			}
		}
	}
	printResults(length, dont_cares, biggest);
}

motifResults * gibbsSampling(motifResults * random_res, int length, int d, vector<char*>* sequences) {
	int i, j, old_j;
	vector<int> * locations = random_res->locations;

	motifResults* best_res = random_res;
	bool sample;
	int redo, samples;
	for (i = 0; i < sequences->size(); i++) {
		sample = true;
		redo = samples = 0;
		while(sample) {
			samples++;
			j = (rand() % 100) % (strlen(sequences->at(i)) - length );
			old_j = locations->at(i);
			locations->at(i) = j;
			motifResults *res = findMotifWithLoci(sequences, locations, length, d);
			if (best_res->log_likelyhood < res->log_likelyhood) {
				best_res = res;
			}
			else {
				locations->at(i) = old_j;
				if ((redo > 4) || (samples > (strlen(sequences->at(i)) - length) / 2)) {
					sample = false;
				}
			}
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

