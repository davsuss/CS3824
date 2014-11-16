#include "Matrix.h"
#include <vector>
#include <ostream>
#ifndef ProbabilityH
#define ProbabilityH

using namespace std;
class Probability {

private:
	Matrix<double>* matrix;
	const int A_INDEX = 0;
	const int C_INDEX = 1;
	const int G_INDEX = 2;
	const int T_INDEX = 3;

public:
	Probability();
	void processSequences(vector<char*>* sequences);
	double getProbability(char base);
	void print(ostream *o);
};


#endif