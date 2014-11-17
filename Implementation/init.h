#ifndef initH
#define initH
#include <string>
#include <vector>
using namespace std;


#define MAXSEQUENCELENGTH 100

bool isvalidFasta(char filename[]);
void commandParser(char newCommand);
vector<char*>* readFasta(char* filename);
char promptforcommand();

#endif
