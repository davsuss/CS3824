#ifndef ProbabilityH
#define ProbabilityH
#include "Matrix.h"
#include <vector>
#include <ostream>

// using namespace std;
class Probability {

private:
	Matrix<double>* matrix;
	const int A_INDEX = 0;
	const int C_INDEX = 1;
	const int G_INDEX = 2;
	const int T_INDEX = 3;

public:
	Probability();
	void processSequences(std::vector<char*>* sequences);
	double getProbability(char base);
	void print(std::ostream *o);
};


#endif