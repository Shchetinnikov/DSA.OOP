#pragma once

#include <sstream>
#include <exception>
#include <map>

using namespace std;

class Exception: public exception {
protected:
	string message;
	string file;
	int line;
public:
	string report()
	{
		ostringstream os;
		os << this->message << endl << "Hint: File " << this->file << ", Line " << this->line << endl;
		return os.str();
	}
};

class InvalidArguments : public Exception {
public:
	InvalidArguments(const string& message, const string& file, const int& line)
	{
		this->message = message;
		this->file = file;
		this->line = line;
	}
};

class IndexOutOfRange : public Exception {
public:
	IndexOutOfRange(const string& message, const string& file, const int& line)
	{
		this->message = message;
		this->file = file;
		this->line = line;
	}
};

class NoneValue : public Exception {
public:
	NoneValue(const string& message, const string& file, const int& line)
	{
		this->message = message;
		this->file = file;
		this->line = line;
	}
};