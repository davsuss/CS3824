#ifndef ProbabilityH
#define ProbabilityH
#include "Matrix.h"
#include <vector>
#include <ostream>
#include <string.h>

#define A_INDEX 0
#define C_INDEX 1
#define G_INDEX 2
#define T_INDEX 3

class Probability {

private:
    Matrix<double>* matrix;

public:
	Probability();
	void processSequences(std::vector<char*>* sequences);
	double getProbability(char base);
	void print(std::ostream *o);
};


#endif