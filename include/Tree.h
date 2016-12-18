
#include "Node.h"

class Tree
{
	
	public:

		Tree(std::string key)
		{
			root = new Node(key);
		}

		Tree()
		{
			root = NULL;
		}
		
		~Tree()
		{
			destroy(root);
		}
		
		bool isEmpty()
		{
			if(root)
				return false;
			return true;
		}

		bool insert(std::string key, std::string txt)
		{
			return insert(root, key, txt);
		}

		bool remove(std::string key)
		{
			return remove(root, key);
		}

		void destroy()
		{
			destroy(root);
			std::cout << "tree destroyed" << std::endl;
		}

		void print()
		{
			print(root);
		}

	private:
		Node *root;

		void destroy(Node *&root)
		{
			if(root)
			{
				delete(root->left);
				delete(root->right);

				delete root;
				root = NULL;
			}
		}

		bool insert(Node *&root, std::string key, string txt)
		{
			if(!root)
			{
				root = new Node(key);
				root->addText(txt);

				return true;
			}
			else if(key < root->key)
			{
				return insert(root->left, key, txt);
			}
			else if(key > root->key)
			{
				return insert(root->right, key, txt);
			}
			else
			{
				root->addText(txt);
				root->freq ++;

				return true;
			}

			return false;
		}

		bool remove(Node *&root, std::string key)
		{
			if(!root)
			{
				std::cout << "node_not_found" << std::endl;

				return false;
			}
			else if(key < root->key)
			{
				return remove(root->left, key);
			}
			else if(key > root->key)
			{
				return remove(root->right, key);
			}
			else
			{
				delete root;
				root = NULL;
				return true;
			}
		}

		void print(Node *root)
		{
			if(!root)
			{
				return;
			}
			else
			{
				std::cout << "key '" << root->key << "'" << std::endl;

				print(root->left);
				print(root->right);
			}
		}

};
