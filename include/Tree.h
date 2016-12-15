
#include "Node.h"

class Tree
{
	private:
		Node *root;
	
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
			std::cout << "tree destroyed" << std::endl;
		}
		
		bool insert(std::string key)
		{
			return insert(root, key);
		}

		bool remove(std::string key)
		{
			return remove(root, key);
		}

		void print()
		{
			print(root);
		}

	private:

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

		bool insert(Node *&root, std::string key)
		{
			if(!root)
			{
				root = new Node(key);

				return true;
			}
			else if(key < root->key)
			{
				return insert(root->left, key);
			}
			else if(key > root->key)
			{
				return insert(root->right, key);
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
				std::cout << root->key << std::endl;

				print(root->left);
				print(root->right);
			}
		}

};
