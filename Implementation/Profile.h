#include "Matrix.h"
#include <vector>
#include <ostream>
#ifndef PROFILEH
#define PROFILEH
using namespace std;
typedef struct _profChar{
	char base;
	int location;
	int number;
}profChar;


class Profile {
	private:
	Matrix<profChar*>* profile;
	int _motifLength;
	public:
		Profile(int motiflength);
		void processMotifs(vector<char*>* motifs);
        char * generateMotif();
		profChar* getHighest(int location);
		void print(ostream* o);
};

#endif
