
#include "Tree.h"

Tree::Tree()
{
	std::cout << "created" << std::endl;
	this -> root = NULL;
	this -> height = 0;
}

Tree::~Tree()
{
	std::cout << "tree_destroyed" << std::endl;
}

Node *Tree::getRoot()
{
	return this -> root;
}

int Tree::getHeight()
{
	return this -> height;
}

void Tree::setHeight(int height)
{
	this -> height = height;
}

void Tree::insert(Node *root, string key)
{
	
}

void Tree::print(Node *root)
{
	
}