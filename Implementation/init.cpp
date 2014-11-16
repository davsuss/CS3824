#include "init.h"
#include <iostream>
#include <fstream>


//bool isvalidFasta(string filename) {
//
//	char fasta[] = ".fasta";
//	int j = 5;
//	for (unsigned int i = filename.length() - 1; i > filename.length() - 6; i--)
//	{
//		if (filename[i] != fasta[j--])
//		{
//			//printf("Error parsing file name: %c does not match %c", &filename[i], fasta[j + 1]);
//			// printf("Error parsing file name (%s): file must end with .fasta", &filename[i], fasta[j + 1]);
//			return false;
//		}
//	}
//	//fastaFile = &filename[0];
//	return true;
//
//
//}
void commandParser(char newCommand)
{
	if (newCommand == 'x')
	{
		exit(9);
	}
	else if (newCommand == 'r')
	{
//		randomMotifFinder();
	}
	else
	{
		printf("Possible commands:\n");
		printf("x: E(x)its the program.\n");
		printf("r: Run the (R)andom Motif Finder with current settings\n");
	}

	//Wait for a new command and send it
	cin.clear();
	cin.ignore(INT_MAX, '\n'); //ignore everything in the buffer up to newline
//	promptForCommand();
}

vector<char*>* readFasta(char* filename)
{
	//create a filestream and open the input file
	ifstream infile;
	infile.open(filename);
	
	vector<char*>* sequences = new vector<char*>();

	if (!infile.good())
	{
		printf("System failed to load file.\n");
		return nullptr;
	}

	//read the file line by line until the end of file
	bool hasHeader = false; //flag for header/sequence error

	while (!infile.eof())
	{
		//read a line of max sequence length
		char buf[MAXSEQUENCELENGTH];
		infile.getline(buf, MAXSEQUENCELENGTH, '\n');
		

		//parse the line, ignore blank spaces, check if its a header	
		if (!buf) //ignore blank lines
		{
			continue;
		}
		if (buf[0] == '>') //if the line is a header
		{
			if (hasHeader)
			{
			//	printf("FASTA read error: two headers with no sequence.\n");
				return nullptr;
			}
			hasHeader = true; //set flag
		}
		else //assume its a sequence
		{
			if (!hasHeader)
			{
			//	printf("FASTA read error: sequence with no header.\n");
				return nullptr;
			}
			hasHeader = false; //reset flag
			sequences->push_back(_strdup(buf)); //any memory issues with strdup are being ignored
		}
	}

	//file parse completed
	//printf("Successful load of file.\n");
	return sequences;
}

void promptForCommand()
{
	printf("Please input a command: ");
//	cin >> command;
	//BcommandParser(command);
}