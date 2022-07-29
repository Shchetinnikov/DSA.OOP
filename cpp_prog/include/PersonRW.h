#pragma once

#include <fstream>
#include <random>

#include "IDictionary.h"
#include "BtIDictionary.h"
#include "Person.h"


using namespace std;



Person* PersonParser(string line)
{
    string subline;

    string FirstName = line.substr(0, line.find(';'));
    line.erase(0, line.find(';') + 1);

    string MiddleName = line.substr(0, line.find(';'));
    line.erase(0, line.find(';') + 1);

    string LastName = line.substr(0, line.find(';'));
    line.erase(0, line.find(';') + 1);

    subline = line.substr(0, line.find(';'));
    int BirthYear = std::stoi(subline);
    line.erase(0, line.find(';') + 1);

    subline = line.substr(0, line.find(';'));
    int Age = std::stoi(subline);
    line.erase(0, line.find(';') + 1);

    subline = line.substr(0, line.find(';'));
    int PassportID = std::stoi(subline);
    line.erase(0, line.find(';') + 1);

    return new Person(FirstName, MiddleName, LastName, BirthYear, Age, PassportID);
}


Sequence<Person*>* ReadPersons()
{
    string line;
    Sequence<Person*>* persons = new ListSequence<Person*>();
    Person* person;

    fstream file("persons.cvs", ios::in);

    getline(file, line);
    while (!file.eof())
    {
        getline(file, line);
        person = PersonParser(line);
        persons->Append(person);
    }
    file.close();

    return persons;
}


void WritePersons(const Sequence<Person*>* persons)
{
    string line;
    Person* person;

    fstream file("persons.cvs", ios::out);
    file << "FirstName" << ";" << "MiddleName" << ";" << "LastName" << ";" << "BirthYear" << ";" << "Age" << ";" << "PassportID";

    for (int i = 0; i < persons->GetLength(); i++)
    {
        file << endl;
        file << persons->Get(i)->GetFirstName() << ";";
        file << persons->Get(i)->GetMiddleName() << ";";
        file << persons->Get(i)->GetLastName() << ";";
        file << persons->Get(i)->GetBirthYear() << ";";
        file << persons->Get(i)->GetAge(2020) << ";";
        file << persons->Get(i)->GetPassportID();
    }   

    file.close();
}



Sequence<Person*>* PersonsGenerator()
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX));

    string first_names[32] = { "Vladimir", "Dmitriy", "Nikolay", "Vasiliy", "Ivan", "Peter", "Stanislav",
                            "Vitaliy", "Maxim", "Georgiy", "Victor", "German", "Rustam", "Boris", "Artem", "Arnold", "Anton",
                            "George", "Vladislav", "Svaytoslav", "Slava", "Alex", "Oleg", "Yuriy", "Evgeniy", "Arseny",
                            "Arkady", "Andrey", "Nikita", "Bohdan", "Denis", "Fedor"};

    string middle_names[16] = { "Nikolaevich", "Dmitrievich", "Olegovich", "Ivanovich", "Vladimirovich", "Svytoslavich", "Vasilievich", "Ivanovich",
                                "Petrovich", "Stanislavovich", "Vitalievich", "Victorovich", "Borisovich", "Olegovich", "Evgenievich", "Andetreevich"};
    string last_names[21] = { "Ivanov", "Petrov", "Sobolev", "Nikitin", "Fedorov", "Victorov", "Lisev", "Volkov", "Koshkin", "Dmitriev", "Artemov", 
                            "Borisov", "Moryashov", "Krasnov", "Eliseev", "Rogkov", "Rzhevskiy", "Okunevskiy", "Ribin", "Kamishev", "Nikulin"};
        
    int index;
    string FirstName;
    string MiddleName;
    string LastName;
    int BirthYear;
    int Age;
    int PassportID;
    Sequence<Person*>* persons = new ListSequence<Person*>();
    for (int i = 0; i < 10000; i++)
    {

        index = static_cast<int>(rand() * fraction * (31));
        FirstName = first_names[index];

        index = static_cast<int>(rand() * fraction * (15));
        MiddleName = middle_names[index];
        
        index = static_cast<int>(rand() * fraction * (20));
        LastName = last_names[index];

        BirthYear = static_cast<int>(rand() * fraction * (2020 - 1910) + 1910);
        Age = 2020 - BirthYear;
        PassportID = static_cast<int>(rand() * fraction * (100000));

        Person* person = new Person(FirstName, MiddleName, LastName, BirthYear, Age, PassportID);
        persons->Append(person);
    }
    return persons;
}