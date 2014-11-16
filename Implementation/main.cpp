#include "Helper.h"
#include "init.h"
#include <iostream>
#include <stdio.h>
#include <ostream>
#include <string.h>
using namespace std;
#define DEBUG

int main(int argc,char* argv[]) {

	char* fastaFile="";
	int dontCares = 0;
	int time = 2;
	int length = 0; 
	Probability prob;
	for (int i = 1; i < argc; i+=2)
	{
		
		if (i + 1 != argc) {// Check that we haven't finished parsing already
			if (strcmp(argv[i],"-f") == 0) {
				// We know the next argument *should* be the filename:
				fastaFile = argv[i + 1];
			}
			else if (strcmp(argv[i], "-d")) {
				dontCares = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-k")) {
				length = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-t")) {
				time = atoi(argv[i + 1]);
			}
			else {
				cout << argv[i];
				std::cout << "Not enough or invalid arguments, please try again.\n";
				exit(0);
			}
		}
	}
	#ifdef DEBUG
		cout << "Settings: Time:" << time << " Dont Cares: " << time << " Length " << length << endl;
	#endif
		vector<char*>* sequences = readFasta(fastaFile);
		if (sequences == nullptr)
		{
			cout << "Failed to open file: " << fastaFile;
			return -1;
		}
	#ifdef DEBUG
		cout << "Sequences: ";
		for (int i = 0; i < sequences->size(); i++)
		{
			cout << sequences->at(i) << endl;
		}
	#endif

		prob.processSequences(sequences);
		
#ifdef DEBUG
		prob.print(&cout);
#endif

		getchar();


	
	





	return 0;

}