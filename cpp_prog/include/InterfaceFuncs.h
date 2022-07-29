#pragma once
#include <string>

#include "Exception.h"
#include "ConsoleColors.h"
#include "Sequence.h"
#include "SequenceGenerator.h"
#include "tests.h"

#include "CompareSorters.h"
#include "ExecuteSorter.h"
#include "SearchingTasks.h"
#include "GraphTasks.h"

// InterfaceText
void TypesItems();
void SequenceItems();
void SequenceClasses();
void SequenceToCompareItems();


void Menu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		state = "SortMenu";
		break;
	case '2':
		state = "SearchMenu";
		break;
	case '3':
		state = "GraphMenu";
		break;
	case '4':
		TestAll();
		break;
	case '5':
		PrintConclusion("\nPROGRAM IS COMPLETED");
		exit(0);
		break;
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


void SortMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		state = "Sorters";
		break;
	case '2':
		Compare();
		break;
	case '3':
		state = "Menu";
		break;
	case '4':
		PrintConclusion("\nPROGRAM IS COMPLETED");
		exit(0);
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}

void SearchMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		AlphabeticalIndexTask();
		break;
	case '2':
		CacheTask();
		break;
	case '3':
		state = "Menu";
		break;
	case '4':
		PrintConclusion("\nPROGRAM IS COMPLETED");
		exit(0);
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}


void GraphMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		GraphTasks();
		break;
	case '3':
		state = "Menu";
		break;
	case '4':
		PrintConclusion("\nPROGRAM IS COMPLETED");
		exit(0);
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}

void SortersMenu(string& state, char choice)
{
	switch (choice)
	{
	case '1':
		ShakerSort();
		break;
	case '2':
		ShellSort();
		break;
	case '3':
		MergeSort();
		break;
	case '4':
		state = "SortMenu";
		break;
	case '5':
		PrintConclusion("\nPROGRAM IS COMPLETED");
		exit(0);
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}

}

char ChooseSequence()
{
	char choice = '0';
	SequenceClasses();
	cin >> choice;
	if (choice < '1' || choice > '2')
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	return choice;
}

char ChooseType()
{
	char choice;
	TypesItems();
	cin >> choice;
	if (choice < '1' || choice > '5')
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	return choice;
}


template<class T>
void GetSequence(Sequence<T>& input)
{
	SequenceItems();
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
		ConstantSequence(input);
		break;
	case '2':
		GenerateSequence(input);
		break;
	case '3':
		PrintSubheading("Warning: include the sequence in square brackets and separate every element by space");
		PrintSubheading("Warning: if type of elements is 'string', use escape character '\\0' at the end of element");
		AccessInput();
		cin >> input;
		break;
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	return;
}

template<class T>
void GetSequenceToCompare(Sequence<T>& input)
{
	SequenceToCompareItems();
	char choice;
	cin >> choice;
	switch (choice)
	{
	case '1':
		DirectSortedSequence(input);
		break;
	case '2':
		ReverseSortedSequence(input);
		break;
	case '3':
		ConstantSequence(input);
		break;
	case '4':
		GenerateSequence(input);
		break;
	default:
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	return;
}
