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

	if ((argc == 2) && (strncmp("sequences_", argv[1], 10)) == 0) {
		sscanf(argv[1], "sequences_k%i_d%i_%*s", &length, &dontCares);
		fastaFile = argv[1];
	}
	else {
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
		// motifResults* biggest = new motifResults();
		// biggest->log_likelyhood = 0;

		ConcurrentQueue * queue = new ConcurrentQueue();
		vector<thread> best_results;
	
		for(int i =0; i < 8; i++){		
		best_results.push_back(thread(motif_thread_start, queue, length, dontCares, sequences, time(NULL)));
		}

   		time_t t1,t2;
    		t1=time(NULL);

                bool continue2 = true;
		cout << "";
		startThreads();
        
	        while(continue2)
                {
                        t2=time(NULL);
                        int x = t2 - t1;


                        if(x > 5)
                        {
  	                      continue2 = false;
                        }
//                        cout << x << "\n";
                }
		stopThreads();

		motifResults* biggest= new motifResults();
		biggest->log_likelyhood = 0;
		for(int i =0; i < best_results.size();i++)
		{
		best_results[i].join();
		
		motifResults * temp = queue->removeItem();

		if(biggest->log_likelyhood < temp->log_likelyhood)
		{
			biggest = temp;
		}
		
		}		
		printResults(length, dontCares,biggest);
		return 0;

}
