#include "Matrix.h"
#include <vector>
#ifndef ProbabilityH
#define ProbabilityH

using namespace std;
class Probability {

private:
	Matrix<double>* matrix;

public:
	Probability();
	void processSequences(vector<char*> sequences);
	double getProbability(char base);

};


#endif