#pragma once

template<class TKey, class TWeight>
class Vertex;



template<class TKey, class TWeight>
class Edge
{
private:
	Vertex<TKey, TWeight>* first;
	Vertex<TKey, TWeight>* last;
	TWeight weight;
public:
	Edge(TWeight weight, Vertex<TKey, TWeight>* first, Vertex<TKey, TWeight>* last);
	Edge(const Edge<TKey, TWeight>& edge);
public:
	Vertex<TKey, TWeight>* GetFirst() const;
	Vertex<TKey, TWeight>* GetLast() const;
	TWeight GetWeight() const;
};


template<class TKey, class TWeight>
Edge<TKey, TWeight> ::Edge(TWeight weight, Vertex<TKey, TWeight>* first, Vertex<TKey, TWeight>* last)
{
	this->weight = weight;
	this->first = first;
	this->last= last;
}


template<class TKey, class TWeight>
Edge<TKey, TWeight> ::Edge(const Edge<TKey, TWeight>& edge)
{
	this->weight = edge.weight;
	this->first = edge.first;
	this->last = edge.last;
}

template<class TKey, class TWeight>
Vertex<TKey, TWeight>* Edge<TKey, TWeight>:: GetFirst() const
{
	return this->first;
}


template<class TKey, class TWeight>
Vertex<TKey, TWeight>* Edge<TKey, TWeight> ::GetLast() const
{
	return this->last;
}


template<class TKey, class TWeight>
TWeight Edge<TKey, TWeight> ::GetWeight() const
{
	return this->weight;
}
