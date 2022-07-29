#pragma once

#include <string>

#include "Sequence.h"
#include "Exception.h"

using namespace std;


class Person
{
private:
	string FirstName;
	string MiddleName;
	string LastName;
	int BirthYear;
	int Age;
	int PassportID;
public:
	Person(string FirstName, string MiddleName, string LastName, int BirthYear, int Age, int PassportID)
	{
		this->FirstName = FirstName;
		this->MiddleName = MiddleName;
		this->LastName = LastName;
		this->BirthYear = BirthYear;
		this->Age = Age;
		this->PassportID = PassportID;
	}
public:
	string GetFirstName() const { return this->FirstName; };
	string GetMiddleName() const { return this->MiddleName; };
	string GetLastName() const { return this->LastName; }
	string GetFullName() const 
	{ 
		return this->LastName + " " + this->FirstName + " " + this->MiddleName;
	};
	string GetFIO() const
	{
		return this->LastName + " " + this->FirstName[0] + "." + this->MiddleName[0] + ".";
	}; 
	int GetBirthYear() const
	{
		return this->BirthYear;
	};
	int GetAge(int year)
	{
		if (year < this->BirthYear)
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		this->Age = year - this->BirthYear;
		return this->Age;
	};
	int GetPassportID() const { return this->PassportID; };
public:
	friend ostream& operator<< (ostream& out, const Person& person);
};


ostream& operator<< (ostream& out, const Person& person)
{
	// Сделать json-вывод с использованием библиотеки 
	out << "{" << endl;
	out << "\t" << "First name: " << person.FirstName << "," << endl;
	out << "\t" << "Middle name: " << person.MiddleName << "," << endl;
	out << "\t" << "Last name: " << person.LastName << "," << endl;
	out << "\t" << "Birth year: " << person.BirthYear << "," << endl;
	out << "\t" << "Age: " << person.Age << "," << endl;
	out << "\t" << "PassportID: " << person.PassportID << "" << endl;
	out << "}" << endl;
	return out;
}