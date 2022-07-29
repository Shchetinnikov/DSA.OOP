#pragma once

#include "Exception.h"

class String
{
private:
	char* items;
	int count;
	int capacity;
public:
	String();
	String(const char* str);
	String(const String& str);
public:
	char Get(const int index) const;
	int GetLength() const { return this->count; }; 
	int GetCapacity() const { return this->capacity; };
	String GetSubstring(const int start, const int end) const;
	int GetPos(char item) const;
public:
	String operator+ (const String& str);
	//String operator* (const int value);
	String operator= (const String& str);
	/*bool operator== (const String& str);
	bool operator!= (const String& str);*/
	/*String operator()();*/
	friend ostream& operator<< (ostream &out, const String& str);
public:
	~String()
	{	
		if (this->items)
			delete[] this->items;
	};
};



String::String()
{
	this->items = new char[1];
	this->items[0] = '\0';
	this->count = 0;
	this->capacity = 1;
};


String :: String(const char* str)
{
	if (!str)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	int capacity = 0;
	do
	{
		capacity++;
	} while (str[capacity - 1] != '\0');

	this->items= new char[capacity];
	for (int index = 0; index < capacity; index++)
	{
		this->items[index] = str[index];
	};
	this->capacity = capacity;
	this->count = capacity- 1;
};



String :: String(const String& str)
{
	if (!str.count || !str.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->count = str.count;
	this->capacity = str.capacity;
	this->items = new char[this->capacity];

	for (int i = 0; i < this->capacity; i++)
		this->items[i] = str.items[i];
};


char String :: Get(const int index) const
{
	if (index < 0 || index >= this->count || this->count <= 0 || !this->items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	return this->items[index];
}



String String :: GetSubstring(const int start, const int end) const
{
	if (start < 0 || end >= this->count || start > end)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);

	int i;
	int index = start;
	char* str = new char[end - start + 2];
	
	for (i = 0; index <= end; index++, i++)
	{
		str[i] = this->items[index];
	}
	str[i] = '\0';

	String output(str);

	delete[] str;
	return output;
};


int String :: GetPos(char item) const
{
	int index;
	for(index = 0; index < this->count && this->items[index] != item; index++) {}

	if (this->items[index] == item)
		return index;
	else
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***", __FILE__, __LINE__);

};



String String :: operator+ (const String& str)
{
	if (!this->count || !this->items || !str.count || !str.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	
	String concat;
	delete[] concat.items;

	concat.count = this->count + str.count;
	concat.capacity = this->capacity + str.count;
	concat.items = new char[this->capacity + str.count];

	int index;
	for (index = 0; index < this->count; index++)
	{
		concat.items[index] = this->items[index];
	};
	for (int i = 0; i < str.count; i++, index++)
	{
		concat.items[index] = str.items[i];
	};
	concat.items[index] = '\0';

	return concat;
};



//String String :: operator* (const int value)
//{
//	if (value <= 0)
//		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
//	
//	String result;
//	delete[] result.items;
//
//	for (int i = 0; i < value; i++)
//	{
//		result = result + *this;
//	};
//
//	return result;
//};



String String :: operator= (const String& str)
{
	if (!this->count || !this->items || !str.count || !str.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	delete[] this->items;

	this->capacity = str.capacity;
	this->count = str.count;
	this->items = new char[str.capacity];

	for (int i = 0; i < str.capacity; i++)
		this->items[i] = str.items[i];

	return *this;
};


//bool String :: operator== (const String& str2)
//{
//	if (!this->length || !this->items || !str2.length || !str2.items)
//		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
//	if (this->length == str2.length)
//	{
//		for (int i = 0; i < this->length; i++)
//		{
//			if (this->items[i] != str2.items[i])
//				return false;
//		};
//	}
//	else
//		return false;
//	return true;
//};
//
//bool String :: operator!= (const String& str2)
//{
//	if (!this->length || !this->items || !str2.length || !str2.items)
//		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
//	if (this->length == str2.length)
//	{
//		for (int i = 0; i < this->length; i++)
//		{
//			if (this->items[i] != str2.items[i])
//				return true;
//		};
//	}
//	else
//		return true;
//	return false;
//};
//
//String String :: operator() ()
//{
//	return *this;
//}

ostream& operator<< (ostream& out, const String& str) 
{
	if (!str.count || !str.items)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	
	for (int i = 0; i < str.capacity; i++)
		out << str.items[i];

	return out;
};