#include "binaryTree.h"
#include <list>
#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

binaryTree::binaryTree() {
	rootPointer = NULL;
}

binaryTree::~binaryTree() {

}

void binaryTree::insert(TreeNode *&nodePointer, TreeNode *&newNode, string key)
{
	if (nodePointer == NULL)
	{
		TreeNode *newTreeNode = new TreeNode;
		newTreeNode->key = key;
		newTreeNode->value = 1;
		newTreeNode->leftChildPointer = newTreeNode->rightChildPointer = NULL;
		if (newNode->key > newTreeNode->key)
			newNode->leftChildPointer = newTreeNode;
		else
			newNode->rightChildPointer = newTreeNode;
	}
	else if (nodePointer->key > key)
		insert(nodePointer->leftChildPointer, nodePointer, key);
	else if (nodePointer->key < key)
		insert(nodePointer->rightChildPointer, nodePointer, key);
	else if (nodePointer->key == key)
		nodePointer->value += 1;
}

void binaryTree::insertNodeIntoTree(string key, TreeNode *&nodePointer)
{
	if (rootPointer == NULL)
	{
		rootPointer = new TreeNode;
		rootPointer->key = key;
		rootPointer->value = 1;
		rootPointer->leftChildPointer = rootPointer->rightChildPointer = NULL;
	}
	else if (rootPointer->key > key)
		insert(rootPointer->leftChildPointer, rootPointer, key);
	else if (rootPointer->key < key)
		insert(rootPointer->rightChildPointer, rootPointer, key);
	else if (rootPointer->key == key)
		rootPointer->value += 1;
}

void binaryTree::clearSubTree(TreeNode *nodePointer)
{
	if (nodePointer)
	{
		if (nodePointer->leftChildPointer)
			clearSubTree(nodePointer->leftChildPointer);
		if (nodePointer->rightChildPointer)
			clearSubTree(nodePointer->rightChildPointer);
		delete nodePointer;
	}
}

void binaryTree::postOrder(TreeNode *nodePointer) const
{
	// Check if the tree is not empty and traverse left and right
	if (nodePointer != NULL)
	{
		postOrder(nodePointer->leftChildPointer);
		postOrder(nodePointer->rightChildPointer);

		cout << nodePointer->key << "\n ";
	}
	else
		return;
}