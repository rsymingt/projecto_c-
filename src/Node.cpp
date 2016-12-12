
#include "Node.h"

Node::Node(std::string key)
{
	setKey(key);
	
	this -> parent = NULL;
	this -> left = NULL;
	this -> right = NULL;
}

Node::~Node()
{
	std::cout << "node destroyed" << std::endl;
}

std::string Node::getKey()
{
	return this -> key;
}

void Node::setKey(std::string key)
{
	this -> key = key;
}