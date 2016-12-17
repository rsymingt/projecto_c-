
class Node
{
		
	private:
		Node *left;
		Node *right;
		std::string key;
		short int height;

	public:
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