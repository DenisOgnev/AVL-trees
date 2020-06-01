#include <iostream>
#include "AVL-tree.h"

using namespace std;

int main()
{
	AVLtree tree(10, 5);
	tree.insert(5, 6);
	tree.insert(15, 4);
	tree.insert(7, 8);
	tree.insert(6, 3);

	tree.print();
	cout << endl;

	tree.remove(6);

	tree.print();
	cout << endl;

	cout << tree.find(15) << endl;

	system("pause");
}