#include "Matrix.h"
#include <vector>

#ifndef PROFILEH
#define PROFILEH
using namespace std;
class Profile {
	private:
	Matrix<int> profile;
	public:
		Profile(int motiflength);
		void processMotifs(vector<string>* motifs, int motifLength);
		int getCount(char nucleotide,int location);
};

#endif