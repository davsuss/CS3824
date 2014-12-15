#include "Probability.h"

using namespace std;

Probability::Probability() {
	matrix = new Matrix<double>(4,1,0.0);
}
void Probability::processSequences(vector<char*>* sequences){
	double countA = 0.0;
	double countT = 0.0;
	double countC = 0.0;
	double countG = 0.0;
	
	for (int i = 0; i < sequences->size(); i++)
	{
		int length = (int)strlen(sequences->at(i));
		char * seq = sequences->at(i);
		for (int y = 0; y < length; y++)
		{
			switch (seq[y])
			{
			case 'A':
			{countA++; break;}
			case 'C':
			{countC++; break;}
			case 'G':
			{countG++; break;}
			case 'T':
			{countT++; break;}
			}
		}
	}
	double total = countA + countG + countC + countT;
	matrix->set(countA / total, A_INDEX, 0);
	matrix->set(countG / total, G_INDEX, 0);
	matrix->set(countT / total, T_INDEX, 0);
	matrix->set(countC / total, C_INDEX, 0);

}
double Probability::getProbability(char base) {
	switch (base)
	{
	case 'A':
	{return matrix->get(A_INDEX, 0); }
	case 'C':
	{return matrix->get(C_INDEX, 0); }
	case 'G':
	{return matrix->get(G_INDEX, 0); }
	case 'T':
	{return matrix->get(T_INDEX, 0); }
	}

	return -1;
}
void Probability::print(ostream* o){
	*o << "A PROBABILITY: " << matrix->get(A_INDEX, 0) << endl;
	*o << "G PROBABILITY: " << matrix->get(G_INDEX, 0) << endl;
	*o << "T PROBABILITY: " << matrix->get(T_INDEX, 0) << endl;
	*o << "C PROBABILITY: " << matrix->get(C_INDEX, 0) << endl;
}