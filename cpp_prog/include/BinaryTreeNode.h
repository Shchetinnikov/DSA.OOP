#pragma once

#include "Exception.h"

/*

	Узел бинарного дерева поиска

*/

template<class TKey, class TValue>
class BinaryTreeNode
{
private:
	struct Node
	{
		TKey key;
		TValue value;
	};
private:
	Node* item;
	BinaryTreeNode<TKey, TValue>* left;
	BinaryTreeNode<TKey, TValue>* right;
public:
	// конструкторы
	BinaryTreeNode(const TKey key, const TValue value);
	BinaryTreeNode(const TKey key, const TValue value, BinaryTreeNode<TKey, TValue>* left, BinaryTreeNode<TKey, TValue>* right);
	BinaryTreeNode(const BinaryTreeNode<TKey, TValue>& node);
public:
	// декомпозиция
	Node GetTreeNode() const  { return *this->item; };
	BinaryTreeNode<TKey, TValue>* GetLeft() const  { return this->left; };
	BinaryTreeNode<TKey, TValue>* GetRight() const { return this->right; };
public:
	// методы
	// содержимое узла не изменяется
	void SetLeft(BinaryTreeNode<TKey, TValue>* node);
	void SetRight(BinaryTreeNode<TKey, TValue>* node);
public:
	// деструктор
	~BinaryTreeNode() 
	{
		delete item;
	}
};




template<class TKey, class TValue>
BinaryTreeNode<TKey, TValue> :: BinaryTreeNode(const TKey key, const TValue value) : left(nullptr), right(nullptr)
{
	this->item = new Node;
	this->item->key = key;
	this->item->value = value;
};


template<class TKey, class TValue>
BinaryTreeNode<TKey, TValue> ::BinaryTreeNode(const TKey key, const TValue value, BinaryTreeNode<TKey, TValue>* left, BinaryTreeNode<TKey, TValue>* right)
{
	if (left->item.key >= key || right->item.key <= key)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->item = new Node;
	this->item->key = key;
	this->item->value = value;
	this->left = left;
	this->right = right;
};


template<class TKey, class TValue>
BinaryTreeNode<TKey, TValue> ::BinaryTreeNode(const BinaryTreeNode<TKey, TValue>& node)
{
	this->item = new Node;
	this->item->key = node.item->key;
	this->item->value = node.item->value;
	this->left = node.left;
	this->right = node.right;
}


template<class TKey, class TValue>
void BinaryTreeNode<TKey, TValue> :: SetLeft(BinaryTreeNode<TKey, TValue>* node)
{
	if (!node)
	{
		this->left = nullptr;
		return;
	};

	if (node->item->key >= this->item->key)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->left = node;
};


template<class TKey, class TValue>
void BinaryTreeNode<TKey, TValue> ::SetRight(BinaryTreeNode<TKey, TValue>* node)
{
	if (!node)
	{
		this->right = nullptr;
		return;
	};

	if (node->item->key <= this->item->key)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->right = node;
};