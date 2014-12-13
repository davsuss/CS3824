#include "Helper.h"
#include "init.h"
#include <stdio.h>
#include <ostream>
#include "Helper.h"
#include <thread>

using namespace std;

int main(int argc,char* argv[]) {

	char* fastaFile;
	int dontCares = 0;
	int max_time = 10;
	int length = 0; 
	srand(time(NULL));

	
	for (int i = 1; i < argc; i+=2)
	{
		
		if (i + 1 != argc) {// Check that we haven't finished parsing already
			if (strcmp(argv[i],"-f") == 0) {
				// We know the next argument *should* be the filename:
				fastaFile = argv[i + 1];
			}
			else if (strcmp(argv[i], "-d") == 0) {
				dontCares = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-k") == 0) {
				length = atoi(argv[i + 1]);
			}
			else if (strcmp(argv[i], "-t" ) == 0) {
				max_time = atoi(argv[i + 1]);
			}
			else {
				cout << argv[i];
				std::cout << "Not enough or invalid arguments, please try again.\n";
				exit(0);
			}
		}
	}
	

	#ifdef DEBUG
		cout << "Settings: Time:" << max_time << " Dont Cares: " << max_time << " Length " << length << endl;
	#endif
		vector<char*>* sequences = readFasta(fastaFile);
		if (sequences == NULL)
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
		motifResults* biggest = new motifResults();
		biggest->log_likelyhood = 0;
	
		thread first (startTimer, max_time); // start timer thread
		thread s1 (motif_thread_start, length, dontCares, sequences, time(NULL));
			// motifResults * results = randomMotifFinder(sequences, length, dontCares);
			// //cout << results->motif << " " << results->log_likelyhood << endl;
			// printResults(length, dontCares, results);

   		time_t t1,t2;
    		t1=time(NULL);

                bool continue2 = true;


                while(continue2)
                {
                        t2=time(NULL);
                        int x = t2 - t1;









                        if(x > 5)
                        {
                        continue2 = false;
                        }
                        cout << x << "\n";
                }


		
		first.join();
		s1.join();
		// getchar();
	return 0;

}
