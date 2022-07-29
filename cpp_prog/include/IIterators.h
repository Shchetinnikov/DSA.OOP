#pragma once


template<class T>
class Sequence;

template<class T>
class ArraySequence;



template<class T>
class IIterator
{
public: //  онцепци€ односв€зного итератора
	virtual T GetValue() const = 0;							 // методы базового варианта
	virtual IIterator<T>* Next() = 0; //void или bool		 //
	virtual bool HasNext() = 0;						         //
	virtual bool HasValue() = 0;
public:  //  онцепци€ двунаправленного итератора
	virtual IIterator<T>* Prev() = 0; //void или bool
	virtual bool HasPrev() = 0; 
public:
	virtual IIterator<T>* operator++() { return this->Next(); }
	virtual IIterator<T>* operator++(int) {	return this->Next(); }
	virtual IIterator<T>* operator--() { return this->Prev(); }
	virtual IIterator<T>* operator--(int) { return this->Prev(); }
	virtual IIterator<T>* operator+(int shift) 
	{ 
		IIterator<T>* it;
		for (it = this; shift > 0; shift--)
			it = it->Next();
		return it; 
	}
	virtual IIterator<T>* operator-(int shift)
	{ 
		IIterator<T>* it;
		for (it = this; shift > 0; shift--)
			it = it->Prev();
		return it;
	}

};

//   [ 1, 2, 3, 4, 5]
// -1  0  1  2  3  4
//	^					- итератор в начальный момент времени может находитьс€ в произв. месте

//   []				„то делать в такой ситуации?
// -1 
//	^					


// »тератор дл€ структуры данных - страницы (блоки) типа ListSequence<ArraySequence<T>*>*
template<class T>
class SwitchableIterator : public IIterator<T>
{
private:
	Sequence<Sequence<T>*>* seqs;
	int seqsCount;
	int currentSeqIndex = -1;
	IIterator<T>* currentIterator = nullptr;
public:
	SwitchableIterator(Sequence<Sequence<T>*>* seqs, int count) // передаем набор коллекций
	{
		this->seqs = seqs;
		this->seqsCount = count;
	}

	virtual IIterator<T>* operator++() override
	{
		if (this->currentSeqIndex)
			this->currentSeqIndex = 0;

		while (this->seqs->Get(this->currentSeqIndex)->GetLength() == 0 && this->currentSeqIndex < this->seqsCount)
			this->currentSeqIndex++;

		if (this->currentSeqIndex < this->seqsCount)
		{
			// set HasValue = false;
			// set HasNext = false;
			return this;
		}
		this->currentIterator = this->seqs->Get(this->currentSeqIndex)->GetIterator();
		return this;
	}

	virtual T GetValue() const
	{
		if (this->currentIterator)
			return this->currentIterator->GetValue();
		throw 1;
	}
};


template<class T>
class IIterable
{
public:
	virtual IIterator<T>* GetIterator() = 0;
};





template<class T>
void IteratorUsageSample()
{
	Sequence<T>* seq = new ArraySequence<T>();
	//
	for (auto iterator = seq->GetIterator(); iterator->HasValue(); iterator->Next())
	{

	}
}