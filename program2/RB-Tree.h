#pragma once
#include "List.h"
#include <iostream>

enum Color { BLACK, RED };

template<class key_type, class data_type>
class Tree_Node
{
public:

	~Tree_Node() 
	{
		Clear();
	}

	void left_rorate(Tree_Node* x);
	void right_rorate(Tree_Node* y);

	// INSERT
	void Insert(key_type key, data_type data);
	void Insert_FIXUP(Tree_Node* node);

	// REMOVE
	void Remove(key_type key);
	void Transplant(Tree_Node* u, Tree_Node* v);
	Tree_Node* Tree_Minimum(Tree_Node* node);
	void Delete_FIXUP(Tree_Node* node);

	// FIND
	data_type Find(key_type key);
	Tree_Node* Find_Node(key_type key);

	// CLEAR
	void Clear();

	// GET KEYS
	void Get_Keys(Tree_Node* node, List<key_type>* keys);

	// GET VALUES
	void Get_Values(Tree_Node* node, List<data_type>* values);

	// PRINT
	void Print(Tree_Node* node);

	Tree_Node* Get_Parent() { return this->parent; }
	Tree_Node* Get_Root() { return this->root; }
	Tree_Node* Get_Nil() { return this->nil; }
	size_t Get_Size() { return this->size; }

	void Nil_Creating()
	{
		this->nil = new Tree_Node;
		this->nil->color = BLACK;
		this->root = nil;
	}
	
	template<class A_type>
	void A_input(Tree_Node* node, A_type* array, size_t check);

	data_type& operator[] (const key_type key)
	{
		Tree_Node* node = Find_Node(key);
		return node->data;
	}

	void operator = (data_type new_data)
	{
		data = new_data;
	}
private:
	Tree_Node* root;
	Tree_Node* parent;
	Tree_Node* right;
	Tree_Node* left;
	Tree_Node* nil;
	Color color;
	data_type data;
	key_type key;
	size_t size;
};


// check == 0 is data, check == 1 is key
template<class key_type, class data_type>
template<class A_type>
inline void Tree_Node<key_type, data_type>::A_input(Tree_Node* node, A_type* array, size_t check)
{
	static int i = 0;
	if (check == 0)
	{
		if (node->Get_Parent() == nullptr)
			throw "RB Tree is empty";
		if (node == this->nil)
			return;
		else
		{
			array[i++] = node->data;
			if (node->left != this->nil)
				A_input(node->left, array, check);
		}
		if (node->right != this->nil)
			A_input(node->right, array, check);
	}
	else if (check == 1)
	{
		if (node->Get_Parent() == nullptr)
			throw "RB Tree is empty";
		if (node == this->nil)
			return;
		else
		{
			array[i++] = node->key;
			if (node->left != this->nil)
				A_input(node->left, array, check);
		}
		if (node->right != this->nil)
			A_input(node->right, array, check);
	}
}

#include "RB-Tree.inl"


