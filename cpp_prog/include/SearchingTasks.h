#pragma once

#include "AlphabeticalIndex.h"
#include "Cache.h"

#include "Person.h"
#include "PersonRW.h"

using namespace std;


ListSequence<string>* GetUniqueWords(string line)
{
	ListSequence<string>* words = new ListSequence<string>();
	{
		// Выделяем уникальные слова из строки
		string word;
		bool flag;

		int k = 0;
		int line_size = line.size();
		for (int i = 0; i < line_size; i++, k++)
		{
			if (line[k] == ' ')
			{
				if (k != 0)
				{
					word = line.substr(0, k);
					flag = false;

					for (int j = 0; j < words->GetLength(); j++)
					{
						if (words->Get(j) == word)
						{
							flag = true;
							break;
						}
					}

					if (!flag)
						words->Append(word);
				}
				line.erase(0, k + 1);
				k = -1;
			}
		}

		flag = false;
		for (int j = 0; j < words->GetLength(); j++)
			if (words->Get(j) == line)
			{
				flag = true;
				break;
			}

		if (!flag && line.size())
			words->Append(line);
	}
	return words;
}



void AlphabeticalIndexTask()
{
	string line;
	int page_size;

	getline(cin, line);
	cout << "Input the string and page size by enter:" << endl;

	getline(cin, line);
	cin >> page_size;

	PagedText* paged_text = new PagedText(line, page_size);
	AlphabeticalIndex* index = new AlphabeticalIndex(*paged_text);

	//Вывод полученного алфавитного указателя
	Sequence<string>* words = GetUniqueWords(line);

	cout << "UNIQUE WORDS: ";
	for (int i = 0; i < words->GetLength(); i++)
	{
		cout <<words->Get(i) << " ";
	}

	cout << endl << endl;
	cout << "*** Alphabetical Index ***" << endl;
	for (int i = 0; i < words->GetLength(); i++)
	{
		cout << "{ " << words->Get(i) << ", " << *index->GetIndex(words->Get(i)) << " }" << endl;
	}
	delete paged_text;
	delete index;
	delete words;
}


void CacheTask()
{
	Sequence<int>* requests = new ListSequence<int>();

	Person* person;
	Sequence<Person*>* persons = ReadPersons();

	int capacity;
	cout << "Input capacity of the cache:" << endl;
	cin >> capacity;

	Cache<int, Person*>* cache = new Cache<int, Person*>(capacity, PriorityComparer);

	int flag;
	int index;
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX));
	for (int i = 0; i < persons->GetLength() - 9000; i++)
	{
		index = static_cast<int>(rand() * fraction * (persons->GetLength() - 1));
		person = persons->Get(index);

		if (!cache->Find(person->GetPassportID()))
		{
			cache->Add(person->GetPassportID(), person);
		}
		else
		{
			cache->Get(person->GetPassportID());
		}

		flag = false;
		for (int j = 0; j < requests->GetLength(); j++)
		{
			if (person->GetPassportID() == requests->Get(j))
			{
				flag = true;
				break;
			}
		}
		if(!flag)
			requests->Append(person->GetPassportID());
	}
	
	cout << "UNIQUE REQUESTS: " << requests->GetLength() << endl;
	cout << cache->GetCapacity() << endl;
	cout << cache->GetCount() << endl;
	for (int i = 0; i < requests->GetLength(); i++)
	{
		if (cache->Find(requests->Get(i)))
		{
			cout << *cache->Get(requests->Get(i)) << endl;
		}
	}
	delete requests;
	delete cache;
	delete persons;
}