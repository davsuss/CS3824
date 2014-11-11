//Alexander Ciccone
//CS 3824 Motif Finding Project
//10 November 2014

//This file includes:
//Translation of random motif finder python file (TODO),
//Command line parser,
//toy fasta file parser,
//command line interface with exit (x) command

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Disable warning message 4996: deprecated function
#pragma warning(disable : 4996)

//Forward declaration of functions
bool argIsFasta(char filename[]);
void commandParser(char newCommand);
bool readFasta(char filename[]);
void promptForCommand();
void randomMotifFinder();

//Error message to show how to invoke the program with flags
#define INVOKE "invocation: $ MotifFinder -k 8 -d 3 -t 5 input.fasta > MotifFinder.out"
#define MAX_SEQUENCE_LENGTH 200
#define MAX_SEQUENCES 100

int k;				//the given length of the motif, default to 6
int d;				//the given number of don't cares (*), default to 0
int t;				//the given timeout length in seconds, default to 2
char command;		//the command given from the user
char * fastaFile;	//the FASTA file containing the sequence
char * sequences[MAX_SEQUENCES];	//the sequences that were extracted from the FASTA file
int numSequences;	//the number of sequences given by the FASTA file



/*
* Needs to be able to run on a Linux command line with:
* $ MotifFinder -k 8 -d 3 -t 5 input.fasta > MotifFinder.out
*/
int main(int argc, char * argv[])
{
	//initialize default values
	k = 6;
	d = 0;
	t = 2;
	char sequence[] = "default sequence";

	//echo the command line
	printf("Invoking: MotifFinder");
	for (int i = 1; i < argc; i++)
	{
		printf(" %s", argv[i]);
	}
	printf("\n");

	//require there to be at least the input.fasta argument
	if (argc < 1 || argc > 8)
	{
		printf(INVOKE "\n");
		printf("Too few or too many arguments.\n");
		printf("Please input a command: ");
		cin >> command;
		commandParser(command);
	}
	//else go into the switch that handles arguments
	for (int i = 1; i < argc; i++)
	{
		if ((argv[i])[0] == '-')
		{
			//its a flag, continue
			if ((argv[i])[1] == 'k')
			{
				//set the k, d, or t value, increment i to skip to the next flag
				k = stoi(argv[++i]);
				continue;
			}
			else if ((argv[i])[1] == 'd')
			{
				d = stoi(argv[++i]);
				continue;
			}
			else if ((argv[i])[1] == 't')
			{
				t = stoi(argv[++i]);
				continue;
			}
			else //the flag is not valid
			{
				printf(INVOKE "\n");
				printf("'Flag is invalid': Current character was: %c\n", (argv[i])[0]);
				printf("Please input a command: ");
				cin >> command;
				commandParser(command);
			}
		}
		else if (argIsFasta(argv[i]))
		{
			//parse the fasta file for the sequence
			if (!readFasta(argv[i]))
			{
				printf("Could not load FASTA: %s\n", argv[i]);
				printf("Please input a command: ");
				cin >> command;
				commandParser(command);
			}
			continue;
		}
		else //something went wrong with parsing the command line
		{
			printf(INVOKE "\n");
			printf("'Something else went wrong': Current character was: %c\n", (argv[i])[0]);
			printf("Please input a command: ");
			cin >> command;
			commandParser(command);
		}
	}

	//Output all variables, sequence, etc
	//Prompt for a command
	printf("Motif Length: %d\n", k);
	printf("Don't Cares: %d\n", d);
	printf("Timeout: %d seconds\n", t);
	printf("Fasta file: %s\n", fastaFile);
	for (int i = 0; i < numSequences; i++)
	{
		printf("Sequence %d: %s\n", i+1, sequences[i]);
	}
	printf("Total Number of Sequences: %d\n", numSequences);
	printf("Please input a command: ");
	cin >> command;
	commandParser(command);
	return 0;
}

/*
Checks if the filename given ends in .fasta, TODO: (and is a valid file)
*/
bool argIsFasta(char filename[])
{
	char fasta[] = ".fasta";
	int j = 5;
	for (unsigned int i = strlen(filename) - 1; i > strlen(filename) - 6; i--)
	{
		if (filename[i] != fasta[j--])
		{
			//printf("Error parsing file name: %c does not match %c", &filename[i], fasta[j + 1]);
			printf("Error parsing file name: file must end with .fasta", &filename[i], fasta[j + 1]);
			return false;
		}
	}
	fastaFile = &filename[0];
	return true;
}

/*
Parses command line inputs
*/
void commandParser(char newCommand)
{
	if (newCommand == 'x')
	{
		exit(9);
	}
	else if (newCommand == 'r')
	{
		randomMotifFinder();
	}
	else
	{
		printf("Possible commands:\n");
		printf("x: E(x)its the program.\n");
		printf("r: Run the (R)andom Motif Finder with current settings\n");
	}
	
	//Wait for a new command and send it
	promptForCommand();

}

bool readFasta(char filename[])
{
	//create a filestream and open the input file
	ifstream infile;
	infile.open(filename);
	if (!infile.good())
	{
		printf("System failed to load file.\n");
		return false;
	}


	//read the file line by line until the end of file
	bool hasHeader = false; //flag for header/sequence error
	numSequences = 0; //sequence counter
	while (!infile.eof())
	{
		//read a line of max sequence length
		char buf[MAX_SEQUENCE_LENGTH];
		infile.getline(buf, MAX_SEQUENCE_LENGTH);
		
		char* token; //pointer to store memory address of the line
		
		//parse the line, ignore blank spaces, check if its a header	
		token = strtok(buf, " ");
		if (!token) //ignore blank lines
		{
			continue;
		}
		if (token[0] == '>') //if the line is a header
		{
			if (hasHeader)
			{
				printf("FASTA read error: two headers with no sequence.\n");
				return false;
			}
			hasHeader = true; //set flag
		}
		else //assume its a sequence
		{ 
			if (!hasHeader)
			{
				printf("FASTA read error: sequence with no header.\n");
				return false;
			}
			hasHeader = false; //reset flag
			sequences[numSequences++] = strdup(token); //any memory issues with strdup are being ignored
		}
	}

	//file parse completed
	printf("Successful load of file.\n");
	return true;
}

/*
Waits for a command from the user and sends it to commandParser()
*/
void promptForCommand()
{
	printf("Please input a command: ");
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cin >> command;
	commandParser(command);
}

/*
Finds the best match motif using random loci
*/
void randomMotifFinder()
{
	printf("Random Motif Finder Not Yet Implemented...\n");
}
