#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct BSTNode
{
	string data;
	BSTNode *left;
	BSTNode *right;

	// Create a binary node
	BSTNode()
	{
		data = "";
		left = NULL;
		right = NULL;
	}

	// Create a binary node with initial data
	BSTNode(string w)
	{
		data = w;
		left = NULL;
		right = NULL;
	}
};

class BSTree
{
private:
	BSTNode *root;

	// Insert a new item into the tree
	void insert(BSTNode *&root, BSTNode *&temp)
	{
		if (!root)
		{
			root = temp;
			return;
		}

		if (temp->data < root->data)
		{
			insert(root->left, temp);
			return;
		}

		if (temp->data > root->data)
		{
			insert(root->right, temp);
			return;
		}

		// Ignore if duplicate has been found
		delete temp;
	}

	// Recursively delete this tree
	void deleteTree(BSTNode *current)
	{
		if (current == NULL)
			return;

		deleteTree(current->left);
		deleteTree(current->right);
		delete current;
	}

public:

	// Construct a binary search tree
	BSTree()
	{
		root = NULL;
	}

	// Delete this tree
	~BSTree()
	{
		deleteTree(root);
	}

	// Insert a new element into the tree
	void insert(string x)
	{
		BSTNode *temp = new BSTNode(x);
		insert(root, temp);
	}
	
	// Search the element and return the total comparisons made when searching
	int countComparisonsToSearch(string x)
	{
		int comparisons = 0;

		BSTNode *current = root;

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
