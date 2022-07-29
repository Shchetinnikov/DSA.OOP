#pragma once

#include <string>
#include <limits>
#include <random>

#include "Exception.h"
#include "Sequence.h"
#include "ConsoleColors.h"
#include "InterfaceText.h"

using namespace std;

int AskSequenceLength()
{
	int length;
	PrintSubheading("Input length of sequence:");
	AccessInput();
	cin >> length;
	if (length <= 0)
	{
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	return length;
}


template<class T>
void SetRange(T& vmin, T& vmax)
{
	PrintSubheading("Input value of generated range left border:");
	AccessInput();
	cin >> vmin;
	PrintSubheading("Input greatest value of generated range right border:");
	AccessInput();
	cin >> vmax;
	if (vmax < vmin)
	{
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


template<class T>
void Generate(Sequence<T>& input)
{
	T vmin;
	T vmax;
	int length;

	SetRange(vmin, vmax);
	length = AskSequenceLength();

	for (int i = 0; i < length; i++)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX));
		T item = static_cast<T>(rand() * fraction * (vmax - vmin) + vmin);
		input.Append(item);
	}
}


void ConstantSequence(Sequence<int>& input)
{
	int arr[10] = { 5, 0, 1, -1, -5, 2, 6, 5, -15, 15 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ConstantSequence(Sequence<float>& input)
{
	float arr[10] = { 0, 19.5, 7.97, -3.09, 4.57, 1, 20, -23.41, 7.97, -1 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ConstantSequence(Sequence<double>& input)
{
	double arr[10] = { 13.5113, 5636.29, 1933.85, 8087.6, 5850.51, 4799.25, 3503.56, 8959.73, 8228.58, 7466.3 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ConstantSequence(Sequence<char>& input)
{
	char arr[10] = { 'b', 'k', 'q', 'r', 'a', 'b', 'o', 't', 'm', 's' };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ConstantSequence(Sequence<string>& input)
{
	string arr[10] = { "bac", "bca", "as", "eq",  "abe",  "wadg",  "b",  "ABC",  "Bca",  "aBC" };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void GenerateSequence(Sequence<int>& input)
{
	Generate(input);
}


void GenerateSequence(Sequence<float>& input)
{
	Generate(input);
}


void GenerateSequence(Sequence<double>& input)
{
	Generate(input);
}


void GenerateSequence(Sequence<char>& input)
{
	char vmin;
	char vmax;
	int length;

	int index = 0;
	int index_min = 0;
	int index_max = 0;
	char arr[62] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	SetRange(vmin, vmax);
	length = AskSequenceLength();

	while (arr[index_min] != vmin)
	{
		index_min++;
	}

	while (arr[index_max] != vmax)
	{
		index_max++;
	}

	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX));
	for (int i = 0; i < length; i++)
	{
		index = static_cast<int>(rand() * fraction * (index_max - index_min) + index_min);
		input.Append(arr[index]);
	}
}

void GenerateSequence(Sequence<string>& input)
{
	int length;

	int index = 0;
	int index_min = 0;
	int index_max = 0;
	int rand_length = 0;
	char arr[62] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

	length = AskSequenceLength();

	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX));
	for (int i = 0; i < length; i++)
	{
		rand_length = static_cast<int>(rand() * fraction * (10 - 1) + 1);
		string word = "";
		for (int j = 0; j < rand_length; j++)
		{
			index = static_cast<int>(rand() * fraction * size(arr));
			word += arr[index];
		}
		input.Append(word);
	}
}


void DirectSortedSequence(Sequence<int>& input)
{
	int arr[10] = { -15, -5, -1, 0, 1, 2, 5, 5, 6, 15 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void DirectSortedSequence(Sequence<float>& input)
{
	float arr[10] = { -23.41, -3.09, -1, 0, 1, 4.57, 7.97, 7.97, 19.5, 20 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void DirectSortedSequence(Sequence<double>& input)
{
	double arr[10] = { 13.5113, 1933.85, 3503.56, 4799.25, 5636.29, 5850.51, 7466.3, 8087.6, 8228.58, 8959.73 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void DirectSortedSequence(Sequence<char>& input)
{
	char arr[10] = { 'a', 'b', 'b', 'k', 'm', 'o', 'p', 'q', 'r', 's' };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void DirectSortedSequence(Sequence<string>& input)
{
	string arr[10] = { "ABC",  "Bca", "aBC", "abe", "as", "b", "bac", "bca",  "eq", "wadg" };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ReverseSortedSequence(Sequence<int>& input)
{
	int arr[10] = { 15, 6, 5, 5, 2, 1, 0, -1, -5, -15 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ReverseSortedSequence(Sequence<float>& input)
{
	float arr[10] = { 20, 19.5, 7.97, 7.97, 4.57, 1, 9, -1, -3.09, -23.41 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ReverseSortedSequence(Sequence<double>& input)
{
	double arr[10] = { 8959.73, 8228.58, 8087.6, 7466.3, 5850.51, 5636.29, 4799.25, 3503.56, 1933.85,  13.5113 };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ReverseSortedSequence(Sequence<char>& input)
{
	char arr[10] = { 's', 'r', 'q', 'p', 'o', 'm', 'k', 'b', 'b', 'a' };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}


void ReverseSortedSequence(Sequence<string>& input)
{
	string arr[10] = { "wadg", "eq", "bca", "bac", "b","as", "abe",  "aBC", "Bca", "ABC" };
	for (int i = 0; i < size(arr); i++)
	{
		input.Append(arr[i]);
	}
}