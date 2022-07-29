#pragma once

#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "Exception.h"
#include "ConsoleColors.h"
#include "InterfaceFuncs.h"

using namespace std;

using ExecuteFunc = void (*)(string&, char);
using ShowInfFunc = void (*)();

void ShowCurrentMenu(string& state);
void ShowMenu();
void ShowSortMenu();
void ShowSearchMenu();
void ShowSortersMenu();
void ShowGraphMenu();


map<string, tuple<ShowInfFunc, ExecuteFunc>> allfuncs =
{
	{"Menu", {ShowMenu, Menu}},
	{"SortMenu", {ShowSortMenu, SortMenu}},
	{"SearchMenu", {ShowSearchMenu, SearchMenu}},
	{"Sorters", {ShowSortersMenu, SortersMenu}},
	{"GraphMenu", {ShowGraphMenu, GraphMenu}}
};


void ShowCurrentMenu(string& state)
{
	if (state.size() == 0)
	{
		ShowMenu();
		state = "Menu";
	}
	else
	{
		get<0>(allfuncs[state])();
	}
}


void ShowMenu()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Blue));

	cout << "\n==========*MENU*==========" << endl;
	cout << " Program main menu" << endl;
	cout << " Choose one of the item:" << endl;
	cout << "1. Sorting tasks" << endl;
	cout << "2. Searching tasks" << endl;
	cout << "3. Graph tasks" << endl;
	cout << "4. Test program" << endl;
	cout << "5. Exit" << endl;
	AccessInput();

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
};


void ShowSortMenu()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Blue));

	cout << "\n==========*SORT MENU*==========" << endl;
	cout << " You've chosen the item 'Sorting tasks'" << endl;
	cout << " Choose one of the item:" << endl;
	cout << "1. Sorters" << endl;
	cout << "2. Compare sorters" << endl;
	cout << "3. Back" << endl;
	cout << "4. Exit" << endl;
	AccessInput();

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
};


void ShowSearchMenu()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Blue));

	cout << "\n==========*SEARCH MENU*==========" << endl;
	cout << " You've chosen the item 'Searching tasks'" << endl;
	cout << " Choose one of the task:" << endl;
	cout << "1. Alphabetical Index" << endl;
	cout << "2. Cache" << endl;
	cout << "3. Back" << endl;
	cout << "4. Exit" << endl;
	AccessInput();

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
}


void ShowGraphMenu()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Blue));

	cout << "\n==========*GRAPH MENU*==========" << endl;
	cout << " You've chosen the item 'Graph tasks'" << endl;
	cout << " Choose one of the task:" << endl;
	cout << "1. Shortest route" << endl;
	cout << "3. Back" << endl;
	cout << "4. Exit" << endl;
	AccessInput();

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
}


void ShowSortersMenu()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Blue));

	cout << "\n\n==========*SORTERS MENU*==========" << endl;
	cout << " You've chosen the item 'Sorters'" << endl;
	cout << " Choose one of algorithm of sorting:" << endl;
	cout << "1. ShakerSorter" << endl;
	cout << "2. ShellSorter" << endl;
	cout << "3. MergeSorter" << endl;
	cout << "4. Back" << endl;
	cout << "5. Exit" << endl;
	AccessInput();

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
}

void SequenceClasses()
{
	cout << endl << " Choose which sequence to use:" << endl;
	cout << "1. Array Sequence" << endl;
	cout << "2. List Sequence" << endl;
	AccessInput();
}

void TypesItems()
{
	cout << endl << " Choose which type to use:" << endl;
	cout << "1. Integer" << endl;
	cout << "2. Float" << endl;
	cout << "3. Double" << endl;
	cout << "4. Char" << endl;
	cout << "5. String" << endl;
	AccessInput();
}


void SorterItems()
{

	cout << " Choose two different items:" << endl;
	cout << "1. ShakerSorter" << endl;
	cout << "2. ShellSorter" << endl;
	cout << "3. MergeSorter" << endl;

	AccessInput();
}


void SequenceItems()
{
	cout << endl << " Choose which sequence to use:" << endl;
	cout << "1. Constant sequence" << endl;
	cout << "2. Generate sequence" << endl;
	cout << "3. Input sequence" << endl;
	AccessInput();
}


void SequenceToCompareItems()
{
	cout << endl << " Choose which sequence to use:" << endl;
	cout << "1. Direct sorted" << endl;
	cout << "2. Reverse sorted" << endl;
	cout << "3. None sorted" << endl;
	cout << "4. Generate sequence" << endl;
	AccessInput();
}


template<class T>
void PrintSequence(const Sequence<T>& origin, const string& text)
{
	cout << text << origin << endl;
}


int AskOrder()
{
	char answer;
	cout << endl << " How would you like to sort the sequence:" << endl;
	cout << "0 - descending order" << endl;
	cout << "1 - ascending order" << endl;
	AccessInput();
	cin >> answer;
	if (answer == '0')
		return 0;
	if (answer == '1')
		return 1;
	throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
}
