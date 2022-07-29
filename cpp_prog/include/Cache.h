#pragma once

#include <chrono>

#include "IDictionary.h"
#include "HtIDictionary.h"
#include "StdSqPriorityQueue.h"



int PriorityComparer(int item1, int item2)
{
	if (item1 < item2)
		return 1;
	else
		if (item1 > item2)
			return -1;
		else
			return 0;
}


template<class TKey, class TValue>
class Cache
{
private:
	HtIDictionary<TKey, TValue>* data;
	StdSqPriorityQueue<int, TKey>* priorities;
	int capacity;
	int count;
	int(*compareKeys)(int, int);
public:
	Cache(int const capacity, int(*compareKeys)(int, int));
public:
	int GetCount() const;
	int GetCapacity() const;
	TValue Get(TKey key) const;
	bool Find(TKey key) const;
public:
	bool Add(TKey key, TValue item);
	bool Clean();
public:
	~Cache()
	{
		delete data;
	}
};


template<class TKey, class TValue>
Cache<TKey, TValue>::Cache(int const capacity, int(*compareKeys)(int, int)) : count(0)
{
	this->capacity = capacity;
	this->data = new HtIDictionary<TKey, TValue>(capacity);
	this->priorities = new StdSqPriorityQueue<int, TKey>(compareKeys);
}


template<class TKey, class TValue>
int Cache<TKey, TValue>::GetCount() const
{
	return this->count;
}


template<class TKey, class TValue>
int Cache<TKey, TValue>::GetCapacity() const
{
	return this->capacity;
}


template<class TKey, class TValue>
TValue Cache<TKey, TValue>::Get(TKey key) const
{
	this->priorities->IncPriority(key);

	TValue value = this->data->Get(key);
	return value;
}


template<class TKey, class TValue>
bool Cache<TKey, TValue>::Find(TKey key) const
{
	return this->data->ContainsKey(key);
}


template<class TKey, class TValue>
bool Cache<TKey, TValue>::Add(TKey key, TValue item)
{
	TKey deleted_key;

	if (this->count == this->capacity)
	{
		deleted_key = this->priorities->Dequeue();
		this->data->Remove(deleted_key);
		this->count--;
	}

	if(this->data->Add(key, item))
	{
		this->priorities->Enqueue(key, 0);
		this->count++;
		return true;
	}
	return false;
};



template<class TKey, class TValue>
bool Cache<TKey, TValue>::Clean()
{
	delete this->data;
	delete this->priorities;
	
	this->data = new HtIDictionary<TKey, TValue>(this->capacity);
	this->priorities = new StdSqPriorityQueue<int, TKey>(compareKeys);

	this->count = 0;
	return true;
};