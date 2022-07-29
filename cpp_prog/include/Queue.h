#pragma once

#include <string>

#include "Exception.h"
#include "Sequence.h"
#include "ListSequence.h"
#include "ArraySequence.h"



template<class T>
class Queue
{
private:
	Sequence<T>* data;
public:
	Queue(T* items, const int count, string sequence = "list");
	Queue(const int count = 0, string sequence = "list");
	Queue(const Queue<T>& other, string sequence = "list");
public:
	T Back() const { return data->GetLast(); };
	T Front() const { return data->GetFirst(); };
	int Size() const { return data->GetLength(); };
	void Print() const;
public:
	T Pop();
	void Push(const T value);
	Queue<T>* Map(T (*mfun)(T)) const;
	Queue<T>* Where(bool (*wfun)(T)) const;
	T Reduce(T (*fun)(T, T), T startvalue) const;				
	Queue<T>* Concat(const Queue<T>& other) const;
	Queue<T>* GetSubQueue(const int start, const int end) const;
	int PosOfSubQueue(const Queue<T>& queue) const;
public:
	~Queue()
	{
		delete data;
	}
};


template<class T>
Queue<T> ::Queue(T* items, const int count, string sequence)
{
	if (!items || count <= 0 || (sequence != "array" && sequence != "list"))
		throw InvalidArguments();
	if (sequence == "list")
	{
		this->data = new ListSequence<T>(items, count);
	}
	else
	{
		this->data = new ArraySequence<T>(items, count);
	};
};

template<class T>
Queue<T> ::Queue(const int count, string sequence)
{
	int actualCount = count >= 0 ? count : 0;
	if (sequence == "list")
	{
		this->data = new ListSequence<T>(actualCount);
	}
	else
	{
		this->data = new ArraySequence<T>(actualCount);
	};
};

template<class T>
Queue<T> ::Queue(const Queue<T>& other, string sequence)
{
	if (!other.data->GetLength())
		throw InvalidArguments();

	if (sequence == "list")
	{
		this->data = new ListSequence<T>(other.data->GetLength());
	}
	else
	{
		this->data = new ArraySequence<T>(other.data->GetLength());
	};
	for (int i = 0; i < other.data->GetLength(); i++)
		this->data->Set(i, other.data->Get(i));
}

template <class T>
void Queue<T>::Print() const
{
	cout << "Current queue: ";
	for (int i = 0; i < this->data->GetLength(); i++)
		cout << this->data->Get(i) << " ";
	cout << endl;
}

template <class T>
T Queue<T> ::Pop()
{
	if (this->data->GetLength() == 0)
	{
		cout << "Queue is empty" << endl;
		return 0;
	}

	T element = this->data->GetFirst();
	this->data->RemoveAt(0);
	return element;
}

template <class T>
void Queue<T> ::Push(const T value)
{
	this->data->Append(value);
}

template <class T>
Queue<T>* Queue<T> ::Map(T(*mfun)(T)) const
{
	if (!this->data || !this->data->GetLength())
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***");
	Queue<T>* queue = new Queue<T>(*(this), "list");
	for (int i = 0; i < queue->data->GetLength(); i++)
	{
		queue->data->Set(i, mfun(this->data->Get(i)));
	};
	return queue;
}

template <class T>
Queue<T>* Queue<T> ::Where(bool (*wfun)(T)) const
{
	if (!this->data || !this->data->GetLength())
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***");
	Queue<T>* queue = new Queue<T>();
	for (int i = 0; i < this->data->GetLength(); i++)
		if (wfun(this->data->Get(i)))
		{
			queue->data->Append(this->data->Get(i));
		};
	return queue;
}

template <class T>
T Queue<T> ::Reduce(T(*rfun)(T, T), T startvalue) const
{
	if (!this->data || !this->data->GetLength())
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***");
	for (int i = this->data->GetLength() - 1; i >= 0; i--)
	{
		startvalue = rfun(this->data->Get(i), startvalue);
	};
	return startvalue;
}

template <class T>
Queue<T>* Queue<T> ::Concat(const Queue<T>& other) const
{
	if (!this->data || !this->data->GetLength() || !other.data->GetLength() || !other.data)
		throw IndexOutOfRange("***IndexError: array is empty or index is out of range***");
	Queue<T>* queue = new Queue<T>();
	for (int i = 0; i < this->data->GetLength(); i++)
	{
		queue->Push(this->data->Get(i));
	};
	for (int i = 0; i < other.data->GetLength(); i++)
	{
		queue->Push(other.data->Get(i));
	};
	return queue;
}

template <class T>
Queue<T>* Queue<T> ::GetSubQueue(const int start, const int end) const
{
	if (!this->data->GetLength() || !this->data || start < 0 || start > end || end >= this->data->GetLength())
		throw InvalidArguments();
	Queue<T>* subqueue = new Queue<T>;
	subqueue->data = this->data->GetSubsequence(start, end);
	return subqueue;
};

template <class T>
int Queue<T> ::PosOfSubQueue(const Queue<T>& queue) const
{
	if (!queue.data->GetLength() || !queue.data || !this->data->GetLength() || !this->data)
		throw InvalidArguments();
	if (queue.data->GetLength() > this->data->GetLength())
		throw NoneValue("***ValueError: there is not value of argument in the array***");
	Queue<T>* copy = new Queue<T>(*this);
	int index = -1;
	T element = queue.data->Get(0);
	for (int i = 0; i < copy->data->GetLength(); i++)
	{
		if (element == copy->data->Get(i))
		{
			index = i;
			if (queue.data->GetLength() > copy->data->GetLength() - i)
			{
				delete copy;
				throw NoneValue("***ValueError: there is not value of argument in the array***");
			};
			for (int k = 1; k < queue.data->GetLength(); k++)
			{
				if (queue.data->Get(k) != this->data->Get(k + i))
				{
					index = -1;
					break;
				};
			};
		};
	};
	if (index < 0)
	{
		delete copy;
		throw NoneValue("***ValueError: there is not value of argument in the array***");
	}
	else
		return index;
};


//////////////////////////////////////////////

/*

Функции, передаваемые соответственно reduce, map и where
(выполняемая операция каждой функции задана произволльно)

*/
template <class T>
T rfun(T value1, T value2)
{
	return value1 * 2 + value2;
}

template <class T>
T mfun(T value)
{
	return value * 3;
}

template <class T>
bool wfun(T value)
{
	if (value != "c")
		return true;
	return false;
}

