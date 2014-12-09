#include "Profile.h"

using namespace std;

Profile::Profile(int motifLength){
	profile = new Matrix<profChar*>(1, motifLength, 0);
	_motifLength = motifLength;
}
void Profile::processMotifs(vector<char*>* motifs){
	int length = motifs->size();
	
	int countA = 0;
	int countG = 0;
	int countT = 0;
	int countC = 0;
	for (int y = 0; y < _motifLength; y++)
	{
		profChar * x = new profChar();
		countA = 0;
		countG = 0;
		countT = 0;
		countC = 0;
		for (int i = 0; i < length; i++)
		{
			switch (motifs->at(i)[y])
			{
				case 'A':
				{
					countA++; break;
				}
				case 'G':
				{
					countG++; break;
				}
				case 'T':
				{
					countT++; break;
				}
				case 'C':
				{
					countC++; break;
				}
			}

		}

		int max = countA;
		x->base = 'A';
		x->location = y;
		x->number = countA;
		if (countG > max)
		{
			max = countG;
			x->base = 'G';
			x->number = countG;
		}
		if (countT > max)
		{
			max = countT;
			x->base = 'T';
			x->number = countT;
		}
		if (countC > max)
		{
			max = countC;
			x->base = 'C';
			x->number = countC;
		}

		profile->set(x, 0, y);

	}
}

char * Profile::generateMotif() {
	int i;
	char * motif = new char[_motifLength + 1];
	motif[_motifLength + 1] = '\0';
	for (i = 0; i < _motifLength; i++) {
		motif[i] = profile->get(0, i)->base;
	}
	motif[_motifLength] = '\0';
	return motif;
}

profChar* Profile::getHighest(int location){
	return profile->get(0, location);
}

void Profile::print(ostream* o)
{
	*o << "Profile" << endl;
	for (int i = 0; i < _motifLength; i++)
	{
		profChar* x = profile->get(0, i);
		*o << x->location << " " << x->base << " " << x->number << endl;
	}
}
