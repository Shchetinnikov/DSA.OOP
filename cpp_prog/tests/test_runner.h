#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "Exception.h"
#include "ConsoleColors.h"

using namespace std;


class TestRunner {
public:
	template <class TestFunc >
	void RunTest(TestFunc func, const string& test_name)
	{	
		stringstream os;
		os << endl << test_name << " is running ...";
		PrintSubheading(os.str());
		os.str("");
		try {
			func();
			os << "Conclusion: " << test_name << " OK";
			PrintConclusion(os.str());
		}
		catch (runtime_error& e) {
			++fail_count;
			SetConsoleTextAttribute(HCONSOLE, (WORD)((Red << 4) | White));

			cerr << test_name << " fail: " << e.what() << endl;
			
			SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
		}
	}
	~TestRunner()
	{
		if (fail_count > 0) {
			SetConsoleTextAttribute(HCONSOLE, (WORD)((Red << 4) | White));
			
			cerr << endl << fail_count << " unit tests failed. Program is completed";
			
			SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));
			exit(1);
		}
	}
private:
	int fail_count = 0;
};




template <class T, class U>
void AssertEqual(const T& result, const U& expected, const string& file, const int& line) 
{
	if (result != expected) {
		ostringstream os;
		os << "Assertion failed: " << result << " != " << expected
			<< ". Hint: File " << file << ", Line " << line << endl;
		throw runtime_error(os.str());
	}
}


void BreakPointer(const string& file, const int& line)
{
	ostringstream os;
	os << "Assertion failed: Unexpectable behavior."
		<< " Hint: File " << __FILE__ << ", Line " << __LINE__ << endl;
	throw runtime_error(os.str());
}



template<class T>
void PrintData(const T& origin, const T& expected, const T& result)
{
	cout << "Initial data: " << origin << endl;
	cout << "Expected value: " << expected << endl;
	cout << "Function result: " << result << endl << endl;
}


template<class T>
void PrintData(const T& origin, const T& expected)
{
	cout << "Initial data: " << origin << endl;
	cout << "Expected value: " << expected << endl;
}


template<class T>
void PrintData(const T& result)
{
	cout << "Function result: " << result << endl << endl;
}

template<class T>
void PrintData(const T& origin, Exception& error)
{
	cout << "Initial data: " << origin << endl;
	cout << "--Exception catching--" << endl;
	cout << error.report() << endl;
}

template<class T>
void PrintData(const T& first, const T& second, const T& expected, const T& result)
{
	cout << "First object: " << first << endl;
	cout << "Second object: " << second << endl;
	cout << "Expected value: " << expected << endl;
	cout << "Function result: " << result << endl << endl;
}

template<class T>
void PrintData(const tuple<T*, T*>& pair, const T& expected)
{
	cout << "Initial data: " << *get<0>(pair) << endl;
	cout << "Target data: " << *get<1>(pair) << endl;
	cout << "Expected value: " << expected << endl;
}
