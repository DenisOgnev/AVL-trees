#pragma once
#include <iostream>

template<class Key, class Data>
struct Node
{
	Key key;
	Data data;
	unsigned char height;
	Node<Key, Data>* left;
	Node<Key, Data>* right;
	Node(Key k, Data d) { key = k; data = d; left = right = nullptr; height = 1; }
};

template<class Key, class Data>
class AVLtree
{
	Node<Key, Data>* node;
public:
	AVLtree(Key k, Data d) { node = new Node<Key, Data>(k, d); }
	void insert(Key k, Data d);
	void remove(Key k);
	int find(Key k);
	void print();
};

template<class Key, class Data>
unsigned char height(Node<Key, Data>* p)
{
	return p ? p->height : 0;
	/*if (p)
		return p->height;
	else
		return 0;*/
}

template<class Key, class Data>
int balanceFactor(Node<Key, Data>* p)
{
	return height(p->right) - height(p->left);
}

template<class Key, class Data>
void fixHeight(Node<Key, Data>* p)
{
	unsigned char hLeft = height(p->left);
	unsigned char hRight = height(p->right);
	p->height = (hLeft > hRight ? hLeft : hRight) + 1;
	/*if (hLeft > hRight)
		p->height = hLeft + 1;
	else
		p->height = hRight + 1;*/
}

template<class Key, class Data>
Node<Key, Data>* rotateRight(Node<Key, Data>* p)
{
	Node<Key, Data>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

template<class Key, class Data>
Node<Key, Data>* rotateLeft(Node<Key, Data>* q)
{
	Node<Key, Data>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

template<class Key, class Data>
Node<Key, Data>* balance(Node<Key, Data>* p)
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

template<class Key, class Data>
Node<Key, Data>* _insert(Node<Key, Data>* p, Key k, Data d)
{
	if (!p)
		return new Node<Key, Data>(k, d);
	if (k < p->key)
		p->left = _insert(p->left, k, d);
	else
		p->right = _insert(p->right, k, d);
	return balance(p);
}

template<class Key, class Data>
Node<Key, Data>* findMin(Node<Key, Data>* p)
{
	return p->left ? findMin(p->left) : p;
	/*if (p->left)
		return findMin(p->left);
	else
		return p;*/
}

template<class Key, class Data>
Node<Key, Data>* removeMin(Node<Key, Data>* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

template<class Key, class Data>
Node<Key, Data>* _remove(Node<Key, Data>* p, Key k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = _remove(p->left, k);
	else if (k > p->key)
		p->right = _remove(p->right, k);
	else //k == p->key
	{
		Node<Key, Data>* q = p->left;
		Node<Key, Data>* r = p->right;
		delete p;
		if (!r) return q;
		Node<Key, Data>* min = findMin(r);
		min->right = removeMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

template<class Key, class Data>
Node<Key, Data>* _find(Node<Key, Data>* p, Key k)
{
	//if (!p) return 0;
	//if (!p->left || !p->right) return 0;
	//if (k < p->key)
	//	p->left = _find(p->left, k);
	//else if (k > p->key)
	//	p->right = _find(p->right, k);
	//else //k == p->key
	//{
	//	return p;
	//}

	if (!p) return 0;
	//if (!p->left || !p->right) return 0;
	if (k < p->key)
		if (p->left)
			Node<Key, Data>* q = _find(p->left, k);
		else
			return 0; //throw
	else if (k > p->key)
		if (p->right)
			Node<Key, Data>* q = _find(p->right, k);
		else
			return 0; //throw
	else //k == p->key
		return p;
}

template<class Key, class Data>
void _print(Node<Key, Data>* p)
{
	if (!p) return;
	std::cout << p->key << " | " << p->data << std::endl;
	_print(p->left);
	_print(p->right);
}

template<class Key, class Data>
void AVLtree<Key, Data>::insert(Key k, Data d)
{
	_insert(node, k, d);
}

template<class Key, class Data>
void AVLtree<Key, Data>::remove(Key k)
{
	_remove(node, k);
}

template<class Key, class Data>
int AVLtree<Key, Data>::find(Key k)
{
	if (_find(node, k) == 0)
		return 0; //throw
	return _find(node, k)->data;
}

template<class Key, class Data>
void AVLtree<Key, Data>::print()
{
	_print(node);
}