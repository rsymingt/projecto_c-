
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

		int getHeight(Node *root)
		{
			if(!root)
			{
				return 0;
			}
			else
			{
				int leftH = 1 + getHeight(root->left);
				int rightH = 1 + getHeight(root->right);
				if(leftH > rightH)
					return leftH;
				return rightH;
			}
		}

	public:
		void addText(string txt)
		{
			list.insert(txt);
		}

		void printList()
		{
			list.print();
		}

		int getHeight()
		{
			return getHeight(this) - 1;
		}

		int getBalance()
		{
			if(left && right)
				return (left->height - right->height);
			else if(left)
				return (left->height);
			else if(right)
				return -(right->height);
			else
				return 0;
		}

		void rotateRight()
		{

		}

		Node(std::string key, std::string txt)
		{
			this->key = key;
			list.insert(txt);

			height = 0;
			freq = 1;

			left = NULL;
			right = NULL;
		}

		~Node()
		{
		}

		friend class Tree;
};
