// EECS-3550-P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>

/*struct node {
	char key;
	node *left;
	node *right;
};

struct tree {
	public:
		bool isOperator(char key);
		void insert(char key);
		void insert(char key, node *leaf);
		node *search(struct node *leaf);
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

node * tree::search(struct node *leaf)
{
	if (leaf->right->right != NULL) {
		search(leaf->right);
	}
	else {
		std::cout << leaf->key;
		return leaf;
	}
}*/

















// This one is separate.
bool isOperator(char key) {
	if ((key == '+') || (key == '-') || (key == '*') || (key == '^')) {
		return true;
	}
	else {
		return false;
	}
}

std::string formStr(std::string str) {
	std::string rstr;
	for (int i = 0; i < str.size(); i++) {
		if (isOperator(str.at(i))) {
			if (str.at(i) == '+') {
				rstr += str.at(++i);
			}
			else {
				// get next char, loop until all characters are done
				char prev = str.at(i - 1);
				char next = str.at(++i);
				for (int j = (int)(next - '0'); j > 1; j--) {
					rstr += prev;
				}
			}
		}
		else {
			rstr += str.at(i);
		}
		std::cout << rstr << '\n';
	}
	return rstr;
}

int main()
{
	// get input
	std::string in = "2 * 3 + 1 = 2 + 2 + 2 + 1";
	in.erase(std::remove(in.begin(), in.end(), ' '), in.end()); // remove all spaces

	signed int numOfEqSigns = std::count(in.begin(), in.end(), '='); // count number of equal signs


	// if no equal sign, throw error at user and quit
	if (numOfEqSigns == 0) { std::cout << "Expression cannot be compared."; exit(1); }

	std::string inOne = in.substr(0, in.find('='));
	std::string inTwo = in.substr(in.find('=') + 1, in.size());

	std::string strarry[2]; 
	strarry[0] = inOne;
	strarry[1] = inTwo;

	// For the string, there isn't a defined order of operations for * or +. 
	// We /assumed/ it goes in order.

	std::string rstrarry[2];

	for (int i = 0; numOfEqSigns >= 0 ; numOfEqSigns--, i++) {
		rstrarry[i] = formStr(strarry[i]);
	}

	for (int i = strarry->size(), j = 0; i > 0; i--, j++) {
		std::string str = rstrarry[j];

		for (int i = strarry->size(), k = 1; i > 0; i--, k++) {

			if (str != rstrarry[k])
				std::cout << str << "!=" << rstrarry[k];
			else
			{
				std::cout << str << "=" << rstrarry[k];
			}
			std::cin.get();
			exit(1);
		}
	}

	std::cout << "All equations are valid!";

	char WaitChar;

	std::cout << "\nProccessing finished. Press 'Enter' to exit the program: \n\n";
	std::cin.get(WaitChar);
	return 0;
}


