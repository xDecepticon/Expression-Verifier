#pragma once

#include "booleanVerifier.h"
#include <list>
#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;


//bool booleanVerifier::isOperatorValid(char key)
//{
//	if ((key == '+') || (key == '*')) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//void booleanVerifier::insertIntoTree(char key, TreeNode * leaf)
//{
//	TreeNode* currentNode = rootPointer;
//	TreeNode* previousNode = NULL;
//
//	if (rootPointer == NULL)
//	{
//		TreeNode* newNode = new TreeNode();
//		newNode->key = key;
//		rootPointer = newNode;
//		currentNode = rootPointer;
//	}
//}
//
//void booleanVerifier::searchTree(TreeNode leaf, char key)
//{
//	// Start at the beginning of the tree (root) where there is no previous node.
//	TreeNode* currentNode = rootPointer;
//
//	// If the currentNode does point to some value
//	while (currentNode)
//	{
//		// If the user's key matches the curent node's key (that is, the node has been found) display the key
//		if (key == currentNode->key)
//		{
//			cout << "something here" << endl;
//			break;
//		}
//		// If the user's key is greater than the current node's key, then the current node points to the right child
//		if (key > currentNode->key)
//		{
//			currentNode = currentNode->rightChildPointer;
//		}
//		// If the user's key is less than the current node's key, then the current node points to the left child
//		else if (key < currentNode->key)
//		{
//			currentNode = currentNode->leftChildPointer;
//		}
//	}
//}

bool And(bool idenifier1, bool idenifier2) {
	return idenifier1 && idenifier2;
}

bool Or(bool idenifier1, bool idenifier2) {
	return idenifier1 || idenifier2;
}