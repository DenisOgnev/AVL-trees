#include <iostream>
#include "AVL-tree.h"

using namespace std;

int main()
{
	AVLtree<int, int> tree(10, 5);
	tree.insert(5, 6);
	tree.insert(15, 4);
	tree.insert(7, 8);
	tree.insert(6, 3);
	tree.insert(6, 2);
	cout << tree.find(16) << endl;
	tree.print();
	cout << endl;

	AVLtree<int, string> strTree(2, "2");
	strTree.insert(3, "abc");
	strTree.insert(1, "ddd");
	cout << strTree.find(4) << endl;
	cout << *strTree.find(2) << endl;
	strTree.print();
	
	

	system("pause");
}