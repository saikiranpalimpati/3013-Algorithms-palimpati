
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>

using namespace std;

struct AVLNode
{
	string data;
	
	AVLNode *left;
	AVLNode *right;
	AVLNode *parent;
	int avlValue;
	
	AVLNode(string word)
	{
		data = word;
		left = right = parent = NULL;
		avlValue = 0;
	}
};

class AVLTree
{
private:
	AVLNode *root;
	
	// Insert a new element in the AVL tree recursively
	void insert(AVLNode *&nodePtr, AVLNode *&newNode)
	{
		if (nodePtr == NULL)
		{
			nodePtr = newNode;
			return;
		}
		
		if (newNode->data < nodePtr->data)
		{
			newNode->parent = nodePtr;
			insert(nodePtr->left, newNode);
			return;
		}

		if (newNode->data > nodePtr->data)
		{
			newNode->parent = nodePtr;
			insert(nodePtr->right, newNode);
			return;
		}

		// Delete duplicates
		delete newNode;
	}

	// Calculate the AVL values of each node
	void computeAvlValues(AVLNode *&nodePtr)
	{
		if (nodePtr == NULL)
			return;

		computeAvlValues(nodePtr->left);
		computeAvlValues(nodePtr->right);

		nodePtr->avlValue = avlValue(nodePtr);
		
		if (nodePtr->avlValue > 1)
			rotateLeft(nodePtr);
		else if (nodePtr->avlValue < -1)
			rotateRight(nodePtr);
	}

	// Perform left rotation to balance a tree
	void rotateLeft(AVLNode *&SubRoot)
	{
		if (leftHeavy(SubRoot->right))
			rotateRight(SubRoot->right);

		AVLNode *Temp;

		Temp = SubRoot->right;
		SubRoot->right = Temp->left;
		Temp->left = SubRoot;
		SubRoot = Temp;

		computeAvlValues(SubRoot);
	}

	// Perform right rotation to balance a tree
	void rotateRight(AVLNode *&SubRoot)
	{
		if (rightHeavy(SubRoot->left))
			rotateLeft(SubRoot->left);
		
		AVLNode *Temp;

		Temp = SubRoot->left;
		SubRoot->left = Temp->right;
		Temp->right = SubRoot;
		SubRoot = Temp;

		computeAvlValues(SubRoot);
	}

	// Compares the subtrees of a node to see which is taller
	bool leftHeavy(AVLNode *nodePtr)
	{
		return height(nodePtr->left)>height(nodePtr->right);
	}

	// Compares the subtrees of a node to see which is taller
	bool rightHeavy(AVLNode *nodePtr)
	{
		return height(nodePtr->right)>height(nodePtr->left);

	}
	
	// Calculate the avl value of a node to identify whether it is balanced or not
	int avlValue(AVLNode *nodePtr)
	{
		return height(nodePtr->right) - height(nodePtr->left);
	}

	// Calculate the level of a node in the tree
	int height(AVLNode *nodePtr)
	{
		if (nodePtr == NULL)
			return 0;
		
		int left_height = height(nodePtr->left);
		int right_height = height(nodePtr->right);
		
		if (left_height > right_height)
			return 1 + left_height;
		
		return 1 + right_height;
	}

	// Recursively delete this tree
	void deleteTree(AVLNode *current)
	{
		if (current == NULL)
			return;

		deleteTree(current->left);
		deleteTree(current->right);
		delete current;
	}

public:

	// Create an empty tree
	AVLTree()
	{
		root = NULL;
	}

	// Delete the tree from memory
	~AVLTree()
	{
		deleteTree(root);
	}

	// Insert a new element into the AVL tree then balances it
	void insert(string word)
	{
		AVLNode *newNode;

		newNode = new AVLNode(word);
		insert(root, newNode);
		computeAvlValues(root);
	}

	// Search the element and return the total comparisons made when searching
	int countComparisonsToSearch(string x)
	{
		int comparisons = 0;

		AVLNode *current = root;

		while (current != NULL)
		{
			comparisons++;

			if (x == current->data)
				break;

			if (x > current->data)
				current = current->right;
			else if (x < current->data)
				current = current->left;
		}

		return comparisons;
	}
};


#endif
