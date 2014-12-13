#ifndef initH
#define initH
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits.h>
#include "Queue.h"
#include "Helper.h"
using namespace std;


void motif_thread_start(ConcurrentQueue<motifResults*> * queue, int length, int dont_cares, vector<char*>* sequences, int seed);
bool isvalidFasta(char filename[]);
void commandParser(char newCommand);
vector<char*>* readFasta(char* filename);
char promptforcommand();

#endif
