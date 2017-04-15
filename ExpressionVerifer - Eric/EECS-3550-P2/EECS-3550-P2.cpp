// EECS-3550-P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>

struct node {
	char key;
	node *left;
	node *right;
};

struct tree {
	public:
		bool isOperator(char key);
		void insert(char key);
		void insert(char key, node *leaf);
		node search(node leaf);
		node *root = NULL;
};

bool tree::isOperator(char key) {
	if ((key == '+') || (key == '-') || (key == '*') || (key == '^')) {
		return true;
	}
	else {
		return false;
	}
}

void tree::insert(char key)
{
	if (root != NULL) {
		insert(key, root);
	}
	else {
		root = new node;
		root->key = key;
		root->left = NULL;
		root->right = NULL;
	}
}

void tree::insert(char key, node *leaf) {
	if (isOperator(key)) {
		// set as new root
		leaf->key = key;
		leaf->right = root;
		root = leaf;
	}
	else {
		// left leaf should be open
		leaf->key = key;
		root->left = leaf;
	}
}

node tree::search(node leaf)
{
	// search til bottom of tree
	// pass in root to start
	// Currently, this loops.
	if (leaf.right->right != NULL) {
		search(*leaf.right);
	}
	else return leaf;
}

















// This one is separate.
bool isOperator(std::string key) {
	if ((key == "+") || (key == "-") || (key == "*") || (key == "^")) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	// get input
	std::string in = "2 * 3 + 1 = 2 + 2 + 2 + 1";
	in.erase(std::remove(in.begin(), in.end(), ' '), in.end()); // remove all spaces

	/*size_t numOfEqSigns = std::count(in.begin(), in.end(), '='); // count number of equal signs (may not be needed))*/
	// if no equal sign, throw error at user and quit

	std::string inOne = in.substr(0, in.find('='));
	std::string inTwo = in.substr(in.find('=') + 1, in.size());
	
	tree treeOne;
	tree treeTwo;



	// create right side tree
	for (int i = 0; i < inOne.size(); i++) {
		// insert elements into tree
		treeOne.insert(inOne.at(i));
	}

	// evaluate results
	node sNode = treeOne.search(*treeOne.root);

	std::cout << inOne;


	// compare and output

    return 0;
}


