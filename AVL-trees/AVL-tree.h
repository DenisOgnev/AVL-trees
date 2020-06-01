#pragma once
#include <iostream>

struct Node
{
	int key;
	int data;
	unsigned char height;
	Node* left;
	Node* right;
	Node(int k, int d) { key = k; data = d; left = right = nullptr; height = 1; }
};

class AVLtree
{
	Node* node;
public:
	AVLtree(int k, int d) { node = new Node(k, d); }
	void insert(int k, int d);
	void remove(int k);
	int find(int k);
	void print();
};

unsigned char height(Node* p)
{
	return p ? p->height : 0;
	/*if (p)
		return p->height;
	else
		return 0;*/
}

int balanceFactor(Node* p)
{
	return height(p->right) - height(p->left);
}

void fixHeight(Node* p)
{
	unsigned char hLeft = height(p->left);
	unsigned char hRight = height(p->right);
	p->height = (hLeft > hRight ? hLeft : hRight) + 1;
	/*if (hLeft > hRight)
		p->height = hLeft + 1;
	else
		p->height = hRight + 1;*/
}

Node* rotateRight(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

Node* rotateLeft(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

Node* balance(Node* p)
{
	fixHeight(p);
	if (balanceFactor(p) == 2)
	{
		if (balanceFactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (balanceFactor(p) == -2)
	{
		if (balanceFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}

Node* _insert(Node* p, int k, int d)
{
	if (!p)
		return new Node(k, d);
	if (k < p->key)
		p->left = _insert(p->left, k, d);
	else
		p->right = _insert(p->right, k, d);
	return balance(p);
}

Node* findMin(Node* p)
{
	return p->left ? findMin(p->left) : p;
	/*if (p->left)
		return findMin(p->left);
	else
		return p;*/
}

Node* removeMin(Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

Node* _remove(Node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = _remove(p->left, k);
	else if (k > p->key)
		p->right = _remove(p->right, k);
	else //k == p->key
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return q;
		Node* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

Node* _find(Node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = _find(p->left, k);
	else if (k > p->key)
		p->right = _find(p->right, k);
	else //k == p->key
	{
		return p;
	}
	//return balance(p);
}

void _print(Node* p)
{
	if (!p) return;
	std::cout << p->key << " | " << p->data << std::endl;
	_print(p->left);
	_print(p->right);
}

void AVLtree::insert(int k, int d)
{
	_insert(node, k, d);
}

void AVLtree::remove(int k)
{
	_remove(node, k);
}

int AVLtree::find(int k)
{
	return _find(node, k)->data;
}

void AVLtree::print()
{
	_print(node);
}