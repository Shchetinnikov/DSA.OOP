#pragma once

#include <string>

#include "Exception.h"
#include "Sequence.h"
#include "ListSequence.h"
#include "BinaryTreeNode.h"

/*
	Бинарное дерево поиска
*/


template <class TKey, class TValue>
class BinaryTree
{
private:
	BinaryTreeNode<TKey, TValue>* root;
	Sequence<BinaryTreeNode<TKey, TValue>*>* stitched;
	int count;
protected:																		
	// функции рекурсивного вызова
	void BinaryTreeBuilder(BinaryTreeNode<TKey, TValue>* tree_node, BinaryTreeNode<TKey, TValue>* node);
	void BinaryTreeCleaner(BinaryTreeNode<TKey, TValue>* node);
protected:
	// функции рекурсивного вызова
	BinaryTreeNode<TKey, TValue>* GetNode(const TKey& key, BinaryTreeNode<TKey, TValue>* start) const;
	int GetSize(BinaryTreeNode< TKey, TValue>* node) const;
	BinaryTreeNode<TKey, TValue>* GetParent(BinaryTreeNode<TKey, TValue>* child, BinaryTreeNode<TKey, TValue>* start) const;
	bool Find(const TKey& key, BinaryTreeNode<TKey, TValue>* start) const;
	bool AssertEqual(BinaryTreeNode<TKey, TValue>* node1, BinaryTreeNode<TKey, TValue>* node2) const;
	bool Insert(BinaryTreeNode<TKey, TValue>* node, BinaryTreeNode < TKey, TValue>* start);
	BinaryTreeNode<TKey, TValue>* Map(BinaryTreeNode<TKey, TValue>* node, BinaryTreeNode<TKey, TValue>* (*mfun)(BinaryTreeNode<TKey, TValue>*)) const;
	void Where(BinaryTreeNode<TKey, TValue>* start, BinaryTree<TKey, TValue>* result, bool (*wfun)(BinaryTreeNode<TKey, TValue>*)) const;
	TValue Reduce(BinaryTreeNode<TKey, TValue>* node, TValue(*rfun)(TValue, TValue), const TValue& value, const string order) const;
	void Stitch(BinaryTreeNode<TKey, TValue>* start, Sequence<BinaryTreeNode<TKey, TValue>*>* seq, const string order);
public:	
	// конструкторы
	BinaryTree() : root(nullptr), stitched(nullptr), count(0) {};													
	BinaryTree(const BinaryTree<TKey, TValue>& tree);													
public: 
	// декомпозиция
	BinaryTreeNode<TKey, TValue>* GetRoot() const {	return this->root; 	};
	Sequence<BinaryTreeNode<TKey, TValue>*>* GetStitched() const { return this->stitched; };
	BinaryTreeNode<TKey, TValue>* GetNode(const TKey& key) const { return GetNode(key, this->root);	};
	BinaryTreeNode<TKey, TValue>* GetParent(BinaryTreeNode<TKey, TValue>* child) const { return this->GetParent(child, this->root); };
	BinaryTree<TKey, TValue>* GetSubTree(const TKey& key) const;
	int GetSize() { return this->count; };
	bool Find(const TKey& key) const {	return Find(key, this->root); };
	bool FindSubTree(BinaryTree<TKey, TValue>* subtree) const;
public: 
	// методы
	void Round(BinaryTreeNode<TKey, TValue>* start, void (*visit)(BinaryTreeNode<TKey, TValue>*), const string order = "NLR") const;
	bool Insert(BinaryTreeNode<TKey, TValue>* node);
	bool Insert(const TKey& key, const TValue& item);
	BinaryTree<TKey, TValue>* Map(BinaryTreeNode<TKey, TValue>* (*mfun)(BinaryTreeNode<TKey, TValue>*)) const;
	BinaryTree<TKey, TValue>* Where(bool (*wfun)(BinaryTreeNode<TKey, TValue>*)) const;
	TValue Reduce(TValue(*rfun)(TValue, TValue), const TValue& startvalue, const string order = "NLR") const;
	void Stitch(const string order = "NLR");
	Sequence<BinaryTreeNode<TKey, TValue>*>* ConvertToSequence(const string order = "NLR") const;			
	bool RemoveSubTree(const TKey& rootkey);
	bool RemoveNode(const TKey& key);																	
	bool RemoveNode(BinaryTreeNode<TKey, TValue>* node);
	
	//BinaryTree<T>* Avl(const string order = "NLR") const;									
public:
	// деструктор
	~BinaryTree()
	{
		if(this->root)
			BinaryTreeCleaner(this->root);

		if (stitched)
			delete stitched;
	}
};




template <class TKey, class TValue>
void BinaryTree<TKey, TValue> ::BinaryTreeBuilder(BinaryTreeNode<TKey, TValue>* tree_node, BinaryTreeNode<TKey, TValue>* node)
{
	node = new BinaryTreeNode<TKey, TValue>(tree_node->GetTreeNode().key, tree_node->GetTreeNode().value);

	if (tree_node->GetLeft())
		BinaryTreeBuilder(tree_node->GetLeft(), node->GetLeft());

	if (tree_node->GetRight())
		BinaryTreeBuilder(tree_node->GetRight(), node->GetRight());
};


template <class TKey, class TValue>
void BinaryTree<TKey, TValue> ::BinaryTreeCleaner(BinaryTreeNode<TKey, TValue>* node)
{
	if (!node->GetLeft() && !node->GetRight())
		delete node;

	if (node->GetLeft())
		BinaryTreeCleaner(node->GetLeft());

	if (node->GetRight())
		BinaryTreeCleaner(node->GetRight());
};


template <class TKey, class TValue>
BinaryTree<TKey, TValue> ::BinaryTree(const BinaryTree<TKey, TValue>& tree) : root(nullptr)
{
	if (!tree.root)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);

	BinaryTreeBuilder(tree.root, this->root);

	this->stitched = nullptr;
	this->count = tree.count;
};


template <class TKey, class TValue>
BinaryTreeNode<TKey, TValue>* BinaryTree<TKey, TValue> ::GetNode(const TKey& key, BinaryTreeNode<TKey, TValue>* start) const
{
	if (!start)
		return nullptr;
	
	if (start->GetTreeNode().key == key)
		return start;
	
	BinaryTreeNode<TKey, TValue>* left = GetNode(key, start->GetLeft());
	BinaryTreeNode<TKey, TValue>* right = GetNode(key, start->GetRight());
	
	if (left)
		return left;
	
	if (right)
		return right;
	
	return nullptr;
}


template <class TKey, class TValue>
BinaryTree<TKey, TValue>* BinaryTree<TKey, TValue> ::GetSubTree(const TKey& key) const
{
	BinaryTree<TKey, TValue>* tree = new BinaryTree<TKey, TValue>();
	tree->root = this->GetNode(key);
	tree->count = GetSize(tree->root);

	return tree;
}

template<class TKey, class TValue>
int BinaryTree<TKey, TValue> ::GetSize(BinaryTreeNode< TKey, TValue>* node) const
{
	int size = 0;

	if (!node)
		return size;
	else
		size++;

	if (node->GetLeft())
		size += GetSize(node->GetLeft());
	
	if (node->GetRight())
		size += GetSize(node->GetRight());
	
	return size;
};


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::Find(const TKey& key, BinaryTreeNode<TKey, TValue>* start) const
{
	string order = "NLR";
	
	if (!start)
		return false;
	
	for (int i = 0; i < order.size(); i++)
		switch (order[i])
		{
		case 'N':
			if (start->GetTreeNode().key == key)
			{
				return true;
			}
			break;
		case 'L':
			if (Find(key, start->GetLeft()))
			{
				return true;
			}
			break;
		case 'R':
			if (Find(key, start->GetRight()))
			{
				return true;
			}
			break;
		};

	return false;
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::FindSubTree(BinaryTree<TKey, TValue>* tree) const
{
	if (!tree->root)
		return false;

	if (!this->root)
		return false;

	TKey rootkey = tree->GetRoot()->GetTreeNode().key;
	TValue rootvalue = tree->GetRoot()->GetTreeNode().value;

	BinaryTreeNode<TKey, TValue>* node = this->GetNode(rootkey);

	if (node->GetTreeNode().key == rootkey && node->GetTreeNode().value == rootvalue)
	{
		BinaryTree<TKey, TValue>* subtree = this->GetSubTree(rootkey);
		return AssertEqual(tree->root, subtree->root);
	}
	else
		return false;
}

template<class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::AssertEqual(BinaryTreeNode<TKey, TValue>* node1, BinaryTreeNode<TKey, TValue>* node2) const
{
	if (!node1 && !node2)
		return true;

	if (!node1 || !node2)
		return false;

	TKey key1 = node1->GetTreeNode().key;
	TValue value1 = node1->GetTreeNode().value;
	TKey key2 = node2->GetTreeNode().key;;
	TValue value2 = node2->GetTreeNode().value;;
	
	if (key1 == key2 && value1 == value2)
		return (AssertEqual(node1->GetLeft(), node2->GetLeft()) && AssertEqual(node1->GetRight(), node2->GetRight()));
	else
		return false;
};



template <class TKey, class TValue>
void BinaryTree<TKey, TValue> ::Round(BinaryTreeNode<TKey, TValue>* start, void (*visit)(BinaryTreeNode<TKey, TValue>*), const string order) const
{
	if (!start)
		return;

	for (int i = 0; i < order.size(); i++)
		switch (order[i])
		{
		case 'N':
			visit(start);
			break;
		case 'L':
			Round(start->GetLeft(), visit, order);
			break;
		case 'R':
			Round(start->GetRight(), visit, order);
			break;
		default:
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::Insert(BinaryTreeNode<TKey, TValue>* node)
{
	if (!node)
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	
	if (!this->root)
	{
		this->root = node;
		this->count++;
		return true;
	};

	if (Insert(node, this->root))
	{
		this->count++;
		return true;
	}
	return false;
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::Insert(const TKey& key, const TValue& item)
{
	BinaryTreeNode<TKey, TValue>* node = new BinaryTreeNode<TKey, TValue>(key, item);
	return this->Insert(node);
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue>::Insert(BinaryTreeNode<TKey, TValue>* node, BinaryTreeNode<TKey, TValue>* start)
{
	if (!node || !start)
		return false;

	if (start->GetTreeNode().key > node->GetTreeNode().key)
	{
		if (!start->GetLeft())
		{
			start->SetLeft(node);
			return true;
		}
		else
			return Insert(node, start->GetLeft());
	};
	if (start->GetTreeNode().key < node->GetTreeNode().key)
	{
		if (!start->GetRight())
		{
			start->SetRight(node);
			return true;
		}
		else
			return Insert(node, start->GetRight());
	}
	return false;
}



template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::RemoveNode(BinaryTreeNode<TKey, TValue>* node)
{
	return this->RemoveNode(node->GetTreeNode().key);
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::RemoveNode(const TKey& key)
{
	BinaryTreeNode<TKey, TValue>* node = this->GetNode(key, this->root);
	
	if (!node)
		return false;

	BinaryTreeNode<TKey, TValue>* parent = this->GetParent(node);

	// Нет дочерних узлов
	if (!node->GetLeft() && !node->GetRight())
	{
		if (parent)
		{
			if (parent->GetLeft()->GetTreeNode().key == node->GetTreeNode().key)
			{
				parent->SetLeft(nullptr);
			}
			else
			{
				parent->SetRight(nullptr);
			}
		}
	}

	// Есть один дочерний узел
	if ((node->GetLeft() && !node->GetRight()) || (!node->GetLeft() && node->GetRight()))
	{
		BinaryTreeNode<TKey, TValue>* node_child = node->GetLeft() ? node->GetLeft(): node->GetRight();
		if (parent)
		{
			if (parent->GetLeft()->GetTreeNode().key == node->GetTreeNode().key)
			{
				parent->SetLeft(node_child);
			}
			else
			{
				parent->SetRight(node_child);
			}
		}
		else
		{
			this->root = node_child;
		}
	}

	// Есть два дочерних узла
		// Поиск справа/слева подходящего родительского узла
	if (node->GetLeft() && node->GetRight())
	{
		BinaryTreeNode<TKey, TValue>* vice_node = node->GetRight();
		while (vice_node->GetLeft())
		{
			vice_node = vice_node->GetLeft();
		}

		BinaryTreeNode<TKey, TValue>* vice_node_parent = this->GetParent(vice_node);
		if (!vice_node->GetRight())
		{
			if (vice_node_parent->GetLeft()->GetTreeNode().key == vice_node->GetTreeNode().key)
			{
				vice_node_parent->SetLeft(nullptr);
			}
			else
			{
				vice_node_parent->SetRight(nullptr);
			}
		}
		else
		{
			if (vice_node_parent->GetLeft()->GetTreeNode().key == node->GetTreeNode().key)
			{
				vice_node_parent->SetLeft(vice_node->GetRight());
			}
			else
			{
				parent->SetRight(vice_node->GetRight());
			}
		}

		if (parent)
		{
			if (parent->GetLeft()->GetTreeNode().key == node->GetTreeNode().key)
			{
				parent->SetLeft(vice_node);
			}
			else
			{
				parent->SetRight(vice_node);
			}
		}
		else
		{
			this->root = vice_node;
		}
		vice_node->SetLeft(node->GetLeft());
		vice_node->SetRight(node->GetRight());
	}

	this->count--;
	delete node;
	return true;
}


template <class TKey, class TValue>
bool BinaryTree<TKey, TValue> ::RemoveSubTree(const TKey& rootkey)
{
	BinaryTreeNode<TKey, TValue>* node = this->GetNode(rootkey);

	if (!node)
		return false;

	if (this->root->GetTreeNode().key == rootkey)
	{
		this->root = nullptr;
	}
	else
	{
		BinaryTreeNode<TKey, TValue>* parent = this->GetParent(node, this->root);
	
		if (parent->GetLeft()->GetTreeNode().key == rootkey)
			parent->SetLeft(nullptr);
		else
			parent->SetRight(nullptr);
	}

	BinaryTreeCleaner(node);

	if (this->stitched)
		delete this->stitched;
	
	this->count = this->GetSize(this->root);
	
	return true;
}


template <class TKey, class TValue>
BinaryTree<TKey, TValue>* BinaryTree<TKey, TValue> ::Map(BinaryTreeNode<TKey, TValue>* (*mfun)(BinaryTreeNode<TKey, TValue>*)) const
{
	BinaryTree<TKey, TValue>* new_tree = new BinaryTree<TKey, TValue>();
	new_tree->root = Map(this->root, mfun);
	new_tree->count = this->count;
	return new_tree;
}


template <class TKey, class TValue>
BinaryTree<TKey, TValue>* BinaryTree<TKey, TValue> ::Where(bool (*wfun)(BinaryTreeNode <TKey, TValue>*)) const
{
	BinaryTree<TKey, TValue>* result = new BinaryTree<TKey, TValue>();
	Where(this->root, result, wfun);
	result->count = GetSize(result->root);
	return result;
}



template <class TKey, class TValue>
TValue BinaryTree<TKey, TValue> ::Reduce(TValue(*rfun)(TValue, TValue), const TValue& startvalue, const string order) const
{
	if (!this->root)
		return 0;

	return Reduce(this->root, rfun, startvalue, order);
}



template <class TKey, class TValue>
void BinaryTree<TKey, TValue> ::Stitch(const string order)
{
	if (!this->root)
		throw NoneValue("***ValueError: there is not value of argument in the binary tree***", __FILE__, __LINE__);

	Sequence<BinaryTreeNode<TKey, TValue>*>* seq = new ListSequence<BinaryTreeNode<TKey, TValue>*>();
	this->Stitch(this->root, seq, order);
	this->stitched = seq;
}


template <class TKey, class TValue>
Sequence<BinaryTreeNode<TKey, TValue>*>* BinaryTree<TKey, TValue> :: ConvertToSequence(const string order) const 
{
	Sequence<BinaryTreeNode<TKey, TValue>*>* seq = new ListSequence<BinaryTreeNode<TKey, TValue>*>();
	this->Stitch(this->root, seq, order);
	return seq;
}


template <class TKey, class TValue>
BinaryTreeNode<TKey, TValue>* BinaryTree<TKey, TValue>::GetParent(BinaryTreeNode<TKey, TValue>* child, BinaryTreeNode<TKey, TValue>* start) const
{
	if (!child || !start)
		return nullptr;

	if (!start->GetLeft() && !start->GetRight())
		return nullptr;

	TKey childkey = child->GetTreeNode().key;
		
	if (start->GetLeft())
	{
		if (start->GetLeft()->GetTreeNode().key == childkey)
			return start;
		
		BinaryTreeNode<TKey, TValue>* left = GetParent(child, start->GetLeft());
		if (left)
			return left;
	};

	if (start->GetRight())
	{
		if (start->GetRight()->GetTreeNode().key == childkey)
			return start;
		
		BinaryTreeNode<TKey, TValue>* right = GetParent(child, start->GetRight());
		if (right)
			return right;
	};

	return nullptr;
}



template <class TKey, class TValue>
BinaryTreeNode<TKey, TValue>* BinaryTree<TKey, TValue>::Map(BinaryTreeNode<TKey, TValue>* node, BinaryTreeNode<TKey, TValue>* (*mfun)(BinaryTreeNode<TKey, TValue>*)) const
{
	if (!node)
		return nullptr;
	
	string order = "NLR";
	BinaryTreeNode<TKey, TValue>* new_node = nullptr;

	for (int i = 0; i < order.size(); i++)
		switch (order[i])
		{
		case 'N':
			new_node = mfun(node);
			break;
		case 'L':
			new_node->SetLeft(Map(node->GetLeft(), mfun));
			break;
		case 'R':
			new_node->SetRight(Map(node->GetRight(), mfun));
			break;
		default:
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}
	
	return new_node;
}


template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::Where(BinaryTreeNode<TKey, TValue>* node, BinaryTree<TKey, TValue>* result, bool (*wfun)(BinaryTreeNode<TKey, TValue>*)) const
{
	if (!node)
		return; 
	
	string order = "NLR";
	
	for (int i = 0; i < order.size(); i++)
		switch (order[i]) {
		case 'N':
			if (wfun(node)) 
			{
				BinaryTreeNode<TKey, TValue>* new_node = new BinaryTreeNode<TKey, TValue>(node->GetTreeNode().key, node->GetTreeNode().value);
				result->Insert(new_node);
			};
			break;
		case 'L':
			Where(node->GetLeft(), result, wfun);
			break;
		case 'R':
			Where(node->GetRight(), result, wfun);
			break;
		default:
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}
}


template<class TKey, class TValue>
TValue BinaryTree<TKey, TValue> :: Reduce(BinaryTreeNode<TKey, TValue>* node, TValue(*rfun)(TValue, TValue), const TValue& value, const string order) const
{
	if (!node)
		return 0;
	
	int result = 0;

	for (int i = 0; i < size(order); i++)
		switch (order[i])
		{
		case 'N':
			TValue node_value = node->GetTreeNode().value;
			result += rfun(value, node_value);
			break;
		case 'L':
			result += Reduce(node->GetLeft(), rfun, result, order);
			break;
		case 'R':
			result += Reduce(node->GetRight(), rfun, result, order);
			break;
		default:
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}

	return result;
}


template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::Stitch(BinaryTreeNode<TKey, TValue>* node, Sequence<BinaryTreeNode<TKey, TValue>*>* seq, const string order) 
{
	if (!node)
		return;

	for (int i = 0; i < order.size(); i++)
	{
		switch (order[i])
		{
		case 'N':
			seq->Append(node);
			break;
		case 'L':
			Stitch(node->GetLeft(), seq, order);
			break;
		case 'R':
			Stitch(node->GetRight(), seq, order);
			break;
		default:
			throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
		}
	}
}