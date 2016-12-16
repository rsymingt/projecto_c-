
#include <iostream>
#include <limits>

#include "Tree.h"

int main()
{
	
	Tree tree;

	std::string usr_input;

	do{
		std::cin >> usr_input;
		if(usr_input == "insert")
		{
			std::cin >> usr_input;
			if(tree.insert(usr_input))
				std::cout << "inserted_" << usr_input << "_successfully" << std::endl;
		}
		else if(usr_input == "print")
		{
			if(!std::cin.eofbit)
			{
				std::cout << "goodbit" << std::endl;
				std::cin >> usr_input;
				if(usr_input == "tree")
				{
					tree.print();
				}
			}
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	}while(usr_input != "q");

	return 0;
}