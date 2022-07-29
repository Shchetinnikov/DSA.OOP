#pragma once

#include "IDictionary.h"
#include "Sequence.h"
#include "BinaryTree.h"


template<class TKey, class TValue>
class BtIDictionary : public IDictionary<TKey, TValue>
{
private:
	BinaryTree<TKey, TValue>* data;
	int count;
	int capacity;
public:
	BtIDictionary();
	BtIDictionary(const BtIDictionary<TKey, TValue>& idict);
public:
	virtual int GetCount() const override;
	virtual int GetCapacity() const override;
	virtual TValue Get(TKey key) const override;
	virtual bool ContainsKey(TKey key) const override;
public:
	virtual bool Add(TKey key, TValue item) override;
	virtual bool Remove(TKey key) override;
public:
	~BtIDictionary() 
	{
		delete data;
	}
};


template<class TKey, class TValue>
BtIDictionary<TKey, TValue> :: BtIDictionary() : count(0), capacity(0)
{
	this->data = new BinaryTree<TKey, TValue>();
};


template<class TKey, class TValue>
BtIDictionary<TKey, TValue> ::BtIDictionary(const BtIDictionary<TKey, TValue>& idict)
{
	this->count = idict.count;
	this->capacity = idict.capacity;
	this->data = new BinaryTree<TKey, TValue>(*idict.data);
};


template<class TKey, class TValue>
int BtIDictionary<TKey, TValue> :: GetCount() const
{
	return this->count;
}


template<class TKey, class TValue>
int BtIDictionary<TKey, TValue> :: GetCapacity() const
{
	return this->capacity;
};


template<class TKey, class TValue>
TValue BtIDictionary<TKey, TValue> :: Get(TKey key) const
{
	BinaryTreeNode<TKey, TValue>* node = this->data->GetNode(key);

	if (!node)
		throw NoneValue("***ValueError: there is not value of argument in the binary tree***", __FILE__, __LINE__);
	else
		return node->GetTreeNode().value;
};


template<class TKey, class TValue>
bool BtIDictionary<TKey, TValue> ::ContainsKey(TKey key) const
{
	return this->data->Find(key);
};


template<class TKey, class TValue>
bool BtIDictionary<TKey, TValue> :: Add(TKey key, TValue item)
{
	if (this->data->Insert(key, item))
	{
		this->capacity++;
		this->count++;
		return true;
	}
	return false;
};


template<class TKey, class TValue>
bool BtIDictionary<TKey, TValue> ::Remove(TKey key)
{
	if (this->data->RemoveNode(key))
	{
		this->capacity--;
		this->count--;
		return true;
	}
	return false;
}