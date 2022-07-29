#pragma once

#include "IIterators.h"
#include "Pair.h"

template<class T>
class ISet : public IIterable<T>
{
public:
	virtual int GetCount() const = 0;
	virtual bool IsEmpty() const;
	virtual bool HasElement(T element) const = 0;
public:
	virtual void Union(ISet<T>* set) = 0;
	virtual void Intersect(ISet<T>* set) = 0;
	virtual void Except(ISet<T>* set) = 0;
	virtual ISet<Pair<T, T>*>* Product(ISet<T>* set) = 0;
};

template<class T>
bool ISet<T>::IsEmpty() const
{
	return this->GetCount() == 0;
}