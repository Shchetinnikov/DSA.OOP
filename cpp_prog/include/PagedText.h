#pragma once

#include "ArraySequence.h"
#include "ListSequence.h"

/*
	Разбиение текста на страницы
*/

class PagedText
{
private:
	ArraySequence<ArraySequence<string>*>* pages;
	int page_size;
	int first_page_size;
	int tenth_page_size;
protected:
	// Обрабатывает строку
	ListSequence<string>* GetWords(string line) const;
public:
	PagedText(const string& line, int page_size, int first_page_size = 0, int tenth_page_size = 0);
public:
	int GetPageSize() const { return this->page_size; };
	int GetFirstPageSize() const { return this->first_page_size; };
	int GetTenthPageSize() const { return this->tenth_page_size; };
	int GetVolume() const { return this->pages->GetLength(); };
	ArraySequence<string>* GetPage(const int page) const { return new ArraySequence<string>(*this->pages->Get(page - 1)); };
public:
	~PagedText()
	{
		delete pages;
	}
};



PagedText::PagedText(const string& line, int page_size, int first_page_size, int tenth_page_size)
{
	if (!line.size() || !page_size)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->pages = new ArraySequence<ArraySequence<string>*>();
	ArraySequence<string>* page = new ArraySequence<string>();
	this->pages->Append(page);

	this->page_size = page_size;
	
	this->first_page_size = first_page_size <= 0 ? page_size / 2 : first_page_size;
	this->tenth_page_size = tenth_page_size <= 0 ? page_size * 3 / 4 : tenth_page_size;

	// Выделяем слова по пропускам
	ListSequence<string>* words = this->GetWords(line);

	// Заполняем страницы
	string word;

	int current_fullness_c = 0;	// текущая заполненность страницы (в символах)
	int space_count = 0;		// кол-во пропусков для текущего кол-ва слов

	int current_page = 1;							// текущая страница
	int current_page_size = this->first_page_size;	// размер в символах текущей страницы

	int word_index = 0;

	while (word_index < words->GetLength())
	{
		word = words->Get(word_index);

		if (word.size() > page_size)
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

		// Добавить слово на текущую страницу, иначе создать новую страницу
		if (current_fullness_c + word.size() + space_count <= current_page_size)
		{
			this->pages->Get(current_page - 1)->Append(word);

			current_fullness_c += word.size();
			word_index++;
			space_count++;
		}
		else
		{
			page = new ArraySequence<string>();
			this->pages->Append(page);

			current_fullness_c = 0;
			space_count = 0;

			current_page++;
			if (current_page == 10)
				current_page_size = this->tenth_page_size;
			else
				current_page_size = this->page_size;
		}
	}
	delete words;
}


// Выделяем слова из строки
ListSequence<string>* PagedText::GetWords(string line) const
{
	ListSequence<string>* words = new ListSequence<string>();
	string word;

	int k = 0;
	int line_size = line.size();
	for (int i = 0; i < line_size; i++, k++)
	{
		if (line[k] == ' ')
		{
			if (k != 0)
			{
				word = line.substr(0, k);
				words->Append(word);
			}
			line.erase(0, k + 1);
			k = -1;
		}
	}
	if (line.size())
		words->Append(line);

	return words;
};