
#include <iostream>

class Node
{
		
	private:
		std::string key;
		static short int height;
		
	public:
		Node *parent;
		Node *left;
		Node *right;
		
		std::string getKey();
		void setKey(std::string);
		
		Node(std::string);
		~Node();

};