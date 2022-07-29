#pragma once

#include "IHashTable.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Pair.h"

/*
	Стандартная реализация хеш-таблицы
	Решение коллизий: двойное хеширование
*/

template<class TKey, class TValue>
class HashTable : IHashTable<TKey, TValue>
{
private:
	int default_capacity = 2;
	int param_p = 4;
	int param_q = 2;
private:
	struct Record
	{
		TKey key;
		TValue data;
		bool status;
	};
private:
	ArraySequence<Record*>* data;
	int capacity;
	int count;
protected:
	// Хеш-функция
	int GetHashCode(const TKey key, const int step = 0) const
	{
		int hash_1 = key % capacity;
		int hash_2 = 1 + key % (capacity - 1);
		return (hash_1 + step * hash_2) % capacity;
	}
private:
	class HashTableIterator: public IIterator<Pair<TKey,TValue>*>
	{
	private:
		HashTable<TKey, TValue>* data;
		IIterator<Record*>* iterator;
		int currentIndex;
	public:
		HashTableIterator(HashTable<TKey, TValue>* hash_table)
		{
			this->data = hash_table;
			this->iterator = hash_table->data->GetIterator();
			this->currentIndex = 0;
		}
	public:
		virtual Pair<TKey, TValue>* GetValue() const override 
		{ 
			TValue value = this->iterator->GetValue()->data;
			TKey key = this->iterator->GetValue()->key;
			Pair<TKey, TValue>* pair = new Pair<TKey, TValue>(key, value);
			return pair; 
		}
		virtual IIterator<Pair<TKey, TValue>*>* Next() override
		{
			this->iterator->Next();
			this->currentIndex++;
			return this;
		}
		virtual bool HasNext() override { return this->iterator->HasNext(); }
		virtual bool HasValue() override { return this->iterator->HasValue(); }
	public:
		virtual IIterator<Pair<TKey, TValue>*>* Prev() override
		{
			this->iterator->Prev();
			this->currentIndex--;
			return this;
		}
		virtual bool HasPrev() override { return this->iterator->HasPrev(); }
	};
public:
	HashTable(const int capacity = 0);
	HashTable(const HashTable& hash_table);
public:
	virtual int GetCount() const override;
	virtual int GetCapacity() const override;
	virtual TValue Get(TKey key) const override;
	virtual bool Find(TKey key) const override;
public:
	virtual bool Add(TKey key, TValue value) override;
	virtual bool Remove(TKey key) override;
	virtual void Rehash() override;
	void Resize();
public:
	virtual IIterator<Pair<TKey, TValue>*>* GetIterator() override
	{
		return new HashTableIterator(this);
	}
public:
	~HashTable()
	{
		delete data;
	}
};


template<class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(const int capacity) : count(0)
{
	if (capacity == 0)
	{
		this->capacity = this->default_capacity;
		this->data = new ArraySequence<Record*>(this->default_capacity);
	}
	else
	{

		int digit = capacity;

		if (digit > 1)
		{
			while (digit % 2 == 0 && digit != 1)
			{
				digit /= 2;
			}
		}
		else
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

		if (digit != 1)
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

		this->capacity = capacity;
		this->data = new ArraySequence<Record*>(capacity);
	}
}


template<class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(const HashTable& hash_table)
{
	int digit = hash_table.capacity;

	if (digit > 1)
	{
		while (digit % 2 == 0 && digit != 1)
		{
			digit /= 2;
		}
	}
	else
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	if (digit != 1)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	this->count = hash_table.count;
	this->capacity = hash_table.capacity;
	this->data = new ArraySequence<Record*>(*hash_table.data);
}



template<class TKey, class TValue>
int HashTable<TKey, TValue>::GetCount() const
{
	return this->count;
};


template<class TKey, class TValue>
int HashTable<TKey, TValue>::GetCapacity() const
{
	return this->capacity;
};


template<class TKey, class TValue>
TValue HashTable<TKey, TValue>::Get(TKey key) const
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 0; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key && record->status)
			break;

		index = this->GetHashCode(key, i + 1);
	}

	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (!this->data->HasValue(index))
			throw NoneValue("***ValueError: there is not value of argument in the hash table***", __FILE__, __LINE__);
		
		if (i >= this->data->GetLength())
		{
			for (index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
			{
				record = this->data->Get(index);
				if (record->key == key && record->status)
					break;
			};
			if (i < this->data->GetLength() && this->data->HasValue(index))
				return record->data;
		}
		throw NoneValue("***ValueError: there is not value of argument in the hash table***", __FILE__, __LINE__);
	}
	else
		return record->data;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Find(TKey key) const
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 0; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key && record->status)
			break;

		index = this->GetHashCode(key, i + 1);
	}

	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (!this->data->HasValue(index))
			return false;

		if (i >= this->data->GetLength())
		{
			for (index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
			{
				record = this->data->Get(index);
				if (record->key == key && record->status)
					break;
			};
			if (i < this->data->GetLength() && this->data->HasValue(index))
				return true;
		}
	}
	else
		return true;
	
	return false;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Add(TKey key, TValue value)
{
	Record* new_record = new Record({ key, value, true });	
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 0; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i + 1);
	}


	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (!this->data->HasValue(index))
		{
			this->count++;
			this->data->Set(index, new_record);
			this->Resize();
			return true;
		}

		for (index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
		{};

		if (index < this->data->GetLength() && !this->data->HasValue(index))
		{
			this->count++;
			this->data->Set(index, new_record);
			this->Resize();
			return true;
		}
	}
	else
	{
		delete new_record;
		if (!record->status)
		{
			this->count++;
			record->status = true;
			this->Resize();
			return true;
		}
	}
	
	return false;
}


template<class TKey, class TValue>
bool HashTable<TKey, TValue>::Remove(TKey key)
{
	int index = this->GetHashCode(key);
	Record* record = nullptr;
	int i;

	for (i = 0; i < this->data->GetLength() && this->data->HasValue(index); i++)
	{
		record = this->data->Get(index);
		if (record->key == key)
			break;

		index = this->GetHashCode(key, i + 1);
	}

	if (!(i < this->data->GetLength() && this->data->HasValue(index)))
	{
		if (!this->data->HasValue(index))
			return false;

		for (index = 0; index < this->data->GetLength() && this->data->HasValue(index); index++)
		{
			record = this->data->Get(index);
			if (record->key == key)
				break;
		};

		if (index < this->data->GetLength() && this->data->HasValue(index))
		{
			if (record->status)
			{
				this->count--;
				record->status = false;
			}
			this->Resize();
			return true;
		}
	}
	else
	{
		if (record->status)
		{
			this->count--;
			record->status = false;
		}
		this->Resize();
		return true;
	}

	return false;
}


template<class TKey, class TValue>
void HashTable<TKey, TValue>::Resize()
{
	if (this->count <= this->capacity / this->param_p)
	{
		this->capacity = this->capacity / this->param_q;
		this->Rehash();
	}
	else
	{
		if (this->count == this->capacity)
		{
			this->capacity = this->capacity * this->param_q;
			this->Rehash();
		}
	}
}


template<class TKey, class TValue>
void HashTable<TKey, TValue>::Rehash()
{
	this->count = 0;
	ArraySequence<Record*>* new_data = new ArraySequence<Record*>(this->capacity);

	Record* record = nullptr;
	Record* new_record = nullptr;
	int index;
	TKey key;

	for (int i = 0; i < this->data->GetLength(); i++)
	{
		if (this->data->HasValue(i) && this->data->Get(i)->status)
		{
			record = this->data->Get(i);
			key = record->key;

			index = this->GetHashCode(key);
			int j;

			for (j = 0; j < new_data->GetLength() && new_data->HasValue(index); j++)
			{
				new_record = new_data->Get(index);
				if (new_record->key == key)
					break;

				index = this->GetHashCode(key, j + 1);
			}

			if (!(j < new_data->GetLength() && new_data->HasValue(index)))
			{
				if (!new_data->HasValue(index))
				{
					this->count++;
					new_record = new Record({ key, record->data, true });
					new_data->Set(index, new_record);
					continue;
				}

				for (index = 0; index < new_data->GetLength() && new_data->HasValue(index); index++)
				{
				};

				if (index < new_data->GetLength() && !new_data->HasValue(index))
				{
					this->count++;
					new_record = new Record({ key, record->data, true });
					new_data->Set(index, new_record);
				}
			}
		}
	}
	delete this->data;
	this->data = new_data;
}
