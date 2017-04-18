#pragma once

#include <list>
#include <string>
#include <stack>
#include <vector>
#include <iostream>

class binaryTree {

	struct TreeNode {
		std::string key;
		int value;
		TreeNode *leftChildPointer;
		TreeNode *rightChildPointer;
	};

public:
	binaryTree();
	~binaryTree();
	TreeNode *rootPointer = NULL;
	void insert(TreeNode *&nodePtr, TreeNode *&newNode, std::string key);
	void insertNodeIntoTree(std::string key, TreeNode *&nodePointer);
	void clearSubTree(TreeNode *nodePtr);
	void postOrder(TreeNode * nodePtr) const;
};