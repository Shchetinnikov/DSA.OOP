#pragma once

#include <string>

#include "IPriorityQueue.h"
#include "Sequence.h"
#include "ListSequence.h"


template<class TKey, class TValue>
class StdSqPriorityQueue: public IPriorityQueue<TKey, TValue>
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
	StdSqPriorityQueue(int(*compareKeys)(TKey, TKey)) : count(0)
	{
		this->data = new ListSequence<Record*>();
		this->compareKeys = compareKeys;
	}
public:
	TKey PeekPriority(const int index = 0) const;
	virtual TValue Peek(const int index) const override;
	virtual TValue PeekFirst() const override;
	virtual TValue PeekLast() const override;
	virtual int GetCount() const override;
public:
	virtual void Enqueue(TValue item, TKey priority) override;
	virtual TValue Dequeue() override;
public:
	bool IncPriority(TValue item);
public:
	~StdSqPriorityQueue()
	{
		delete data;
	}
};


template<class TKey, class TValue>
TKey StdSqPriorityQueue<TKey, TValue> ::PeekPriority(const int index) const
{
	if (index >= this->data->GetLength() || index < 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	return this->data->Get(index)->priority;
}


template<class TKey, class TValue>
TValue StdSqPriorityQueue<TKey, TValue> ::Peek(const int index) const
{
	if (index >= this->data->GetLength() || index < 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	return this->data->Get(index)->data;
}


template<class TKey, class TValue>
TValue StdSqPriorityQueue<TKey, TValue> ::PeekFirst() const
{
	return this->data->GetFirst()->data;
}


template<class TKey, class TValue>
TValue StdSqPriorityQueue<TKey, TValue> ::PeekLast() const
{
	return this->data->GetLast()->data;
}


template<class TKey, class TValue>
int StdSqPriorityQueue<TKey, TValue> ::GetCount() const
{
	return this->count;
}


template<class TKey, class TValue>
void StdSqPriorityQueue<TKey, TValue> ::Enqueue(TValue item, TKey priority)
{
	Record* new_record = new Record({ item, priority });
	
	if (!this->data->GetLength())
	{
		this->data->Append(new_record);
		this->count++;
		return;
	}


	int index = 0;
	Record* record;
	for(index; index < this->data->GetLength(); index++)
	{ 
		record = this->data->Get(index);
		if (compareKeys(priority, record->priority) != 1 && compareKeys(priority, record->priority) != 0)
			break;
	}

	if(index >= this->data->GetLength())
		this->data->Append(new_record);
	else
		this->data->InsertAt(index, new_record);
	this->count++;
}
	

template<class TKey, class TValue>
TValue StdSqPriorityQueue<TKey, TValue> ::Dequeue()
{
	TValue item = this->data->GetFirst()->data;
	
	this->data->RemoveAt(0);
	this->count--;
	return item;
}


template<class TKey, class TValue>
bool StdSqPriorityQueue<TKey, TValue> ::IncPriority(TValue item)
{
	ListSequence<Record*>* list = new ListSequence<Record*>();

	int index = 0;
	Record* record;

	bool flag = false;
	int count_pq = this->count;

	for (int i = 0; i < count_pq; i++, index++)
	{
		record = this->data->Get(index);
		if (record->data == item)
		{
			list->Append(new Record({ item, record->priority + 1 }));
			this->data->RemoveAt(index);
			this->count--;
			index--;
			flag = true;
		}
	}

	for (int i = 0; i < list->GetLength(); i++)
	{
		record = list->Get(i);
		this->Enqueue(record->data, record->priority);
	}

	delete list;
	return flag;
}


