#include "BSTree.h"

BSTree::BSTree()
{
	root = NULL;
}

BSTree::~BSTree()
{
}

int BSTree::count()
{
	return count(root);
}

int BSTree::height(int key)
{
	if (key > 0)
	{
		//find node
	}
	else
	{
		return height(root);
	}
	return 0;
}

void BSTree::insert(int x)
{
	node *temp = new node(x);
	insert(root, temp);
}

void BSTree::deleteNode(int key)
{
	 deleteNode(root, key);
	 root = NULL;
}

void BSTree::minValue()
{
	print_node(minValueNode(root), "minVal");
}


int BSTree::count(node * root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}

void BSTree::insert(node *& root, node *& temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->data < root->data)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

void BSTree::print_node(node * n, string label)
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->data << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

node * BSTree::minValueNode(node * root)
{
	node *current = root;

	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}

node * BSTree::deleteNode(node *&root, int key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if (root->right == NULL)
		{
			node *temp = root->left;
			delete root;
			return temp;

		}
		else if (root->left == NULL) {
			node *temp = root->right;
			delete root;
			return temp;
		}
		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		node *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->data = temp->data;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

int BSTree::height(node * root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

void BSTree::printGivenLevel(node * root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_node(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}

void BSTree::GraphVizGetIds(node * nodePtr, ofstream & VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->data
			<< "[label=\"" << nodePtr->data << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

void BSTree::GraphVizMakeConnections(node * nodePtr, ofstream & VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->left->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->right->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}





void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}

void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}

int BSTree::top()
{
	if (root)
		return root->data;
	else
		return 0;
}

node::node()
{
	{
		data = -1;
		left = NULL;
		right = NULL;
	}
}

node::node(int x)
{
	{
		data = x;
		left = NULL;
		right = NULL;
	}
}