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

	tree.print();
	cout << endl;

	tree.remove(6);
	cout << tree.find(6) << endl;

	cout << tree.find(16) << endl;

	cout << tree.find(15) << endl;

	tree.print();
	cout << endl;
	cout << tree.find(4);
	cout << endl;
	tree.print();
	cout << endl;

	cout << tree.find(15) << endl;

	system("pause");
}