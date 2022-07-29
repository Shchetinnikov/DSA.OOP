#pragma once

#include "Exception.h"
#include "Pair.h"
#include "HashTable.h"
#include "OrientedGraph.h"
#include "RouteTreeNode.h"


template<class TKey, class TWeight>
class RouteTree
{
private:
	TWeight(*add)(TWeight, TWeight);
private:
	Vertex<TKey, TWeight>* root;
	HashTable<TKey, RouteTreeNode<TKey, TWeight>*>* data;
public:
	RouteTree(Vertex<TKey, TWeight>* start, TWeight(*add)(TWeight, TWeight));
	//RouteTree(OrientedGraph<TKey, TWeight>* graph, TKey start_key, TWeight(*add)(TWeight, TWeight));
public:
	TWeight GetLength(TKey node_key) const;
	Sequence<Vertex<TKey, TWeight>*>* GetRoute(TKey node_key) const;
	RouteTreeNode<TKey, TWeight>* GetNode(TKey node_key) const;
	Vertex<TKey, TWeight>* GetRoot() const;
public:
	bool Insert(RouteTreeNode<TKey, TWeight>* node);
	bool Insert(Vertex<TKey, TWeight>* child, Vertex<TKey, TWeight>* parent, Edge<TKey, TWeight>* edge);
	bool RemoveNode(RouteTreeNode<TKey, TWeight>* node);
	bool RemoveNode(TKey node_key);
public:
	~RouteTree()
	{
		delete data;
	}
};


//template<class TKey, class TWeight>
//RouteTree<TKey, TWeight> ::RouteTree(OrientedGraph<TKey, TWeight>* graph, TKey start_key, TWeight(*add)(TWeight, TWeight))
//{
//	this->data = new HashTable<TKey, RouteTreeNode<TKey, TWeight>*>();
//
//}


template<class TKey, class TWeight>
RouteTree<TKey, TWeight> ::RouteTree(Vertex<TKey, TWeight>* start, TWeight(*add)(TWeight, TWeight))
{
	this->data = new HashTable<TKey, RouteTreeNode<TKey, TWeight>*>();

	RouteTreeNode<TKey, TWeight>* root_node = new RouteTreeNode<TKey, TWeight>(start);
	this->data->Add(start->GetKey(), root_node);
	this->add = add;
}




template<class TKey, class TWeight>
TWeight RouteTree<TKey, TWeight> ::GetLength(TKey node_key) const
{
	RouteTreeNode<TKey, TWeight>* node = this->data->Get(node_key);
	return node->GetLength();
}


template<class TKey, class TWeight>
Sequence<Vertex<TKey, TWeight>*>* RouteTree<TKey, TWeight> ::GetRoute(TKey node_key) const
{
	Sequence<Vertex<TKey, TWeight>*>* inverted_route = new ListSequence<Vertex<TKey, TWeight>*>();
	
	RouteTreeNode<TKey, TWeight>* node = this->data->Get(node_key);
	inverted_route->Append(node->GetChild());
	while (node->GetParent())
	{
		node = this->data->Get(node->GetParent()->GetKey());
		inverted_route->Append(node->GetChild());
	}
	
	Sequence<Vertex<TKey, TWeight>*>* route = new ListSequence <Vertex<TKey, TWeight>*>();
	for (int i = inverted_route->GetLength() - 1; i >= 0 ; i--)
	{
		route->Append(inverted_route->Get(i));
	}
	
	delete inverted_route;
	return route;
}



template<class TKey, class TWeight>
RouteTreeNode<TKey, TWeight>* RouteTree<TKey, TWeight> ::GetNode(TKey node_key) const
{
	return this->data->Get(node_key);
}


template<class TKey, class TWeight>
Vertex<TKey, TWeight>* RouteTree<TKey, TWeight> ::GetRoot() const
{
	return this->root;
}
	

template<class TKey, class TWeight>
bool RouteTree<TKey, TWeight> ::Insert(RouteTreeNode<TKey, TWeight>* node)
{
	if (node && this->data->Find(node->GetParent()->GetKey()))
	{
		this->data->Add(node->GetChild()->GetKey(), node);
		return true;
	}
	return false;
}


template<class TKey, class TWeight>
bool RouteTree<TKey, TWeight> ::Insert(Vertex<TKey, TWeight>* child, Vertex<TKey, TWeight>* parent, Edge<TKey, TWeight>* edge)
{
	if (child && parent && edge)
	{
		if (this->data->Find(parent->GetKey()))
		{
			RouteTreeNode<TKey, TWeight>* parent_node = this->data->Get(parent->GetKey());
			RouteTreeNode<TKey, TWeight>* node;

			if (parent_node->GetLength())
				node = new RouteTreeNode<TKey, TWeight>(child, parent, edge, this->add(parent_node->GetLength(), edge->GetWeight()));
			else
				node = new RouteTreeNode<TKey, TWeight>(child, parent, edge, edge->GetWeight());
			
			this->data->Add(child->GetKey(), node);
			return true;
		}
	}
	return false;
}


template<class TKey, class TWeight>
bool RouteTree<TKey, TWeight> ::RemoveNode(TKey node_key)
{
	return this->data->Remove(node_key);
}


template<class TKey, class TWeight>
bool RouteTree<TKey, TWeight> ::RemoveNode(RouteTreeNode<TKey, TWeight>* node)
{
	return this->RemoveNode(node->GetChild()->GetKey());
}