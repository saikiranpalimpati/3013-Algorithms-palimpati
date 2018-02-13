///////////////////////////////////////////////////////////////////////////////
// Title: FIX DELETE METHOD

// Files: main.cpp, BSTree.cpp, BSTree.h

// Semester: (3013 Algorithms) Spring 2018

// Author: (SAIKIRAN PALIMPATI)

// Email: (palimpatisaikiran@yahoo.in)

// Description: fixed the delete method when it doesn't have a left or right child
/////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include"BSTree.h"
using namespace std;
//http://www.webgraphviz.com/
int main()
{
	srand(2342);

	BSTree B;

	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	B.printLevelOrder();
	B.GraphVizOut("before.txt");

	 while(B.top()){
	    cout<<"removing: "<<B.top()<<endl;
		B.deleteNode(B.top());
	 }

	/*B.deleteNode(3);
	B.deleteNode(29);
	B.deleteNode(27);
	B.deleteNode(10);*/
	B.printLevelOrder();

	B.GraphVizOut("after.txt");
	system("pause");
	return 0;
}
