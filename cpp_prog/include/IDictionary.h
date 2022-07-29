#pragma once

template<class TKey, class TValue>
class IDictionary
{
public:
	virtual int GetCount() const = 0;
	virtual int GetCapacity() const = 0;
	virtual TValue Get(TKey key) const = 0;
	virtual bool ContainsKey(TKey key) const = 0;
public:
	virtual bool Add(TKey key, TValue item) = 0;
	virtual bool Remove(TKey key) = 0;
};