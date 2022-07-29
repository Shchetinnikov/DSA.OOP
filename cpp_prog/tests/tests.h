#pragma once
#include <iostream>

#include "Exception.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "HashTable.h"
#include "Person.h"
#include "PersonRW.h"
#include "ISorter.h"
#include "test_runner.h"
#include "tests.h"

using namespace std;

void GetSubsequenceTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	int exp[2] = { 1, 3 };
	// Получение подпосл-ти
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 2);
		Sequence<int>* result = origin->GetSubsequence(1, 2);
		PrintData(*origin, *expected, *result);
		AssertEqual(*result, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 2);
		Sequence<int>* result = origin->GetSubsequence(1, 2);
		PrintData(*origin, *expected, *result);
		AssertEqual(*result, *expected, __FILE__, __LINE__);
	}
	// Получение подпосл-ти с выходом за пределы исходной посл-ти
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		try
		{
			Sequence<int>* result = origin->GetSubsequence(3, 4);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		}
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		try
		{
			Sequence<int>* result = origin->GetSubsequence(3, 4);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		}
	}
}

void PrependTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	int exp[5] = { 5, 4, 1, 3, 2 };
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->Prepend(5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->Prepend(5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
}

void AppendTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	int exp[5] = { 4, 1, 3, 2, 5 };
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->Append(5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->Append(5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
}

void InsertAtTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	// Вставка в центральные позиции
	{
		int exp[5] = { 4, 1, 5, 3, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(2, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[5] = { 4, 1, 5, 3, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(2, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Вставка в крайние позиции
	// Слева
	{
		int exp[5] = { 5, 4, 1, 3, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(0, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[5] = { 5, 4, 1, 3, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(0, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Справа
	{
		int exp[5] = { 4, 1, 3, 5, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(origin->GetLength() - 1, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[5] = { 4, 1, 3, 5, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 5);
		PrintData(*origin, *expected);
		origin->InsertAt(origin->GetLength() - 1, 5);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Обращение к индексу вне диапазона
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		try
		{
			origin->InsertAt(origin->GetLength(), 5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		};
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		try
		{
			origin->InsertAt(origin->GetLength(), 5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		};
	}
}

void RemoveAtTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	// Удаление в центральных позициях
	{
		int exp[3] = { 4, 3, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[3] = { 4, 3, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Удаление в крайних позициях
	// Слева
	{
		int exp[3] = { 1, 3, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(0);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[3] = { 1, 3, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(0);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Справа
	{
		int exp[3] = { 4, 1, 3 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(origin->GetLength() - 1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[3] = { 4, 1, 3 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->RemoveAt(origin->GetLength() - 1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Обращение к индексу вне диапазона
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		try
		{
			origin->RemoveAt(4);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		};
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		try
		{
			origin->RemoveAt(4);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		};
	}
}

void RemoveTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	// Удаление центрального элемента
	{
		int exp[3] = { 4, 3, 2 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->Remove(1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[3] = { 4, 3, 2 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->Remove(1);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Удаление крайнего элемента
	{
		int exp[3] = { 4, 1, 3 };
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->Remove(2);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		int exp[3] = { 4, 1, 3 };
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(exp, 3);
		PrintData(*origin, *expected);
		origin->Remove(2);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Попытка удалить элемент, не входящий в посл-ть
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		try
		{
			origin->Remove(5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (NoneValue e)
		{
			PrintData(*origin, e);
		};
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		try
		{
			origin->Remove(5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (NoneValue e)
		{
			PrintData(*origin, e);
		};

	}
}

void RemoveAllTest()
{
	int arr[5] = { 4, 1, 4, 3, 4 };
	int exp[2] = { 1, 3 };
	// Удаление эл-та из посл-ти
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 5);
		Sequence<int>* expected = new ArraySequence<int>(exp, 2);
		PrintData(*origin, *expected);
		origin->RemoveAll(4);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 5);
		Sequence<int>* expected = new ListSequence<int>(exp, 2);
		PrintData(*origin, *expected);
		origin->RemoveAll(4);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Попытка удалить элемент, не входящий в посл-ть
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 5);
		try
		{
			origin->RemoveAll(5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (NoneValue e)
		{
			PrintData(*origin, e);
		};
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 5);
		try
		{
			origin->RemoveAll(5);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (NoneValue e)
		{
			PrintData(*origin, e);
		};
	}
}

void ConcatTest()
{
	int arr_1[4] = { 4, 1, 3, 2 };
	int arr_2[2] = { 5, 5 };
	int exp[6] = { 4, 1, 3, 2, 5, 5 };
	{
		Sequence<int>* first = new ArraySequence<int>(arr_1, 4);
		Sequence<int>* second = new ArraySequence<int>(arr_2, 2);
		Sequence<int>* expected = new ArraySequence<int>(exp, 6);
		Sequence<int>* result = first->Concat(*second);
		PrintData(*first, *second, *expected, *result);
		AssertEqual(*result, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* first = new ListSequence<int>(arr_1, 4);
		Sequence<int>* second = new ListSequence<int>(arr_2, 2);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		Sequence<int>* result = first->Concat(*second);
		PrintData(*first, *second, *expected, *result);
		AssertEqual(*result, *expected, __FILE__, __LINE__);
	}
}

void CopyTest()
{
	int arr[4] = { 4, 1, 3, 2 };
	{
		Sequence<int>* origin = new ArraySequence<int>(arr, 4);
		Sequence<int>* expected = new ArraySequence<int>(arr, 4);
		Sequence<int>* copy = origin->Copy();
		PrintData(*origin, *expected, *copy);
		AssertEqual(*copy, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr, 4);
		Sequence<int>* expected = new ListSequence<int>(arr, 4);
		Sequence<int>* copy = origin->Copy();
		PrintData(*origin, *expected, *copy);
		AssertEqual(*copy, *expected, __FILE__, __LINE__);
	}
}

void CopyToTest()
{
	int arr1[4] = { 4, 1, 3, 2 };
	int arr2[6] = { 0, 0, 0, 0, 0, 0 };
	int exp[6] = { 0, 0, 4, 1, 3, 2 };
	// Копирование в посл-ть
	{
		Sequence<int>* origin = new ArraySequence<int>(arr1, 4);
		Sequence<int>* target = new ArraySequence<int>(arr2, 6);
		Sequence<int>* expected = new ArraySequence<int>(exp, 6);
		tuple<Sequence<int>*, Sequence<int>*> pair = tie(origin, target);
		PrintData(pair, *expected);
		origin->CopyTo(target, 2);
		PrintData(*target);
		AssertEqual(*target, *expected, __FILE__, __LINE__);
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr1, 4);
		Sequence<int>* target = new ListSequence<int>(arr2, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		tuple<Sequence<int>*, Sequence<int>*> pair = tie(origin, target);
		PrintData(pair, *expected);
		origin->CopyTo(target, 2);
		PrintData(*target);
		AssertEqual(*target, *expected, __FILE__, __LINE__);
	}
	// Копирование в посл-ть с неверным указанием начального индекса
	{
		Sequence<int>* origin = new ArraySequence<int>(arr1, 4);
		Sequence<int>* target = new ArraySequence<int>(arr2, 6);
		Sequence<int>* expected = new ArraySequence<int>(exp, 6);
		try {
			origin->CopyTo(target, 6);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		}
	}
	{
		Sequence<int>* origin = new ListSequence<int>(arr1, 4);
		Sequence<int>* target = new ListSequence<int>(arr2, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		try {
			origin->CopyTo(target, 6);
			BreakPointer(__FILE__, __LINE__);
		}
		catch (IndexOutOfRange e)
		{
			PrintData(*origin, e);
		}
	}
}




void ShakerSorterTest()
{
	ShakerSorter<int> sorter(AscendingComparer<int>);
	// Пустая послед-ть
	{
		Sequence<int>* origin = new ListSequence<int>();
		Sequence<int>* expected = new ListSequence<int>();
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 1
	{
		int arr[1] = { 1 };
		Sequence<int>* origin = new ListSequence<int>(arr, 1);
		Sequence<int>* expected = new ListSequence<int>(arr, 1);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 2
	{
		int arr[5] = { 1, 1, 1, 1, 1, };
		Sequence<int>* origin = new ListSequence<int>(arr, 5);
		Sequence<int>* expected = new ListSequence<int>(arr, 5);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с совпадающими элементами
	{
		int arr[6] = { 5, 1, 5, 3, 7, 1 };
		int exp[6] = { 1, 1, 3, 5, 5, 7 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с отрицательными членами
	{
		int arr[6] = { -5, 0, 6, 1, 5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Обратно отсортированная послед-ть
	{
		int arr[6] = { 6, 5, 1, 0, -5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Прямо отсортированная послед-ть
	{
		int arr[6] = { -9, -5, 0, 1, 5, 6 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
}


void ShellSorterTest()
{
	ShellSorter<int> sorter(AscendingComparer<int>);
	// Пустая послед-ть
	{
		Sequence<int>* origin = new ListSequence<int>();
		Sequence<int>* expected = new ListSequence<int>();
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 1
	{
		int arr[1] = { 1 };
		Sequence<int>* origin = new ListSequence<int>(arr, 1);
		Sequence<int>* expected = new ListSequence<int>(arr, 1);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 2
	{
		int arr[5] = { 1, 1, 1, 1, 1, };
		Sequence<int>* origin = new ListSequence<int>(arr, 5);
		Sequence<int>* expected = new ListSequence<int>(arr, 5);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с совпадающими элементами
	{
		int arr[6] = { 5, 1, 5, 3, 7, 1 };
		int exp[6] = { 1, 1, 3, 5, 5, 7 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с отрицательными членами
	{
		int arr[6] = { -5, 0, 6, 1, 5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Обратно отсортированная послед-ть
	{
		int arr[6] = { 6, 5, 1, 0, -5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Прямо отсортированная послед-ть
	{
		int arr[6] = { -9, -5, 0, 1, 5, 6 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
}

void MergeSorterTest()
{
	MergeSorter<int> sorter(AscendingComparer<int>);
	// Пустая послед-ть
	{
		Sequence<int>* origin = new ListSequence<int>();
		Sequence<int>* expected = new ListSequence<int>();
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 1
	{
		int arr[1] = { 1 };
		Sequence<int>* origin = new ListSequence<int>(arr, 1);
		Sequence<int>* expected = new ListSequence<int>(arr, 1);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть из одного элемента - 2
	{
		int arr[5] = { 1, 1, 1, 1, 1, };
		Sequence<int>* origin = new ListSequence<int>(arr, 5);
		Sequence<int>* expected = new ListSequence<int>(arr, 5);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с совпадающими элементами
	{
		int arr[6] = { 5, 1, 5, 3, 7, 1 };
		int exp[6] = { 1, 1, 3, 5, 5, 7 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Послед-ть с отрицательными членами
	{
		int arr[6] = { -5, 0, 6, 1, 5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Обратно отсортированная послед-ть
	{
		int arr[6] = { 6, 5, 1, 0, -5, -9 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
	// Прямо отсортированная послед-ть
	{
		int arr[6] = { -9, -5, 0, 1, 5, 6 };
		int exp[6] = { -9, -5, 0, 1, 5, 6 };
		Sequence<int>* origin = new ListSequence<int>(arr, 6);
		Sequence<int>* expected = new ListSequence<int>(exp, 6);
		PrintData(*origin, *expected);
		sorter.Sort(origin);
		PrintData(*origin);
		AssertEqual(*origin, *expected, __FILE__, __LINE__);
	}
}


void HashTableTest()
{
	Sequence<Person*>* persons;
	Person* person;
	persons = ReadPersons();

	HashTable<int, Person*>* table;
	int power = 2;

	for(int i = 1; i <= 10; i++)
	{
		SetConsoleTextAttribute(HCONSOLE, (WORD)((White << 4) | Black));
		cout << "HashTable capacity: " << power;
		SetConsoleTextAttribute(HCONSOLE, (WORD)((Black << 4) | White));

		table = new HashTable<int, Person*>(power);

		cout << endl;
		for (int j = 0; j < persons->GetLength() - 9900; j++)
		{
			person = persons->Get(j);
			
			cout << endl;
			cout << "Person-" << j + 1 << endl;
			cout << "ID: " << person->GetPassportID() << endl;

			table->Add(person->GetPassportID(), person);
		}
		cout << endl << endl;
		delete table;
		
		power *= 2;
	}
}



void TestAll()
{
	TestRunner obj;
	PrintHeading("*****'Sequence' testing*****");
	obj.RunTest(GetSubsequenceTest, "GetSubsequenceTest");
	obj.RunTest(PrependTest, "PrependTest");
	obj.RunTest(AppendTest, "AppendTest");
	obj.RunTest(InsertAtTest, "InsertAtTest");
	obj.RunTest(RemoveAtTest, "RemoveAtTest");
	obj.RunTest(RemoveTest, "RemoveTest");
	obj.RunTest(RemoveAllTest, "RemoveAllTest");
	obj.RunTest(ConcatTest, "ConcatTest");
	obj.RunTest(CopyTest, "CopyTest");
	obj.RunTest(CopyToTest, "CopyToTest");

	cout << endl;

	PrintHeading("*****'ISorter' testing*****");
	obj.RunTest(ShakerSorterTest, "ShakerSorterTest");
	obj.RunTest(ShellSorterTest, "ShellSorterTest");
	obj.RunTest(MergeSorterTest, "MergeSorterTest");

	cout << endl;

	/*PrintHeading("***** 'Hash Table' testing *****");
	obj.RunTest(HashTableTest, "HashTableTest");*/

	//PrintHeading("*****'Graph algorithms' testing*****");
	//obj.RunTest(ShakerSorterTest, "ShakerSorterTest");
	//obj.RunTest(ShellSorterTest, "ShellSorterTest");
	//obj.RunTest(MergeSorterTest, "MergeSorterTest");


}