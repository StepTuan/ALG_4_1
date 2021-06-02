#pragma once
#include <iostream>
using namespace std;

enum color 
{ 
	RED, BLACK 
};

struct Node
{
	int key;
	char value;
	color color;
	Node* left;
	Node* right;
	Node* parent;
};

class RBtree
{
public:
	RBtree() :root(nullptr) {};				// constructor
	void insert(int key, char value);		// method for adding an item with key and value
	void remove(int x);						// method for deleting a tree element by key
	void find(int key);						// method to find an element by key
	void clear();							// method for clearing an associative array
	void get_keys();						// method returns a list of keys 
	void get_values();						// method returns a list of values
	void print();							// console output
	~RBtree();								// destructor
	Node* root;								// pointer
	bool findNode(int x);					// method for checking if a node is present
private:
	Node* balancing(Node*);					// balancing method
	void insertfix(Node*);					// balancing method after adding a node
	void deletefix(Node*);					// balancing method after node removal
	void leftrotate(Node*);					// left turn
	void rightrotate(Node*);				// right turn
	void insert(Node*);						// method for adding a node to a tree
	void keys(Node*);						// key output method
	void values(Node*);						// value output method
	void printNode(Node*);					// node output method
	void destruct(Node*);					// method for the destructor
}; 

Node* RBtree::balancing(Node* node)
{
	Node* y = NULL;					
	if (node->left != NULL)
	{
		y = node->left;
		while (y->right != NULL)
			y = y->right;
	}
	else							
	{
		y = node->right;
		while (y->left != NULL)
			y = y->left;
	}
	return y;
}

void RBtree::insertfix(Node* t)
{
	Node* uncle = NULL;
	if (root == t) 
	{
		t->color = BLACK;
		t->parent = NULL;
		return;
	}
	while (t->parent != NULL && t->parent->color == RED)
	{
		Node* grandpa = t->parent->parent;	
		if (grandpa->left == t->parent)		
		{
			if (grandpa->right != NULL)		
			{
				uncle = grandpa->right;		
				if (uncle->color == RED)	
				{
					t->parent->color = BLACK;	
					uncle->color = BLACK;		
					grandpa->color = RED;		
					t = grandpa;
				}
			}
			else  
			{
				if (t->parent->right == t)  
				{
					t = t->parent;
					leftrotate(t);
				}
				t->parent->color = BLACK;	
				grandpa->color = RED;		
				rightrotate(grandpa);		
			}
		}
		else  
		{
			if (grandpa->left != NULL)
			{
				uncle = grandpa->left;
				if (uncle->color == RED)
				{
					t->parent->color = BLACK;
					uncle->color = BLACK;
					grandpa->color = RED;
					t = grandpa;
				}
			}
			else
			{
				if (t->parent->left == t)
				{
					t = t->parent;
					rightrotate(t);
				}
				t->parent->color = BLACK;
				grandpa->color = RED;
				leftrotate(grandpa);
			}
		}
		root->color = BLACK;
		root->parent = NULL;
	}
}

void RBtree::deletefix(Node* node)
{
	Node* s = NULL;
	while (node != NULL && node != root && node->color == BLACK)	
	{
		if (node->parent->left == node)
		{
			s = node->parent->right;
			if (s->color == RED)	
			{
				s->color = BLACK;		
				node->parent->color = RED;
				leftrotate(node->parent);
				s = node->parent->right;
			}
			if (s->right->color == BLACK && s->left->color == BLACK)  
			{
				s->color = RED; 
				node = node->parent;
			}
			else
			{
				if (s->right->color == BLACK)	
				{
					s->left->color = BLACK; 
					s->color = RED;			
					rightrotate(s);			
					s = node->parent->right;
				}
				s->color = node->parent->color;
				node->parent->color = BLACK;
				s->right->color = BLACK;
				leftrotate(node->parent);
				node = root;
			}
		}
		else 
		{
			s = node->parent->left;
			if (s->color == RED)
			{
				s->color = BLACK;
				node->parent->color = RED;
				rightrotate(node->parent);
				s = node->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				node = node->parent;
			}
			else
			{
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					leftrotate(s);
					s = node->parent->left;
				}
				s->color = node->parent->color;
				node->parent->color = BLACK;
				s->left->color = BLACK;
				rightrotate(node->parent);
				node = root;
			}
		}
		node->color = BLACK;
		root->color = BLACK;
		root->parent = NULL;
	}
}

void RBtree::leftrotate(Node* node)
{
	if (node->right == NULL)
		return;
	else
	{
		Node* y = node->right;
		if (y->left != NULL)
		{
			node->right = y->left;
			y->left->parent = node;
		}
		else
			node->right = NULL;
		if (node->parent != NULL)
			y->parent = node->parent;
		if (node->parent == NULL)
			root = y;
		else
		{
			if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;
		}
		y->left = node;
		node->parent = y;
	}
}

void RBtree::rightrotate(Node* node)
{
	if (node->left == NULL)
		return;
	else
	{
		Node* y = node->left;
		if (y->right != NULL)
		{
			node->left = y->right;
			y->right->parent = node;
		}
		else
			node->left = NULL;
		if (node->parent != NULL)
			y->parent = node->parent;
		if (node->parent == NULL)
			root = y;
		else
		{
			if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;
		}
		y->right = node;
		node->parent = y;
	}
}

void RBtree::insert(int key, char value)  
{
	Node* t = new Node;
	t->key = key;
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	t->color = RED;
	if (findNode(t->key))
		delete t;
	else
		insert(t);				
}

void RBtree::insert(Node* t)
{
	Node* rootCopy = root, * q = NULL;
	if (root == NULL)  
	{
		root = t;
		t->parent = NULL;
	}
	else  
	{
		while (rootCopy != NULL)	
		{
			q = rootCopy;
			if (rootCopy->key < t->key)		
				rootCopy = rootCopy->right;
			else								
				rootCopy = rootCopy->left;
		}
		t->parent = q;						
		if (q->key < t->key)				
			q->right = t;
		else								
			q->left = t;
	}
	insertfix(t);
}

void RBtree::clear()
{
	while (root)
		remove(root->key);
}

void RBtree::remove(int x)
{
	if (root == NULL)
	{
		cout << "\nThe tree is empty, deletion is impossible!";
		return;
	}
	Node* node = root;
	Node* y = NULL;
	Node* q = NULL;
	bool found = false;
	while (node != NULL && found == false)
	{
		if (node->key == x)
			found = true;
		if (found == false)
		{
			if (node->key < x)
				node = node->right;
			else
				node = node->left;
		}
	}
	if (found == false)
	{
		cout << "\nNo such item exists in the tree!";
		return;
	}
	else
	{
		cout << "\nDeleted item: " << node->key << " " << node->value;

		if (node->left == NULL || node->right == NULL)
			y = node;
		else
			y = balancing(node);
		if (y->left != NULL)		
			q = y->left;
		else						
		{
			if (y->right != NULL)	
				q = y->right;
			else					
				q = NULL;
		}
		if (q != NULL)		
			q->parent = y->parent;
		if (y->parent == NULL)			
			root = q;
		else							
		{
			if (y == y->parent->left)	
				y->parent->left = q;
			else						
				y->parent->right = q;
		}
		if (y != node)
		{
			node->color = y->color;
			node->key = y->key;
		}
		if (y->color == BLACK)
			deletefix(q);
	}

}

bool RBtree::findNode(int x)
{
	if (root == NULL)
		return false;
	Node* node = root;
	bool found = false;
	while (node != NULL && found == false)
	{
		if (node->key == x)
			found = true;
		if (found == false)
		{
			if (node->key < x)
				node = node->right;
			else
				node = node->left;
		}
	}
	if (found == false)
		return false;
	else
		return true;
}

void RBtree::find(int x)
{
	if (root == NULL)
	{
		cout << "\nThe tree is empty!";
		return;
	}
	Node* node = root;
	bool found = false;
	while (node != NULL && found == false)
	{
		if (node->key == x)
			found = true;
		if (found == false)
		{
			if (node->key < x)
				node = node->right;
			else
				node = node->left;
		}
	}
	if (found == false)
	{
		cout << "\nNode not found!";
		return;
	}
	else
	{
		cout << "\nSearched node: " << node->key << " " << node->value;
	}
}

void RBtree::get_keys()
{
	keys(root);
}

void RBtree::keys(Node* node)
{
	if (root == NULL)
	{
		cout << "\nThe tree is empty!";
		return;
	}
	if (node != NULL)
	{
		cout << "\n" << node->key ;
		if (node->left)
		{
			keys(node->left);
		}
		if (node->right)
		{
			keys(node->right);
		}
	};
}

void RBtree::get_values()
{
	values(root);
}

void RBtree::values(Node* node)
{
	if (root == NULL)
	{
		cout << "\nThe tree is empty!";
		return;
	}
	if (node != NULL)
	{
		cout << "\n" << node->value;
		if (node->left)
		{
			values(node->left);
		}
		if (node->right)
		{
			values(node->right);
		}
	};
}

void RBtree::print()
{
	printNode(root);
}

void RBtree::printNode(Node* node)
{
	if (root == NULL)
	{
		cout << "\nThe tree is empty!";
		return;
	}
	if (node != NULL)
	{
		if (node == root)
			cout << "\n" << node->key << " " << node->value;
		else
			cout << "\n" << node->key << " " << node->value;
		if (node->left)
		{
			printNode(node->left);
		}
		if (node->right)
		{
			printNode(node->right);
		}
	}
}

RBtree::~RBtree() 
{
	if (root != NULL)
	{
		destruct(root); 
	}
}

void RBtree::destruct(Node* current) 
{
	if (current != nullptr)
	{
		destruct(current->left);
		destruct(current->right);
		delete current;
	}
}

#pragma once