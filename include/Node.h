
#include "LinkedList.h"

class Node
{
		
	private:
		Node *left;
		Node *right;
		LinkedList list;

		std::string key;
		int height;
		int freq;

	public:
		void addText(string txt)
		{
			list.insert(txt);
		}

		void printList()
		{
			list.print();
		}

		Node(std::string key)
		{
			this->key = key;
			this->height = 0;

			left = NULL;
			right = NULL;
		}

		~Node()
		{
		}
		
		friend class Tree;
};