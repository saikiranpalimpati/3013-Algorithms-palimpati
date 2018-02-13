#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct node
{
	int data;
	node *left;
	node *right;
	node();
	node(int x);
};
class BSTree
{
private:
	node * root;
	int count(node *root);
	void insert(node *&root, node *&temp);
	void print_node(node *n, string label = "");
	node *minValueNode(node *root);
	node *deleteNode(node *&root, int key);
	int height(node *root);
	void printGivenLevel(node *root, int level);
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);
public:
	BSTree();
	int count();
	void insert(int x);
	void deleteNode(int key);
	void minValue();
	int height(int key = -1);
	int top();
	void printLevelOrder();
	void GraphVizOut(string filename);
	~BSTree();


};

