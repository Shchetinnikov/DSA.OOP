#pragma once

#include "Exception.h"
#include "IIterators.h"
#include "ISet.h"
#include "Pair.h"
#include "HashTable.h"


template<class TKey, class TValue>
class HashSet: public ISet<Pair<TKey, TValue>*>
{
private:
	HashTable<TKey, TValue>* data;
	int count;
private:
	class HashSetIterator : public IIterator<Pair<TKey, TValue>*>
	{
	private:
		HashTable<TKey, TValue>* data;
		IIterator<Pair<TKey, TValue>*>* iterator;
		int currentIndex;
	public:
		HashSetIterator(HashSet<TKey, TValue>* hash_set)
		{
			this->data = hash_set->data;
			this->iterator = hash_set->data->GetIterator();
			this->currentIndex = -1;
			if (hash_set->count)
			{
				this->currentIndex = 0;
				for(this->iterator; !this->iterator->HasValue(); this->iterator->Next())
				{ 
					this->currentIndex++;
				}
			}
		}
	public:
		virtual Pair<TKey, TValue>* GetValue() const override { return this->iterator->GetValue(); }
		virtual IIterator<Pair<TKey, TValue>*>* Next() override
		{
			if (!this->data->GetCount())
			{
				this->currentIndex = -1;
				delete this->iterator;
				this->iterator = this->data->GetIterator();
				return this;
			}

			this->iterator->Next();
			this->currentIndex++;
			for (this->iterator; this->currentIndex < this->data->GetCapacity() && !this->iterator->HasValue(); this->iterator->Next(), this->currentIndex++)
			{ }
			return this;
		}

		virtual bool HasNext() override 
		{ 
			this->iterator->Next();
			int index = this->currentIndex + 1;
			for (this->iterator; index < this->data->GetCapacity() && !this->iterator->HasValue(); this->iterator->Next(), index++)
			{ }

			int flag = true;
			if (index >= this->data->GetCapacity())
				flag = false;

			for (this->iterator; index != this->currentIndex; this->iterator->Prev(), index--)
			{ }
			return flag;
		}

		virtual bool HasValue() override { return this->iterator->HasValue(); }
	public:
		virtual IIterator<Pair<TKey, TValue>*>* Prev() override
		{
			if (!this->data->GetCount())
			{
				this->currentIndex = -1;
				delete this->iterator;
				this->iterator = this->data->GetIterator();
				return this;
			}

			this->iterator->Prev();
			this->currentIndex--;
			for (this->iterator; this->currentIndex >= 0 && !this->iterator->HasValue(); this->iterator->Prev(), this->currentIndex--)
			{ }
			return this;
		}

		virtual bool HasPrev() override 
		{ 
			this->iterator->Prev();
			int index = this->currentIndex - 1;
			for (this->iterator; index >= 0 && !this->iterator->HasValue(); this->iterator->Prev(), index--)
			{ }

			int flag = true;
			if (index < 0)
				flag = false;

			for (this->iterator; index != this->currentIndex; this->iterator->Next(), index++)
			{ }
			return flag;
		}
	};
public:
	HashSet(const int capacity = 0);
	HashSet(const HashSet<TKey, TValue>& set);
public:
	virtual int GetCount() const override { return this->count; }
	virtual bool HasElement(Pair<TKey, TValue>* element) const override { return this->data->Find(element->GetKey()); }
	//virtual bool IsEmpty() const override { return this->GetCount() == 0; }
public:
	virtual void Union(ISet<Pair<TKey, TValue>*>* set) override;
	virtual void Intersect(ISet<Pair<TKey, TValue>*>* set) override;
	virtual void Except(ISet<Pair<TKey, TValue>*>* set) override;
	virtual ISet<Pair<Pair<TKey, TValue>*, Pair<TKey, TValue>*>*>* Product(ISet<Pair<TKey, TValue>*>* set) override;
	bool Add(Pair<TKey, TValue>* element);
	void Clear();
	bool Remove(Pair<TKey, TValue>* element);
public:
	virtual IIterator<Pair<TKey, TValue>*>* GetIterator() override
	{
		return new HashSetIterator(this);
	}
public:
	~HashSet() 
	{  
		delete data;
	}
};


template<class TKey, class TValue>
HashSet<TKey, TValue> ::HashSet(const int capacity) : count(0)
{
	if (capacity < 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->data = new HashTable<TKey, TValue>(capacity);
}


template<class TKey, class TValue>
HashSet<TKey, TValue> ::HashSet(const HashSet<TKey, TValue>& set)
{
	this->count = set.count;
	this->data = new HashTable<TKey, TValue>(*set.data);
}


template<class TKey, class TValue>
void HashSet<TKey, TValue> ::Union(ISet<Pair<TKey, TValue>*>* set)
{
	Pair<TKey, TValue>* pair;
	auto iterator = set->GetIterator();
	for (iterator; iterator->HasValue(); iterator->Next())
	{
		pair = iterator->GetValue();
		if (!this->HasElement(pair))
		{
			this->Add(pair);
		}
	}
	delete iterator;
}


template<class TKey, class TValue>
void HashSet<TKey, TValue> ::Intersect(ISet<Pair<TKey, TValue>*>* set)
{
	Pair<TKey, TValue>* pair;
	TKey key;
	TValue value;
	HashTable<TKey, TValue>* new_data = new HashTable<TKey, TValue>();

	auto iterator = set->GetIterator();
	for (iterator; iterator->HasValue(); iterator->Next())
	{
		pair = iterator->GetValue();
		if (this->HasElement(pair))
		{
			key = pair->GetKey();
			value = pair->GetValue();
			new_data->Add(key, value);
		}
	}
	delete this->data;
	this->data = new_data;
	this->count = new_data->GetCount();

	delete iterator;
}


template<class TKey, class TValue>
void HashSet<TKey, TValue> ::Except(ISet<Pair<TKey, TValue>*>* set)
{
	Pair<TKey, TValue>* pair;
	TKey key;
	TValue value;
	HashTable<TKey, TValue>* new_data = new HashTable<TKey, TValue>();

	auto iterator = set->GetIterator();
	for (iterator; iterator->HasValue(); iterator->Next())
	{
		pair = iterator->GetValue();
		if (!this->HasElement(pair))
		{
			key = pair->GetKey();
			value = pair->GetValue();
			new_data->Add(key, value);
		}
	}
	delete iterator;

	iterator = this->GetIterator();
	for (iterator; iterator->HasValue(); iterator->Next())
	{
		pair = iterator->GetValue();
		if (!set->HasElement(pair))
		{
			key = pair->GetKey();
			value = pair->GetValue();
			new_data->Add(key, value);
		}
	}
	delete iterator;

	delete this->data;
	this->data = new_data;
	this->count = new_data->GetCount();
}


template<class TKey, class TValue>
ISet<Pair<Pair<TKey, TValue>*, Pair<TKey, TValue>*>*>* HashSet<TKey, TValue> ::Product(ISet<Pair<TKey, TValue>*>* set)
{
	return nullptr;
}


template<class TKey, class TValue>
bool HashSet<TKey, TValue> ::Add(Pair<TKey, TValue>* element)
{
	TKey key = element->GetKey();
	TValue value = element->GetValue();
	if (this->data->Add(key, value))
	{
		this->count = this->data->GetCount();
		return true;
	}
	return false;
};


template<class TKey, class TValue>
void HashSet<TKey, TValue> ::Clear()
{
	this->count = 0;
	delete this->data;
	this->data = new HashTable<TKey, TValue>();
}


template<class TKey, class TValue>
bool HashSet<TKey, TValue> ::Remove(Pair<TKey, TValue>* element)
{
	TKey key = element->GetKey();
	if (this->data->Remove(key))
	{
		this->count = this->data->GetCount();
		return true;
	}
	return false;
}