#pragma once

#include "Exception.h"

template <class T>
class DynamicArray {
private:
	T* items;
	bool* itemsCheck;
	int size;
public:
	DynamicArray(T* items, const int count);
	DynamicArray(const int size = 0);
	DynamicArray(const DynamicArray<T>& array);
public:
	int GetSize() const;
	T Get(const int index) const;
	bool HasValue(const int index) const;
	bool TryGetValue(const int index, T& value) const;
public:
	void Set(const int index, const T value);
	void Resize(const int newSize);
public:
	~DynamicArray();
};


template <class T>
DynamicArray<T> ::DynamicArray(T* items, const int size)
{
	if (!items || size < 1)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	int actualSize = size;
	this->items = new T[actualSize];
	this->itemsCheck = new bool[actualSize];
	for (int i = 0; i < actualSize; i++)
	{
		this->items[i] = items[i];
		this->itemsCheck[i] = true;
	};
	this->size = actualSize;
};

template <class T>
DynamicArray<T> ::DynamicArray(const int size)
{
	if (size < 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->size = size;
	this->items = new T[size];
	this->itemsCheck = new bool[size];
	for (int i = 0; i < size; i++)
		this->itemsCheck[i] = false;
};

template <class T>
DynamicArray<T> ::DynamicArray(const DynamicArray<T>& array)
{
	if (array.size < 0 || !array.items)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	this->items = new T[array.size];
	this->itemsCheck = new bool[array.size];
	for (int i = 0; i < array.size; i++)
	{
		if (array.itemsCheck[i])
		{
			this->items[i] = array.items[i];
			this->itemsCheck[i] = true;
		}
		else { this->itemsCheck[i] = false; };
	};
	this->size = array.size;
};

template <class T>
int DynamicArray<T> ::GetSize() const
{
	return this->size;
}

template <class T>
T DynamicArray<T> ::Get(const int index) const
{
	if (index < 0 || index >= this->size || !this->size || !this->items)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	if (this->itemsCheck[index])
		return this->items[index];
	throw NoneValue("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
};

template <class T>
bool DynamicArray<T> ::HasValue(const int index) const
{
	if (index < 0 || index >= this->size || !this->size || !this->items)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	return this->itemsCheck[index];
};


template <class T>
bool DynamicArray<T> ::TryGetValue(const int index, T& value) const
{
	if (index < 0 || index >= this->size || !this->size || !this->items)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	if (!this->itemsCheck[index])
		return false;
	value = this->items[index];
	return true;
};

template <class T>
void DynamicArray<T> ::Set(const int index, const T value)
{
	if (index < 0 || index >= this->size || !this->size || !this->items)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);
	this->items[index] = value;
	this->itemsCheck[index] = true;
};

template <class T>
void DynamicArray<T> ::Resize(const int newSize)
{
	if (newSize <= 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	if (newSize == this->size)
		return;
	T* new_items = new T[newSize];
	bool* new_itemsCheck = new bool[newSize];
	if (newSize > this->size)
	{
		int i;
		for (i = 0; i < this->size; i++)
		{
			if (this->HasValue(i))
			{
				new_items[i] = this->items[i];
				new_itemsCheck[i] = true;
			}
			else
				new_itemsCheck[i] = false;
		};
		for (i; i < newSize; i++)
			new_itemsCheck[i] = false;
	}
	else
	{
		for (int i = 0; i < newSize; i++)
		{
			if (this->HasValue(i))
			{
				new_items[i] = this->items[i];
				new_itemsCheck[i] = true;
			}
			else
				new_itemsCheck[i] = false;
		};
	};
	this->size = newSize;
	delete[] this->items;
	delete[] this->itemsCheck;
	this->items = new_items;
	this->itemsCheck = new_itemsCheck;
}

template <class T>
DynamicArray<T> ::~DynamicArray()
{
	delete[] this->itemsCheck;
	delete[] this->items;
};