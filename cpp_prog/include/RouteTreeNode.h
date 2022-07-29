#pragma once

#include "Exception.h"
#include "Edge.h"
#include "Vertex.h"

template<class TKey, class TWeight>
class RouteTreeNode
{
private:
	Vertex<TKey, TWeight>* parent;
	Vertex<TKey, TWeight>* child;
	Edge<TKey, TWeight>* edge;
	TWeight length;
public:
	RouteTreeNode(Vertex<TKey, TWeight>* vertex);
	RouteTreeNode(Vertex<TKey, TWeight>* child, Vertex<TKey, TWeight>* parent, Edge<TKey, TWeight>* edge, TWeight length);
	RouteTreeNode(const RouteTreeNode<TKey, TWeight>& node);
public:
	Vertex<TKey, TWeight>* GetParent() const { return this->parent; };
	Vertex<TKey, TWeight>* GetChild() const { return this->child; };
	Edge<TKey, TWeight>* GetEdge() const { return this->edge; };
	TWeight GetLength() const { return this->length; };
};


template<class TKey, class TWeight>
RouteTreeNode<TKey, TWeight> ::RouteTreeNode(Vertex<TKey, TWeight>* vertex) : parent(nullptr), edge(nullptr), length(0)
{
	this->child = vertex;
}


template<class TKey, class TWeight>
RouteTreeNode<TKey, TWeight> ::RouteTreeNode(Vertex<TKey, TWeight>* child, Vertex<TKey, TWeight>* parent, Edge<TKey, TWeight>* edge, TWeight length)
{
	if(!child)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->parent = parent;
	this->child = child;
	this->edge = edge;
	this->length = length;
}


template<class TKey, class TWeight>
RouteTreeNode<TKey, TWeight> ::RouteTreeNode(const RouteTreeNode<TKey, TWeight>& node)
{
	if (!node.child)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	this->parent = node.parent;
	this->child = node.child;
	this->edge = node.edge;
	this->length = node.length;
}