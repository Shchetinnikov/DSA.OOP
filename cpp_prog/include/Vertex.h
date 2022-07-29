#pragma once

#include "ArraySequence.h"
#include "Edge.h"


template<class TKey, class TWeight>
class Vertex
{
private:
	ArraySequence<Edge<TKey, TWeight>*>* edges_out;
	ArraySequence<Edge<TKey, TWeight>*>* edges_in;
	int neighbour_count;
	TKey key;
public:
	Vertex(TKey key);
	Vertex(const Vertex<TKey, TWeight>& vertex);
public:
	TKey GetKey() const { return this->key; };
	int GetNeighbourCount() const { return this->neighbour_count; };
	Edge<TKey, TWeight>* GetEdgeOut(TKey l_key);
	Edge<TKey, TWeight>* GetEdgeIn(TKey f_key);
	ArraySequence<Edge<TKey, TWeight>*>* GetEdgesOut();
	ArraySequence<Edge<TKey, TWeight>*>* GetEdgesIn();
	Vertex<TKey, TWeight>* GetNeighbour(TKey key);
	ArraySequence<Vertex<TKey, TWeight>*>* GetNeighbours();
	bool FindEdgeOut(TKey l_key);
	bool FindEdgeIn(TKey f_key);
	bool FindNeighbour(TKey key);
public:
	bool RemoveEdgeOut(TKey l_key);
	bool RemoveEdgeIn(TKey f_key);
	bool RemoveAllEdges();
	bool AddNeighbour(Vertex<TKey, TWeight>* vertex, TWeight weight);
public:
	~Vertex()
	{
		this->RemoveAllEdges();
		delete edges_in;
		delete edges_out;
	}
};


template<class TKey, class TWeight>
Vertex<TKey, TWeight> ::Vertex(TKey key): neighbour_count(0)
{
	this->key = key;
	this->edges_out = new ArraySequence<Edge<TKey, TWeight>*>();
	this->edges_in = new ArraySequence<Edge<TKey, TWeight>*>();
}


template<class TKey, class TWeight>
Vertex<TKey, TWeight> ::Vertex(const Vertex<TKey, TWeight>& vertex)
{
	Edge<TKey, TWeight>* edge;

	this->neighbour_count = vertex.neighbour_count;
	this->key = vertex.key;
	this->edges_out = new ArraySequence<Edge<TKey, TWeight>*>();
	this->edges_in = new ArraySequence<Edge<TKey, TWeight>*>();

	if (vertex.Edges_out)
	{
		for (int i = 0; i < vertex.edges_out->GetLength(); i++)
		{
			edge = vertex.edges_out->Get(i);
			Edge<TKey, TWeight>* new_edge = new Edge<TKey, TWeight>(edge->GetWeight(), this, edge->GetLast());
			this->edges_out->Append(new_edge);
		}
	}
	if (vertex.edges_in)
	{
		for (int i = 0; i < vertex.edges_in->GetLength(); i++)
		{
			edge = vertex.edges_in->Get(i);
			Edge<TKey, TWeight>* new_edge = new Edge<TKey, TWeight>(edge->GetWeight(), edge->GetFirst(), this);
			this->edges_in->Append(new_edge);
		}
	}
}


template<class TKey, class TWeight>
Edge<TKey, TWeight>* Vertex<TKey, TWeight> ::GetEdgeOut(TKey l_key)
{
	if(!this->edges_out)
		throw NoneValue("***ValueError: there are not outgoing edges in the vertex***", __FILE__, __LINE__);
	
	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		if (edge->GetLast()->GetKey() == l_key)
			return edge;
	}

	throw NoneValue("***ValueError: there is not outgoing Edge with such arguments in the vertex***", __FILE__, __LINE__);
}


template<class TKey, class TWeight>
Edge<TKey, TWeight>* Vertex<TKey, TWeight> ::GetEdgeIn(TKey f_key)
{
	if (!this->edges_in)
		throw NoneValue("***ValueError: there are not incoming edges in the vertex***", __FILE__, __LINE__);

	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_in->GetLength(); i++)
	{
		edge = this->edges_in->Get(i);
		if (edge->GetFirst()->GetKey() == f_key)
			return edge;
	}

	throw NoneValue("***ValueError: there is not incoming edge with such arguments in the vertex***", __FILE__, __LINE__);
}


template<class TKey, class TWeight>
ArraySequence<Edge<TKey, TWeight>*>* Vertex<TKey, TWeight> ::GetEdgesOut()
{
	if (this->edges_out)
	{
		return edges_out;
	}
	else
		return nullptr;
}


template<class TKey, class TWeight>
ArraySequence<Edge<TKey, TWeight>*>* Vertex<TKey, TWeight> ::GetEdgesIn()
{
	if (this->edges_in)
	{
		return edges_in;
	}
	else
		return nullptr;
}


template<class TKey, class TWeight>
Vertex<TKey, TWeight>* Vertex<TKey, TWeight> ::GetNeighbour(TKey key)
{
	if (!this->edges_out)
		throw NoneValue("***ValueError: there are not outgoing edges in the vertex***", __FILE__, __LINE__);
	
	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		if (edge->GetLast()->GetKey() == key)
			return edge->GetLast();
	}

	throw NoneValue("***ValueError: there is not neighbour of the current vertex with such key***", __FILE__, __LINE__);
}


template<class TKey, class TWeight>
ArraySequence<Vertex<TKey, TWeight>*>* Vertex<TKey, TWeight> ::GetNeighbours()
{
	if (!this->edges_out)
		throw NoneValue("***ValueError: there are not outgoing edges in the vertex***", __FILE__, __LINE__);

	ArraySequence<Vertex<TKey, TWeight>*>* vertices = new ArraySequence<Vertex<TKey, TWeight>*>();
	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		vertices->Append(edge->GetLast());
	}
	return vertices;
}


template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> ::FindEdgeOut(TKey l_key)
{
	if (!this->edges_out)
		return false;

	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		if (edge->GetLast()->GetKey() == l_key)
			return true;
	}

	return false;
}


template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> ::FindEdgeIn(TKey f_key)
{
	if (!this->edges_in)
		return false;

	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_in->GetLength(); i++)
	{
		edge = this->edges_in->Get(i);
		if (edge->GetLast()->GetKey() == f_key)
			return true;
	}

	return false;
}



template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> ::FindNeighbour(TKey key)
{
	if (!this->edges_out)
		return false;

	Edge<TKey, TWeight>* edge;
	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		if (edge->GetLast()->GetKey() == key)
			return true;
	}

	return false;
}


template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> ::RemoveEdgeOut(TKey l_key)
{
	if (!this->edges_out)
		return false;

	Edge<TKey, TWeight>* edge;
	Vertex<TKey, TWeight>* end;

	for (int i = 0; i < this->edges_out->GetLength(); i++)
	{
		edge = this->edges_out->Get(i);
		if (edge->GetLast()->GetKey() == l_key)
		{
			end = edge->GetLast();
			end->edges_in->Remove(edge);
			this->edges_out->RemoveAt(i);
			
			delete edge;
			this->neighbour_count--;
			return true;
		};
	}

	return false;
}


template<class TKey, class TWeight>
bool  Vertex<TKey, TWeight> ::RemoveEdgeIn(TKey f_key)
{
	if (!this->edges_in)
		return false;

	Edge<TKey, TWeight>* edge;
	Vertex<TKey, TWeight>* start;

	for (int i = 0; i < this->edges_in->GetLength(); i++)
	{
		edge = this->edges_in->Get(i);
		if (edge->GetFirst()->GetKey() == f_key)
		{
			start = edge->GetFirst();
			start->edges_out->Remove(edge);
			this->edges_in->RemoveAt(i);
			
			delete edge;
			return true;
		};
	}

	return false;
}



template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> ::RemoveAllEdges()
{
	Edge<TKey, TWeight>* edge;
	Vertex<TKey, TWeight>* vertex;

	if (!this->edges_in && !this->edges_out)
		return false;

	if (this->edges_out)
	{
		while(this->edges_out->GetLength() > 0)
		{
			edge = this->edges_out->Get(0);
			vertex = edge->GetLast();
			
			vertex->edges_in->Remove(edge);
			this->edges_out->RemoveAt(0);

			delete edge;
		}
		delete edges_out;
		this->edges_out = new ArraySequence<Edge<TKey, TWeight>*>();
	}

	if (this->edges_in)
	{
		while (this->edges_in->GetLength() > 0)
		{
			edge = this->edges_in->Get(0);
			vertex = edge->GetFirst();

			vertex->edges_out->Remove(edge);
			this->edges_in->RemoveAt(0);

			delete edge;
		}
		delete edges_in;
		this->edges_in = new ArraySequence<Edge<TKey, TWeight>*>();
	}
	this->neighbour_count = 0;
	return true;
}


template<class TKey, class TWeight>
bool Vertex<TKey, TWeight> :: AddNeighbour(Vertex<TKey, TWeight>* vertex, TWeight edge_weight)
{
	Edge<TKey, TWeight>* edge = new Edge<TKey, TWeight>(edge_weight, this, vertex);
	vertex->edges_in->Append(edge);
	this->edges_out->Append(edge);
	this->neighbour_count++;
	return true;
}
