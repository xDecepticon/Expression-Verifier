// This is the main file for the program. Naturally, the code starts here.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "binaryTree.h"

using namespace std;

int main(int argc, char *argv[])
{
	// Instantiate stack.
	// std::vector<std::streamoff> callStack;
	binaryTree BSTree;

	// Additional set-up.
	string singleLine = "";
	fstream inputFile("input.txt", ios_base::in | ios_base::binary);
	ofstream outputFile("outputFile.txt");
	//stack.assignLabels(inputFile); // Assign labels to a line number.

	cout << "\nThe following is what the input file contains: \n\n";

	if (inputFile.is_open())
	{
		while (!inputFile.eof() && getline(inputFile, singleLine))
		{
			cout << singleLine << endl;
			BSTree.insertNodeIntoTree(singleLine, BSTree.rootPointer);
			// Trim leading spaces
			//std::size_t pos = singleLine.find_first_not_of(" \t");
			//if (std::string::npos != pos) { singleLine = singleLine.substr(pos); } // remove leading spaces
			//if (singleLine[singleLine.size() - 1] == '\r') { singleLine = singleLine.substr(0, singleLine.size() - 1); }
			//std::size_t postwo = singleLine.find_last_not_of(" \t");
			//if (std::string::npos != postwo) {
			//	singleLine = singleLine.substr(0, postwo + 1);
			//} // for foo.jaz

		}
		cout << "=======================================Below is what the tree looks like:" << endl;

		BSTree.postOrder(BSTree.rootPointer);

		inputFile.close();
	}
	else
	{
		cout << "Error: File is unable to open.  Check the location and the name of the file for possible errors.";
	}

	// Wait for user to press 'Enter' to exit program
	outputFile.close();
	char WaitChar;

	cout << "\nProccessing finished. Press 'Enter' to exit the program: \n\n";
	cin.get(WaitChar);
	return 0;
}