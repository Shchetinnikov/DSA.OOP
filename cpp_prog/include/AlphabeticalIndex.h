#pragma once

#include "IDictionary.h"
#include "BtIDictionary.h"
#include "Pair.h"
#include "PagedText.h"


/*
	Алфавитный указатель
*/


class AlphabeticalIndex
{
private:
	BtIDictionary<string, ListSequence<int>*>* data;
protected:
	// Формирует пары слово-страница
	ListSequence<Pair<string, int>*>* GetWordPagePairs(const PagedText& paged_text) const;
public:
	AlphabeticalIndex(const PagedText& paged_text);
public:
	int GetCount() const { return this->data->GetCount(); };
	ListSequence<int>* GetIndex(string word) const { return new ListSequence<int>(*this->data->Get(word)); }
	bool HasWord(string word) const { return this->data->ContainsKey(word); };
public:
	~AlphabeticalIndex()
	{
		delete data;
	}
};



AlphabeticalIndex::AlphabeticalIndex(const PagedText& paged_text)
{
	if (!paged_text.GetVolume())
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->data = new BtIDictionary<string, ListSequence<int>*>();

	// Формируем пары "слово-страница"
	ListSequence<Pair<string, int>*>* pairs_seq = this->GetWordPagePairs(paged_text);
	
	// Отслеживаем рассмотренные слова
	ListSequence<string>* index = new ListSequence<string>();
	{
		// Проходим по каждой паре
		Pair<string, int>* item;
		Pair<string, int>* pair;
		bool flag;
		for (int i = 0; i < pairs_seq->GetLength(); i++)
		{
			pair = pairs_seq->Get(i);

			// Проверка на наличие в индексе
			flag = false;
			for (int k = 0; k < index->GetLength(); k++)
			{
				if (pair->GetKey() == index->Get(k))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			
			// Формируем список страниц, где встречается слово
			ListSequence<int>* word_pages = new ListSequence<int>();
			for (int j = i; j < pairs_seq->GetLength(); j++)
			{
				item = pairs_seq->Get(j);

				if (pair->GetKey() == item->GetKey())
					word_pages->Append(item->GetValue());
			}

			// Удаляем повторы
			int k = 0;
			int index_size = word_pages->GetLength();
			for (int j = 0; j < index_size; j++, k++)
			{
				while (k + 1 < word_pages->GetLength() && word_pages->Get(k) == word_pages->Get(k + 1))
				{
					word_pages->RemoveAt(k + 1);
				}
				if (k + 1 < word_pages->GetLength() && j >= word_pages->GetLength())
					break;
			}
			this->data->Add(pair->GetKey(), word_pages);
			index->Append(pair->GetKey());
		}
	}
	delete index;
	delete pairs_seq;
};


// Определяем страницы слов
ListSequence<Pair<string, int>*>* AlphabeticalIndex::GetWordPagePairs(const PagedText & paged_text) const
{
	ListSequence<Pair<string, int>*>* pairs_seq = new ListSequence<Pair<string, int>*>();	// пары "слово-страница" 

	Pair<string, int>* pair;
	ArraySequence<string>* page;

	for (int i = 0; i < paged_text.GetVolume(); i++)
	{
		page = paged_text.GetPage(i + 1);
		for (int j = 0; j < page->GetLength(); j++)
		{
			pair = new Pair<string, int>(page->Get(j), i + 1);
			pairs_seq->Append(pair);
		}
	}
	return pairs_seq;
}