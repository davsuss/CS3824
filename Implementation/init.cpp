#include "init.h"

/* method called by new thread to calculate motif */
void motif_thread_start(int length, int dont_cares, vector<char*>* sequences, int seed) {
	motifResults * results = randomMotifFinder(sequences, length, dont_cares);
	//cout << results->motif << " " << results->log_likelyhood << endl;
	printResults(length, dont_cares, results);
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

