#pragma once

template<class T>
class SortedSequence
{
protected:
	int length;
public:
	int GetLength() const;
	bool IsEmpty() const;
public:
	virtual T Get(int index) const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual int IndexOf(T element) const = 0;
	virtual SortedSequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
public:
	virtual void Set(int index, T item) = 0;
	virtual void Add(T item) = 0;
	virtual bool Remove(T item) = 0;
};



template<class T>
class SbtSortedSequence : SortedSequence<T>
{
protected:
	StitchedBinaryTree<T>* data;
public:
	BtSortedSequence(int (*)(T, T));
public:
	int GetLength() const
	{
		return this->data->GetCount();
	}
	bool IsEmpty() const;
public:
	virtual T Get(int index) const;
	virtual T GetFirst() const;

};