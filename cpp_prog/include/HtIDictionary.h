#pragma once

#include "IDictionary.h"
#include "StaticHashTable.h"


template<class TKey, class TValue>
class HtIDictionary : public IDictionary<TKey, TValue>
{
private:
	StaticHashTable<TKey, TValue>* data;
	int count;
	int capacity;
public:
	HtIDictionary(const int capacity);
	HtIDictionary(const HtIDictionary<TKey, TValue>& idict);
public:
	virtual int GetCount() const override;
	virtual int GetCapacity() const override;
	virtual TValue Get(TKey key) const override;
	virtual bool ContainsKey(TKey key) const override;
public:
	virtual bool Add(TKey key, TValue item) override;
	virtual bool Remove(TKey key) override;
public:
	~HtIDictionary()
	{
		delete data;
	}
};


template<class TKey, class TValue>
HtIDictionary<TKey, TValue>::HtIDictionary(const int capacity)
{
	this->data = new StaticHashTable<TKey, TValue>(capacity);
}

template<class TKey, class TValue>
HtIDictionary<TKey, TValue>::HtIDictionary(const HtIDictionary<TKey, TValue>& idict)
{
	this->data = new StaticHashTable<TKey, TValue>(*idict.data);
}


template<class TKey, class TValue>
int HtIDictionary<TKey, TValue>::GetCount() const
{
	return this->count;
};

template<class TKey, class TValue>
int HtIDictionary<TKey, TValue>::GetCapacity() const
{
	return this->capacity;
};

template<class TKey, class TValue>
TValue HtIDictionary<TKey, TValue>::Get(TKey key) const
{
	return this->data->Get(key);
};

template<class TKey, class TValue>
bool HtIDictionary<TKey, TValue>::ContainsKey(TKey key) const
{
	return this->data->Find(key);
};



template<class TKey, class TValue>
bool HtIDictionary<TKey, TValue>::Add(TKey key, TValue item)
{
	return this->data->Add(key, item);
}


template<class TKey, class TValue>
bool HtIDictionary<TKey, TValue>::Remove(TKey key)
{
	return this->data->Remove(key);
}