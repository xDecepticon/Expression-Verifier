#pragma once

#include <list>
#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

//  The booleanVerifier will verify whether or not the identity holds true.
//  The booleanVerifier will take in a string and return a boolean (true/false) verifying the result.

class booleanVerifier {

struct TreeNode {
	char key;
	TreeNode *leftChildPointer;
	TreeNode *rightChildPointer;
};

public:
	booleanVerifier(string identifier);
	~booleanVerifier();
	bool isOperatorValid(char key);
	void insertIntoTree(char key, TreeNode *leaf);
	void searchTree(TreeNode leaf, char key);
	TreeNode *rootPointer = NULL;
};