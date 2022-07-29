#pragma once

template<class TKey, class TValue>
class IPriorityQueue
{
public:
    virtual TValue Peek(const int i) const = 0;
    virtual TValue PeekFirst() const = 0;
    virtual TValue PeekLast() const = 0;
    virtual int GetCount() const = 0;
public:
    virtual void Enqueue(TValue item, TKey priority) = 0;
    virtual TValue Dequeue() = 0;
};