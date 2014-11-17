#include "Matrix.h"
#include <vector>

#ifndef PROFILEH
#define PROFILEH
using namespace std;
typedef struct _profChar{
	char base;
	int location;
	int number;
} profChar;


class Profile {
	private:
	Matrix<int> profile;
	public:
		Profile(int motiflength);
		void processMotifs(vector<char*>* motifs, int motifLength);
		profChar* getHighest(int location);
};

#endif