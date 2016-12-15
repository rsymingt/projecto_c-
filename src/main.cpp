
#include <iostream>

#include "Tree.h"

int main()
{
	
	Tree tree;

	std::string usr_input;

	do{

		std::cin >> usr_input;

		if(usr_input == "insert")
		{
			if(int i = usr_input.find(" "))
			{
				std::cout << "YAY" << std::endl;
			}
			tree.insert(usr_input);
		}

	}while(usr_input != "q");

	return 0;
}