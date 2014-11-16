#include "Helper.h"
#include <math.h>


vector<int>* randomLociCalc(vector<string>* sequences,int k) {
	vector<int> * results = new vector<int>();

	for (int i = 0; i < sequences->size(); i++)
	{
		results->push_back(rand() % (sequences->at(i).size() - k));
	}
	return results;

}

