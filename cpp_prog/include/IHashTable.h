#pragma once

#include "IIterators.h"
#include "Pair.h"

template<class TKey, class TValue>
class IHashTable : public IIterable<Pair<TKey, TValue>*>
{
public:
	virtual int GetCount() const = 0;
	virtual int GetCapacity() const = 0;
	virtual TValue Get(TKey key) const = 0;
	virtual bool Find(TKey key) const = 0;
public:
	virtual bool Add(TKey key, TValue value) = 0;
	virtual bool Remove(TKey key) = 0;
	//virtual void Resize() = 0;
	virtual void Rehash() = 0;
};