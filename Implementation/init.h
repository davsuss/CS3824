#ifndef initH
#define initH
#include <string>
#include <vector>
using namespace std;


#define MAXSEQUENCELENGTH 300

bool isvalidFasta(char filename[]);
void commandParser(char newCommand);
vector<char*>* readFasta(char* filename);
char promptforcommand();

#endif
