#pragma once

#include <chrono>
#include <math.h>

#include "Exception.h"
#include "Sequence.h"
#include "BinaryTree.h"
#include "BinaryTreeNode.h"

using namespace std::chrono;

template <class T>
int AscendingComparer(T item1, T item2)
{
    if (item1 < item2)
        return -1;
    else
        if (item1 > item2)
            return 1;
        else
            return 0;
}

template <class T>
int DescendingComparer(T item1, T item2)
{
    if (item1 < item2)
        return 1;
    else
        if (item1 > item2)
            return -1;
        else
            return 0;
}

template <class T>
class ISorter
{
protected:
    int (*cmp)(T, T);
    double timer = 0;
protected:
    void Swap(Sequence<T>* seq, const int index1, const int index2)
    {
        if (!seq || index1 < 0 || index2 < 0)
            throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
        T item = seq->Get(index1);
        seq->Set(index1, seq->Get(index2));
        seq->Set(index2, item);
    }
public:
    double GetTimerValue()
    {
        return this->timer;
    }
public:
    virtual void Sort(Sequence<T>* input) = 0;
};


template <class T>
class ShakerSorter : public ISorter<T>
{
public:
    ShakerSorter(int (*cmp)(T, T))
    {
        this->cmp = cmp;
    }
public:
    virtual void Sort(Sequence<T>* input) override;
};


template <class T>
class ShellSorter : public ISorter<T> 
{
public:
    ShellSorter(int (*cmp)(T, T))
    {
        this->cmp = cmp;
    }
public:
    virtual void Sort(Sequence<T>* input) override;
};


template <class T>
class MergeSorter : public ISorter<T>
{
protected:
    void MergeRecursive(Sequence<T>* input, int left, int middle, int right);
public:
    MergeSorter(int (*cmp)(T, T))
    {
        this->cmp = cmp;
    }
public:
    virtual void Sort(Sequence<T>* input) override;
};


template<class T>
void ShakerSorter<T>::Sort(Sequence<T>* input)
{
    if (!input)
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
   
    auto start = system_clock::now();
    int left = 0;
    int right = input->GetLength() - 1;
    int flag = 1;                                           // идентификатор смещения
    
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)
        {
            if (this->cmp(input->Get(i), input->Get(i + 1)) == 1)
            {
                this->Swap(input, i, i + 1);
                flag = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (this->cmp(input->Get(i - 1), input->Get(i)) == 1)
            {
                this->Swap(input, i - 1, i);
                flag = 1;
            }
         
        }
        left++;
    }

    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}


template<class T>
void ShellSorter<T> ::Sort(Sequence<T>* input)
{
    if (!input)
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
   
    auto start = system_clock::now();

# if 0
    // Схема Инсерпи-Седгевика
    // t = [log(n)]

    int t = floor(log2(input->GetLength()));
    int p = 2.5;  // 2,5, pi, exp

    if (t >= 8)
        t = 7;

    int* a = new int[t];
    for (int i = 0; i < t; i++)
        a[i] = floor(pow(p, i));

    std::vector<int> steps(t);
    for (int i = t - 1; i >= 0; i--)
    {
        steps[i] = 1;
        for (int j = 1; j <= i; j++)
            steps[i] *= a[j];
    }

    for (auto step : steps)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= step) && this->cmp(input->Get(j - step), element) == 1)  // переносим наим/наиб в конец группы
            {
                input->Set(j, input->Get(j - step));
                j = j - step;
            }
            input->Set(j, element);
        }
    }

# endif

# if 0
    // Модификация Седжвика
    Sequence<int>* steps = new ListSequence<int>();
    int dist = 0;
    for (int i = 0; dist < input->GetLength(); i++)
    { 
        if (i % 2 == 0)
            dist = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
        else
            dist = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
        steps->Prepend(dist);
    }

    for(int k = 0; k < steps->GetLength(); k++)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= steps->Get(k)) && this->cmp(input->Get(j - steps->Get(k)),element) == 1)  // переносим наим/наиб в конец группы
            {
                input->Set(j, input->Get(j - steps->Get(k)));
                j = j - steps->Get(k);
            }
            input->Set(j, element);
        }
    }
    
# endif

# if 1
    // Distance d(i) / 2
    int step = input->GetLength() / 2;
    while(step > 0)
    {
        for (int i = 0; i < input->GetLength(); i++)
        {
            int j = i;
            T element = input->Get(i);
            while ((j >= step) && this->cmp(input->Get(j - step),element) == 1)  // переносим наим/наиб в конец группы
            {
                input->Set(j, input->Get(j - step));
                j = j - step;
            }
            input->Set(j, element);
        }
        step = step / 2;
    }

# endif
    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}


template<class T>
void MergeSorter<T>::Sort(Sequence<T>* input)
{
    if (!input)
        throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

    auto start = system_clock::now();

    int i_length = input->GetLength();
    if (i_length > 1)
    {
        MergeRecursive(input, 0, i_length / 2, i_length);
    }

    auto finish = system_clock::now();
    duration<double> elapsed = finish - start;
    this->timer = elapsed.count() * 1000;
}



template<class T>
void MergeSorter<T> ::MergeRecursive(Sequence<T>* input, int left, int middle, int right)
{
    if (right - left > 1)
    {
        // получаем 2 отсортированные части
        MergeRecursive(input, left, left + (middle - left) / 2, middle);
        MergeRecursive(input, middle, middle + (right - middle) / 2, right);

        int ind_l = 0; // индекс левой части
        int ind_r = 0; // индекс правой части
        
        Sequence<T>* result = new ArraySequence<T>(right - left);

        while (left + ind_l < middle && middle + ind_r < right)
        {
            if (this->cmp(input->Get(left + ind_l), input->Get(middle + ind_r)) == 1)
            {
                result->Set(ind_l + ind_r, input->Get(middle + ind_r));
                ind_r++;
            }
            else
            {
                result->Set(ind_l + ind_r, input->Get(left + ind_l));
                ind_l++;
            }
        }
            
        while (left + ind_l < middle)
        {
            result->Set(ind_l + ind_r, input->Get(left + ind_l));
            ind_l++;
        }

        while (middle + ind_r < right)
        {
            result->Set(ind_l + ind_r, input->Get(middle + ind_r));
            ind_r++;
        }

        for (int i = 0; i < result->GetLength(); i++)
        {
            input->Set(left + i, result->Get(i));
        }

        delete result;
    }
};
