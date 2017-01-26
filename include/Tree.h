
#include "Node.h"

class Tree
{

	public:

		Tree(std::string key, std::string txt)
		{
			root = new Node(key, txt);
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
			if(root)
			{
				for(int i = 0; i <= root->height; i ++)
				{
					print(root, 0, i);
					std::cout << std::endl;
				}
			}
		}

		LinkedList * search(LinkedList *lastSearchList, Tokenizer tokenizer)
		{
			LinkedList *list = NULL;

 			if(tokenizer.hasNext())
 			{

				if(Node *found = get(root, tokenizer.getNext()))
				{
					list = found->list.clone();
					if(list)
					{
						while(tokenizer.hasNext())
						{
							if(found = get(root, tokenizer.getNext()))
							{
								LinkedList *crossmatch = found->list.clone();
								if(crossmatch)
								{
									Record *record = list->getRecord();
									while(record)
									{
										Record *crossRecord = crossmatch->getRecord();
										bool found = false;
										while(crossRecord)
										{
											if(record->getText().compare(crossRecord->getText()) == 0)
												found = true;
											crossRecord = crossRecord->getNext();
										}
										if(!found)
										{
											list->remove(record->getText());
										}
										record = record->getNext();
									}
									delete crossmatch;
									crossmatch = NULL;
								}
								else
								{
									delete list;
									list = NULL;
								}
							}
						}
					}
				}
				else
				{
					//change!
					std::cout << "NOT FOUND" << std::endl;
				}

			}
			else
			{
				std::cout << "please enter in some terms" << std::endl;
			}

			return list;
		}

	private:
		Node *root;

		Node * get(Node *root, std::string key)
		{
			if(!root)
			{
				return root;
			}
			else if(key.compare(root->key) < 0)
			{
				return get(root->left, key);
			}
			else if(key.compare(root->key) > 0)
			{
				return get(root->right, key);
			}
			else
			{
				return root;
			}
		}

		void destroy(Node *&root)
		{
			if(root)
			{
				destroy(root->left);
				destroy(root->right);

				delete root;
				root = NULL;
			}
		}

		bool insert(Node *&root, std::string key, string txt)
		{
			bool result=false;
			if(!root)
			{
				root = new Node(key, txt);

				return true;
			}
			else if(key.compare(root->key) < 0)
			{
				result = insert(root->left, key, txt);
			}
			else if(key.compare(root->key) > 0)
			{
				result = insert(root->right, key, txt);
			}
			else
			{
				root->addText(txt);
				root->freq ++;

				return true;
			}
			if(!root)
				return result;

			root->height = root->getHeight();

			int balance = root->getBalance();

			if(balance > 1 && key < root->left->key)
	        {
	                root = rotateRight(root);
	        }
	        else if(balance < -1 && key > root->right->key)
	        {
	                root = rotateLeft(root);
	        }
	        else if(balance > 1 && key > root->left->key)
	        {
	                root->left = rotateLeft(root->left);
	                root = rotateRight(root);
	        }
	        else if(balance < -1 && key < root->right->key)
	        {
	                root->right = rotateRight(root->right);
	                root = rotateLeft(root);
	        }


			return result;
		}

		Node * rotateRight(Node *&root)
		{
			Node *leftChild = root->left;

			root->left = leftChild->right;

			leftChild->right = root;

			leftChild->height = leftChild->getHeight();
			root->height = root->getHeight();

			return leftChild;
		}

		Node * rotateLeft(Node *root)
		{
			Node *rightChild = root->right;
			root->right = rightChild->left;

			rightChild->left = root;

			rightChild->height = rightChild->getHeight();
			root->height = root->getHeight();

			return rightChild;
		}

		bool remove(Node *&root, std::string key)
		{
			bool result = false;
			if(!root)
			{
				std::cout << "node_not_found" << std::endl;

				return false;
			}
			else if(key.compare(root->key) < 0)
			{
				result = remove(root->left, key);
			}
			else if(key.compare(root->key) > 0)
			{
				result = remove(root->right, key);
			}
			else
			{
				if(root->freq == 1)
                {
                    if(!root->left || !root->right)
                    {

                            Node *temp = root->left ? root->left : root->right;

                            if(!temp)
                            {
                                    delete root;
                                    root = NULL;
                            }
                            else
                            {
                                    *root = *temp;
                            }

                            delete temp;
                    }
                    else
                    {
                            Node *temp = findMin(root->right);

                            root->key = temp->key;
                            root->freq = temp->freq;
                            temp->freq = 1;

                            result = remove(root->right, temp->key);
                    }
                }
                else
                {
                        root->freq --;
                }
            }

            if(root == NULL)
            	return result;

            root->height = root->getHeight();

			int balance = root->getBalance();

			if(balance > 1 && key.compare(root->left->key) < 0)
	        {
	            root = rotateRight(root);
	        }
	        else if(balance < -1 && key.compare(root->right->key) > 0)
	        {
	            root = rotateLeft(root);
	        }
	        else if(balance > 1 && key.compare(root->left->key) > 0)
	        {
	            root->left = rotateLeft(root->left);
	            root = rotateRight(root);
	        }
	        else if(balance < -1 && key.compare(root->right->key) < 0)
	        {
	            root->right = rotateRight(root->right);
	            root = rotateLeft(root);
        	}

			return result;
		}

		Node * findMin(Node *root)
		{
			if(root->left)
			{
				Node *found = findMin(root->left);
			}
			else
			{
				return root;
			}
		}

		void print(Node *root, int depth, int height)
		{
			if(depth == height)
			{
				if(root)
				{
					std::cout << root->key << " ";
					//root->printList();
					//std::cout << std::endl;
				}
				else
				{
					std::cout << "N ";
				}
			}
			if(root)
			{
				print(root->left, depth + 1, height);
				print(root->right, depth + 1, height);
			}
		}

};
