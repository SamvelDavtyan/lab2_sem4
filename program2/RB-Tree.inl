#pragma once
#include "RB-Tree.h"

using namespace std;

//Restoring the properties of red-black tree
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::left_rorate(Tree_Node* x)
{
	Tree_Node* y;
	y = x->right;
	x->right = y->left;
	if (y->left != this->nil)
		y->left->parent = x;
	if (y != this->nil)
		y->parent = x->parent;
	if (x->parent == this->nil)
		this->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	if (x != this->nil)
		x->parent = y;
}

//Restoring the properties of red-black tree
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::right_rorate(Tree_Node* x)
{
	Tree_Node* y;
	y = x->left;
	x->left = y->right;
	if (y->right != this->nil)
		y->right->parent = x;
	if (y != this->nil)
		y->parent = x->parent;
	if (x->parent == this->nil)
		this->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	if (x != this->nil)
		x->parent = y;
}

//Adding an element with a key and value
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Insert(key_type key, data_type data)
{
	Tree_Node* x, * y;
	y = this->nil;
	x = this->root;
	Tree_Node* New_Node = new Tree_Node;
	New_Node->key = key;
	New_Node->data = data;
	while (x != this->nil)
	{
		y = x;
		if (New_Node->key == x->key)
			throw 0;
		if (New_Node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	New_Node->parent = y;
	if (y == this->nil)
		this->root = New_Node;
	else if (New_Node->key < y->key)
		y->left = New_Node;
	else
		y->right = New_Node;
	New_Node->left = this->nil;
	New_Node->right = this->nil;
	New_Node->color = RED;
	Insert_FIXUP(New_Node);
	this->size++;
}

//Restoring the properties of the red-black tree when adding an element
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Insert_FIXUP(Tree_Node* node)
{
	while (node->parent->color == RED && node != this->root)
	{
		if (node->parent == node->parent->parent->left)
		{
			Tree_Node* y = node->parent->parent->right;
			if (y->color == RED)
			{
				node->parent->color = BLACK;              
				y->color = BLACK;						
				node->parent->parent->color = RED;		
				node = node->parent->parent;		   
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;             
					left_rorate(node);              
				}
				node->parent->color = BLACK;          
				node->parent->parent->color = RED;   
				right_rorate(node->parent->parent);    
			}
		}
		else
		{
			Tree_Node* y = node->parent->parent->left;
			if (y->color == RED)
			{
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					right_rorate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				left_rorate(node->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

//Moving subtrees
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Transplant(Tree_Node* u, Tree_Node* v)
{
	if (u->parent == this->nil)
		this->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

//Search for an element by key
template<class key_type, class data_type>
data_type Tree_Node<key_type, data_type>::Find(key_type key)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	else
	{
		Tree_Node* temp = this->root;
		while (temp->key != key)
		{
			if (key > temp->key)
				temp = temp->right;
			else
				temp = temp->left;
			if (temp == this->nil)
				throw "Node not found.";
		}
		return temp->data;
	}
}

template<class key_type, class data_type>
Tree_Node<key_type, data_type>* Tree_Node<key_type, data_type>::Find_Node(key_type key)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	else
	{
		Tree_Node* temp = this->root;
		while (temp->key != key)
		{
			if (key > temp->key)
				temp = temp->right;
			else
				temp = temp->left;
			if (temp == this->nil)
				throw "Node not found.";
		}
		return temp;
	}
}

//Clearing a map
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Clear()
{
	while (this->root != this->nil)
		Remove(root->key);
}

//Returning a list of keys
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Get_Keys(Tree_Node* node, List<key_type>* keys)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	if (node == this->nil)
		return;
	else
	{
		keys->push_back(node->key);
		if (node->left != this->nil)
			Get_Keys(node->left, keys);
	}
	if (node->right != this->nil)
		Get_Keys(node->right, keys);
}

//Returning a list of values
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Get_Values(Tree_Node* node, List<data_type>* values)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	if (node == this->nil)
		return;
	else
	{
		values->push_back(node->data);
		if (node->left != this->nil)
			Get_Values(node->left, values);
	}
	if (node->right != this->nil)
		Get_Values(node->right, values);
}

//Print to console
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Print(Tree_Node* node)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	if (node == this->nil)
		return;
	else
	{

		cout << "Key = " << node->key << ", data = " << node->data;
		if (node->color == 0)
			cout<< ", color = BLACK" << endl;
		if (node->color == 1)
			cout << ", color = RED" << endl;
		if (node->left != this->nil)
			Print(node->left);
	}
	if (node->right != this->nil)
		Print(node->right);
}

//Deleting a tree element by key
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Remove(key_type key)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	Tree_Node* y, * x;
	Tree_Node* z = this->root;
	while (z->key != key)
	{
		if (key > z->key)
			z = z->right;
		else
			z = z->left;
		if (z == this->nil)
			throw "Node not found.";
	}
	y = z;
	Color y_original_color = y->color;
	if (z->left == this->nil)
	{
		x = z->right;
		Transplant(z, z->right);
	}
	else if (z->right == this->nil)
	{
		x = z->left;
		Transplant(z, z->left);
	}
	else
	{
		y = Tree_Minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_original_color == BLACK)
		Delete_FIXUP(x);
	this->size--;
}

//Search for the minimum element of a subtree
template<class key_type, class data_type>
Tree_Node<key_type, data_type>* Tree_Node<key_type, data_type>::Tree_Minimum(Tree_Node* node)
{
	if (this->root == this->nil)
		throw "RB Tree is empty.";
	else
	{
		while (node->left != this->nil)
			node = node->left;
		return node;
	}
}

//Restoring the properties of the red-black tree when deleting an element
template<class key_type, class data_type>
void Tree_Node<key_type, data_type>::Delete_FIXUP(Tree_Node* x)
{
	while (x != this->root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			Tree_Node* w;
			w = x->parent->right;
			if (w->color == RED)
			{
				w->color = BLACK;					
				x->parent->color = RED;				
				left_rorate(x->parent);				
				w = x->parent->right;				
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;				
				x = x->parent;				
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;			
					w->color = RED;					
					right_rorate(w);				
					w = x->parent->right;			
				}
				w->color = x->parent->color;		
				x->parent->color = BLACK;			
				w->right->color = BLACK;			
				left_rorate(x->parent);				
				x = this->root;						
			}
		}
		else
		{
			Tree_Node* w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;					
				x->parent->color = RED;				
				right_rorate(x->parent);			
				w = x->parent->left;				
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;				
				x = x->parent;				
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;			
					w->color = RED;						
					left_rorate(w);						
					w = x->parent->left;				
				}
				w->color = x->parent->color;			
				x->parent->color = BLACK;				
				w->left->color = BLACK;					
				right_rorate(x->parent);				
				x = this->root;							
			}
		}
	}
	x->color = BLACK;
}