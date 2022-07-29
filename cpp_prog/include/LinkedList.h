#pragma once

#include "Exception.h"

template <typename T>
struct Node
{
	T data;
	bool dataCheck;
	Node<T>* pNext;
};

template <class T>
class LinkedList {
private:
	Node<T>* pFirst;
	int size;
public:
	LinkedList(T* items, const int count);
	LinkedList(const int size = 0);
	LinkedList(const LinkedList<T>& list);
public:
	int GetLength() const;
	T GetFirst() const;
	T GetLast() const;
	T Get(const int index) const;
	LinkedList<T>* GetSubList(const int startIndex, const int endIndex) const;
	bool HasValue(const int index) const;
	bool TryGetValue(const int index, T& value) const;
public:
	void Append(const T value);
	void Prepend(const T value);
	void Set(const int index, const T value);
	void InsertAt(const int index, const T value);
	void RemoveAt(const int index);
	void Remove(const T value);
	void RemoveAll(const T value);
	LinkedList<T>* Concat(const LinkedList<T>& list) const;
public:
	~LinkedList();
};


template <class T>
LinkedList<T> ::LinkedList(T* items, const int size)
{
	if (!items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	int actualSize = size >= 0 ? size : 0;
	this->size = actualSize;
	if (!actualSize)
	{
		this->pFirst = nullptr;
		return;
	};
	this->pFirst = new Node<T>;
	pFirst->data = items[0];
	pFirst->dataCheck = true;
	pFirst->pNext = nullptr;
	Node<T>* ptr1 = pFirst;
	for (int i = 1; i < actualSize; i++)
	{
		Node<T>* ptr2 = new Node<T>;
		ptr2->data = items[i];
		ptr2->dataCheck = true;
		ptr2->pNext = nullptr;
		ptr1->pNext = ptr2;
		ptr1 = ptr2;
	};
};

template <class T>
LinkedList<T> ::LinkedList(const int size)
{
	int actualSize = size >= 0 ? size : 0;
	this->size = actualSize;
	if (!actualSize)
	{
		this->pFirst = nullptr;
		return;
	};
	this->pFirst = new Node<T>;
	pFirst->dataCheck = false;
	pFirst->pNext = nullptr;
	Node<T>* ptr1 = pFirst;
	for (int i = 1; i < actualSize; i++)
	{
		Node<T>* ptr2 = new Node<T>;
		ptr2->dataCheck = false;
		ptr2->pNext = nullptr;
		ptr1->pNext = ptr2;
		ptr1 = ptr2;
	};
};

template <class T>
LinkedList<T> ::LinkedList(const LinkedList<T>& list)
{
	if (!list.size || !list.pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->size = list.size;
	Node<T>* ptr1 = list.pFirst;
	Node<T>* ptr2 = list.pFirst->pNext;

	this->pFirst = new Node<T>;
	if (ptr1->dataCheck)
	{
		this->pFirst->data = ptr1->data;
		this->pFirst->dataCheck = true;
	}
	else
	{
		this->pFirst->dataCheck = false;
	}
	this->pFirst->pNext = nullptr;
	Node<T>* ptr_1 = this->pFirst;
	Node<T>* ptr_2;
	for (int i = 1; i < list.size; i++)
	{
		ptr1 = ptr2;
		ptr2 = ptr2->pNext;
		ptr_2 = new Node<T>;
		if (ptr1->dataCheck)
		{
			ptr_2->data = ptr1->data;
			ptr_2->dataCheck = true;
		}
		else
		{
			ptr_2->dataCheck = false;
		};
		ptr_2->pNext = nullptr;
		ptr_1->pNext = ptr_2;
		ptr_1 = ptr_2;
	};
};

template <class T>
int LinkedList<T> ::GetLength() const
{
	return this->size;
};

template <class T>
T LinkedList<T> ::GetFirst() const
{
	if (!this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->pFirst->dataCheck)
		throw NoneValue("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	return this->pFirst->data;
};

template <class T>
T LinkedList<T> ::GetLast() const
{
	if (!this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	Node<T>* ptr = pFirst;
	for (int i = 1; i < size; i++)
	{
		ptr = ptr->pNext;
	};
	if (!ptr->dataCheck)
		throw NoneValue("***ValueError: value is not defined***", __FILE__, __LINE__);
	return ptr->data;
};

template <class T>
T LinkedList<T> ::Get(const int index) const
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	Node<T>* ptr = this->pFirst;
	for (int i = 1; i <= index; i++)
	{
		ptr = ptr->pNext;
	};
	if (!ptr->dataCheck)
		throw NoneValue("***ValueError: value is not defined***", __FILE__, __LINE__);
	return ptr->data;
};

template <class T>
bool LinkedList<T> ::HasValue(const int index) const
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	Node<T>* ptr = this->pFirst;
	for (int i = 1; i <= index; i++)
		ptr = ptr->pNext;
	if (ptr->dataCheck)
		return true;
	return false;
}

template <class T>
bool LinkedList<T> ::TryGetValue(const int index, T& value) const
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->HasValue(index))
		return false;
	value = this->Get(index);
	return true;
}

template <class T>
LinkedList<T>* LinkedList<T> ::GetSubList(const int startIndex, const int endIndex) const
{
	if (startIndex < 0 || startIndex > endIndex || endIndex >= this->size || !this->size || !this->pFirst)
		throw new IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	LinkedList<T>* sublist = new LinkedList<T>(endIndex - startIndex + 1);
	sublist->size = endIndex - startIndex + 1;
	for (int i = startIndex; i <= endIndex; i++)
	{
		sublist->Set(i - startIndex, this->Get(i));
	};
	return sublist;
};

template <class T>
void LinkedList<T> ::Prepend(const T value)
{
	if (this->size < 0)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->size)
	{
		pFirst = new Node<T>;
		pFirst->data = value;
		pFirst->dataCheck = true;
		pFirst->pNext = nullptr;
		this->size++;
		return;
	};
	this->size++;
	Node<T>* ptr = new Node<T>;
	ptr->data = value;
	ptr->dataCheck = true;
	ptr->pNext = this->pFirst;
	this->pFirst = ptr;
};

template <class T>
void LinkedList<T> ::Append(const T value)
{
	if (this->size < 0)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->size)
	{
		pFirst = new Node<T>;
		pFirst->data = value;
		pFirst->dataCheck = true;
		pFirst->pNext = nullptr;
		this->size++;
		return;
	}
	Node<T>* p = this->pFirst;
	Node<T>* ptr = new Node<T>;
	ptr->data = value;
	ptr->dataCheck = true;
	ptr->pNext = nullptr;
	for (int i = 1; i < this->size; i++)
	{
		p = p->pNext;
	};
	p->pNext = ptr;
	this->size++;
};

template <class T>
void LinkedList<T> ::Set(const int index, const T value)
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	Node<T>* ptr = this->pFirst;
	for (int i = 1; i <= index; i++)
	{
		ptr = ptr->pNext;
	};
	ptr->data = value;
	ptr->dataCheck = true;
};

template <class T>
void LinkedList<T> ::InsertAt(const int index, const T value)
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	this->size++;
	Node<T>* ptr = new Node<T>;
	if (index == 0)
	{
		ptr->data = value;
		ptr->dataCheck = true;
		ptr->pNext = this->pFirst;
		this->pFirst = ptr;
		return;
	};
	Node<T>* p = this->pFirst;
	for (int i = 1; i < index; i++)
	{
		p = p->pNext;
	};
	ptr->pNext = p->pNext;
	p->pNext = ptr;
	ptr->data = value;
	ptr->dataCheck = true;
};

template <class T>
void LinkedList<T> ::RemoveAt(const int index)
{
	if (index < 0 || index >= this->size || !this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	Node<T>* ptr = this->pFirst;
	if (index == 0)
	{
		this->pFirst = this->pFirst->pNext;
		delete ptr;
	}
	else
	{
		for (int i = 1; i < index; i++)
		{
			ptr = ptr->pNext;
		};
		Node<T>* p = ptr->pNext;
		ptr->pNext = p->pNext;
		delete p;
	};
	this->size--;
};

template <class T>
void LinkedList<T> ::Remove(T value)
{
	if (!this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	int flag = 0;
	Node<T>* ptr = this->pFirst;
	for (int i = 0; i < this->size; i++)
	{
		if (ptr->dataCheck && ptr->data == value)
		{
			flag = 1;
			this->RemoveAt(i);
			break;
		};
		ptr = ptr->pNext;
	};
	if (!flag)
		throw NoneValue("***ValueError: there is not value of argument in the list***", __FILE__, __LINE__);
};

template <class T>
void LinkedList<T> ::RemoveAll(T value)
{
	if (!this->size || !this->pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	int flag = 0;
	try {
		int num = this->size;
		for (int i = 0; i < num; i++)
		{
			Remove(value);
			flag = 1;
		};
	}
	catch (NoneValue& e)
	{
		if (!flag)
			throw NoneValue("***ValueError: there is not value of argument in the list***", __FILE__, __LINE__);
	}
};

template <class T>
LinkedList<T>* LinkedList<T> ::Concat(const LinkedList<T>& other) const
{
	if (!this->size || !this->pFirst || !other.size || !other.pFirst)
		throw IndexOutOfRange("***IndexError: list is empty or index is out of range***", __FILE__, __LINE__);
	LinkedList<T>* list = new LinkedList<T>(this->size + other.size);
	int index;
	for (index = 0; index < this->size; index++)
	{
		list->Set(index, this->Get(index));
	};
	for (int i = 0; i < other.size; i++)
	{
		list->Set(index, other.Get(i));
		index++;
	};
	return list;
};

template <class T>
LinkedList<T> :: ~LinkedList()
{
	Node<T>* ptr;
	for (int i = 0; i < this->size; i++)
	{
		ptr = pFirst->pNext;
		delete pFirst;
		pFirst = ptr;
	};
}
