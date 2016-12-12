
#include <iostream>

#include "Tree.h"

int main()
{
	
	Tree tree;
	std::cout << tree.getHeight() << std::endl;
	
	Node node("hello");
	std::cout << node.getKey() << std::endl;
	
	return 0;
}