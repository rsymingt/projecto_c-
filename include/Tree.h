
#include "Node.h"

class Tree
{
	private:
		int height;
	
	public:
		Node *root;
		
		Node *getRoot();
		
		int getHeight();
		void setHeight(int);
		
		void insert(Node*, string);
		void print(Node*);
		
		Tree();
		~Tree();
};
