#pragma once

#include <iostream>
#include <windows.h>
#include <string>

#include "Exception.h"

using namespace std;

#define HCONSOLE GetStdHandle(STD_OUTPUT_HANDLE)

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


void AccessInput()
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Cyan));

	cout << endl << "> ";

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
}


void PrintHeading(const string& text)
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((White << 4) | Black));

	cout << text;

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));

	cout << endl;
}


void PrintConclusion(const string& text)
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | DarkGray));

	cerr << text;

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
	
	cout << endl;
}


void PrintSubheading(const string& text)
{
	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | Cyan));

	cout << endl << text;

	SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));

	cout << endl;
}
