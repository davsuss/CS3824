#ifndef initH
#define initH
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;


#define MAXSEQUENCELENGTH 300

bool isvalidFasta(char filename[]);
void commandParser(char newCommand);
vector<char*>* readFasta(char* filename);
char promptforcommand();

#endif
