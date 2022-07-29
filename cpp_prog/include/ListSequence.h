#pragma once

#include "Exception.h"
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class ListSequence : public Sequence<T> {
private:
	LinkedList<T>* data;
	int count;
public:
	ListSequence(T* items, const int count);
	ListSequence(const int count = 0);
	ListSequence(const ListSequence<T>& other);
public:
	virtual int GetCapacity() const override
	{
		return this->data->GetLength();
	}
	virtual int GetLength() const override { return this->count; };
	virtual T GetFirst() const override;
	virtual T GetLast() const override;
	virtual T Get(const int i) const override;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const override;
	bool HasValue(const int index) const;
	bool TryGetValue(const int index, T& value) const;
public:
	virtual void Append(const T value) override;
	virtual void Prepend(const T value) override;
	virtual void Set(const int index, const T value) override;
	virtual void InsertAt(const int index, const T value) override;
	virtual void RemoveAt(const int index) override;
	virtual void Remove(const T value) override;
	virtual void RemoveAll(const T value) override;
	virtual Sequence<T>* Copy() const override;
	virtual Sequence<T>* Concat(const Sequence<T>& other) const override;
	virtual void CopyTo(Sequence<T>* target, const int startIndex) const override;
public:
	virtual IIterator<T>* GetIterator() override
	{
		return nullptr;
	}
public:
	~ListSequence();
};


template <class T>
ListSequence<T> ::ListSequence(T* items, const int count)
{
	if (!items || count <= 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->count = count;
	this->data = new LinkedList<T>(items, count);
};

template <class T>
ListSequence<T> ::ListSequence(const int count)
{
	int actualCount = count >= 0 ? count : 0;
	this->count = actualCount;
	this->data = new LinkedList<T>(actualCount);
};

template <class T>
ListSequence<T> ::ListSequence(const ListSequence<T>& other)
{
	if (!other.count || !other.data)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->count = other.count;
	this->data = new LinkedList<T>(*(other.data));
};

template <class T> T
ListSequence<T> ::GetFirst() const
{
	if (!this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	return this->data->GetFirst();
};

template <class T>
T ListSequence<T> ::GetLast() const
{
	if (!this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	return this->data->GetLast();
};

template <class T>
T ListSequence<T> ::Get(const int index) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	return this->data->Get(index);
};

template <class T>
bool ListSequence<T> ::HasValue(const int index) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	return this->data->HasValue(index);
}

template <class T>
bool ListSequence<T> ::TryGetValue(const int index, T& value) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->data->HasValue(index))
		return false;
	value = this->data->Get(index);
	return true;
}

template <class T>
Sequence<T>* ListSequence<T> ::GetSubsequence(const int start, const int end) const
{
	if (start < 0 || start > end || end >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	ListSequence<T>* subseq = new ListSequence<T>(end - start + 1);
	subseq->count = end - start + 1;
	for (int i = start; i <= end; i++)
	{
		subseq->Set(i - start, this->data->Get(i));
	};
	return subseq;
};

template <class T>
void ListSequence<T> ::Prepend(const T value)
{
	if (this->count < 0)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->count++;
	this->data->Prepend(value);
};

template <class T>
void ListSequence<T> ::Append(const T value)
{
	if (this->count < 0)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->count++;
	this->data->Append(value);
};

template <class T>
void ListSequence<T> ::Set(const int index, const T value)
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->data->Set(index, value);
};

template <class T>
void ListSequence<T> ::InsertAt(const int index, T value)
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->count++;
	this->data->InsertAt(index, value);
};

template <class T>
void ListSequence<T> ::RemoveAt(const int index)
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->data->RemoveAt(index);
	this->count = this->data->GetLength();
};

template <class T>
void ListSequence<T> ::Remove(T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->data->Remove(value);
	this->count = this->data->GetLength();
};

template <class T>
void ListSequence<T> ::RemoveAll(T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->data->RemoveAll(value);
	this->count = this->data->GetLength();
};

template <class T>
Sequence<T>* ListSequence<T> ::Copy() const
{
	Sequence<T>* seq = new ListSequence<T>(*this);
	return seq;
};

template <class T>
Sequence<T>* ListSequence<T> ::Concat(const Sequence<T>& other) const
{
	if (!this->count || !this->data || !other.GetLength())
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	ListSequence<T>* seq = new ListSequence<T>(this->count + other.GetLength());
	seq->count = this->count + other.GetLength();
	int index = 0;
	for (index; index < this->count; index++)
	{
		seq->Set(index, this->data->Get(index));
	};
	for (int i = 0; i < other.GetLength(); i++)
	{
		seq->Set(index, other.Get(i));
		index++;
	};
	return seq;
};

template <class T>
void ListSequence<T> ::CopyTo(Sequence<T>* target, int startIndex) const
{
	if (!target->GetLength() || !target || startIndex < 0 || startIndex >= target->GetLength())
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	for (int i = startIndex, index = 0; i < target->GetLength() && index < this->GetLength(); i++, index++)
	{
		target->Set(i, this->data->Get(index));
	};
}

template <class T>
ListSequence<T> ::~ListSequence()
{
	delete this->data;
};
