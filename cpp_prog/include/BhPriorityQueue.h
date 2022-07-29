#pragma once

#include "IPriorityQueue.h"

template<class TKey, class TValue>
class BhPriorityQueue : IPriorityQueue<TKey, TValue>
{
private:
	struct Record
	{
		TValue data;
		TKey priority;
	};
private:
	Sequence<Record*>* data;
	int count;
	int(*compareKeys)(TKey, TKey);
public:
	BhPriorityQueue(int(*compareKeys)(TKey, TKey)) : count(0)
	{
		this->data = new ListSequence<Record*>();
		this->compareKeys = compareKeys;
	}
public:
    virtual TValue Peek(const int i) const override;
    virtual TValue PeekFirst() const override;
    virtual TValue PeekLast() const override;
    virtual int GetCount() const override;
public:
    virtual void Enqueue(TValue item, TKey priority) override;
    virtual TValue Dequeue() override;
public:
	~BhPriorityQueue()
	{
		delete data;
	}
};