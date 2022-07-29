#pragma once

#include "Exception.h"
#include "HashTable.h"
#include "HashSet.h"
#include "Edge.h"
#include "Vertex.h"
#include "StdSqPriorityQueue.h"
#include "RouteTree.h"


template<class TKey, class TWeight>
class OrientedGraph
{
private:
	HashTable<TKey, Vertex<TKey, TWeight>*>* vertices;
	int vertex_count;
	int edge_count;
public:
	OrientedGraph(const int capacity = 0);
	OrientedGraph(const OrientedGraph& graph);
public:
	int GetVertexCount() const { return this->vertex_count; };
	int GetEdgeCount() const { return this->edge_count; };
	Vertex<TKey, TWeight>* GetVertex(TKey key) const;
	Edge<TKey, TWeight>* GetEdge(TKey start_key, TKey end_key) const;
	bool FindVertex(TKey key) const;
	bool FindEdge(TKey start_key, TKey end_key) const;
public:
	bool AddVertex(TKey key, Vertex<TKey, TWeight>* vertex);
	bool AddEdge(TKey start_key, TKey end_key, TWeight edge_weight);
	bool RemoveVertex(TKey key);
	bool RemoveEdge(TKey start_key, TKey end_key);
	void Dijkstra(TKey v1_key, TKey v2_key, int (*comparer)(TWeight, TWeight), TWeight (*add)(TWeight, TWeight), TWeight& length, Sequence<Vertex<TKey, TWeight>*>*& path);
	//void Dijkstra(TKey key, Sequence<int>& lengths, Sequence<>& paths);
	/*OrientedGraph<TKey>* Ostov();
	Sequence<TKey>* TopologicalSort();*/
public:
	~OrientedGraph()
	{
		delete vertices;
	}
};


template<class TKey, class TWeight>
OrientedGraph<TKey, TWeight>::OrientedGraph(const int capacity): vertex_count(0), edge_count(0)
{
	if (capacity < 0)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->vertices = new HashTable<TKey, Vertex<TKey, TWeight>*>(capacity);
}


template<class TKey, class TWeight>
OrientedGraph<TKey, TWeight>::OrientedGraph(const OrientedGraph& graph)
{
	this->vertices = new HashTable<TKey, Vertex<TKey, TWeight>*>(*graph.vertices);
	this->vertex_count = graph.vertex_count;
	this->edge_count = graph.edge_count;
}


template<class TKey, class TWeight>
Vertex<TKey, TWeight>* OrientedGraph<TKey, TWeight>::GetVertex(TKey key) const
{
	return this->vertices->Get(key);
}

template<class TKey, class TWeight>
Edge<TKey, TWeight>* OrientedGraph<TKey, TWeight>::GetEdge(TKey start_key, TKey end_key) const
{
	Vertex<TKey, TWeight>* start = this->vertices->Get(start_key);
	return start->GetEdgeOut(end_key);
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::FindVertex(TKey key) const
{
	return this->vertices->Find(key);
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::FindEdge(TKey start_key, TKey end_key) const
{
	Vertex<TKey, TWeight>* start = this->vertices->Get(start_key);
	return start->FindEdgeOut(end_key);
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::AddVertex(TKey key, Vertex<TKey, TWeight>* vertex)
{
	if (vertex->GetEdgesIn()->GetLength() || vertex->GetEdgesOut()->GetLength())
		return false;

	if (this->vertices->Add(key, vertex))
	{
		this->vertex_count++;
		return true;
	}
	return false;
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::AddEdge(TKey start_key, TKey end_key, TWeight edge_weight)
{
	Vertex<TKey, TWeight>* start = this->vertices->Get(start_key);
	Vertex<TKey, TWeight>* end = this->vertices->Get(end_key);
	if (start->AddNeighbour(end, edge_weight))
	{
		this->edge_count++;
		return true;
	}
	return false;
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::RemoveVertex(TKey key)
{
	Vertex<TKey, TWeight>* vertex = this->vertices->Get(key);
	int arcs_count = vertex->GetEdgesOut()->GetLength() + vertex->GetEdgesIn()->GetLength();
	if (this->vertices->Remove(key))
	{
		this->edge_count -= arcs_count;
		this->vertex_count--;
		return true;
	}
	return false;
}


template<class TKey, class TWeight>
bool OrientedGraph<TKey, TWeight>::RemoveEdge(TKey start_key, TKey end_key)
{
	Vertex<TKey, TWeight>* start = this->vertices->Get(start_key);
	if (start->RemoveEdgeOut(end_key))
	{
		this->edge_count--;
		return true;
	}
	return false;
}


template<class TKey, class TWeight>
void OrientedGraph<TKey, TWeight>::Dijkstra(TKey v1_key, TKey v2_key, int (*comparer)(TWeight, TWeight), TWeight (*add)(TWeight, TWeight), TWeight& length, Sequence<Vertex<TKey, TWeight>*>*& path)
{
	// ћножество посещенных вершин и очередь с приоритетами посещени€ вершин
	HashSet<TKey, Vertex<TKey, TWeight>*>* visited = new HashSet<TKey, Vertex<TKey, TWeight>*>();
	StdSqPriorityQueue<TWeight, Pair<Vertex<TKey, TWeight>*, Vertex<TKey, TWeight>*>*>* pr_edges = new StdSqPriorityQueue<TWeight, Pair<Vertex<TKey, TWeight>*, Vertex<TKey, TWeight>*>*>(comparer);

	// Ќачальна€ и конечна€ вершины
	Vertex<TKey, TWeight>* start = this->GetVertex(v1_key);
	Vertex<TKey, TWeight>* finish = this->GetVertex(v2_key);

	Pair<TKey, Vertex<TKey, TWeight>*>* finish_pair = new Pair<TKey, Vertex<TKey, TWeight>*>(v2_key, finish);

	// “екуща€ рассматриваема€ вершина и соседний узел (родитель) 
	Vertex<TKey, TWeight>* deq_vertex = start;
	Vertex<TKey, TWeight>* parent = nullptr;
	TWeight label;											// метка дл€ текущей вершины (длина кратчайшего пути)
	Sequence<Edge<TKey, TWeight>*>* edges;					// исход€щие дуги
	Pair<TKey, Vertex<TKey, TWeight>*>* deq_vertex_pair;	// пара "ключ текущего узла - текущий узел"


	// »нициализаци€ дерева маршрутов корневым узлом
	RouteTree<TKey, TWeight>* r_tree = new RouteTree<TKey, TWeight>(deq_vertex, add);

	// ѕромежуточные значени€
	Vertex<TKey, TWeight>* vertex;	// соседний узел
	TWeight weight;					// вес дуги
	Pair<Vertex<TKey, TWeight>*, Vertex<TKey, TWeight>*>* parent_child;		// пара родитель-дочерний узел


	// ѕоиск кратчайшего пути до конечной вершины
	while (!visited->HasElement(finish_pair))
	{
		edges = deq_vertex->GetEdgesOut();

		for (auto iterator = edges->GetIterator(); iterator->HasValue(); iterator->Next())
		{
			vertex = iterator->GetValue()->GetLast();
			weight = iterator->GetValue()->GetWeight();
			if (!visited->HasElement(new Pair<TKey, Vertex<TKey, TWeight>*>(vertex->GetKey(), vertex)))
			{
				parent_child = new Pair<Vertex<TKey, TWeight>*, Vertex<TKey, TWeight>*>(deq_vertex, vertex);

				if (deq_vertex == start)
				{
					pr_edges->Enqueue(parent_child, weight);
				}
				else
				{
					pr_edges->Enqueue(parent_child, add(weight, label));
				}
			}
		}
		
		deq_vertex_pair = new Pair<TKey, Vertex<TKey, TWeight>*>(deq_vertex->GetKey(), deq_vertex);
		visited->Add(deq_vertex_pair);

		if (deq_vertex != start)
		{
			r_tree->Insert(deq_vertex, parent, parent->GetEdgeOut(deq_vertex->GetKey()));
		}

		do
		{
			label = pr_edges->PeekPriority();
			parent_child = pr_edges->Dequeue();
			parent = parent_child->GetKey();
			deq_vertex = parent_child->GetValue();
		} while (visited->HasElement(new Pair<TKey, Vertex<TKey, TWeight>*>(deq_vertex->GetKey(), deq_vertex)) && pr_edges->GetCount());
	}

	length = r_tree->GetLength(v2_key);
	path = r_tree->GetRoute(v2_key);

	delete r_tree;
	delete visited;
	delete pr_edges;
	delete finish_pair;
}


//template<class TKey, class TWeight>
//void Dijkstra(TKey key, Sequence<int>& lengths, Sequence<>& paths)
//{
//
//}