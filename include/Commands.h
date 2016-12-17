
#include "Tree.h"

using std::string;
using std::cout;
using std::endl;

class Commands
{
	
	private:

		string list[3];
		string subCommands[3];

		Tree tree;

		void init()
		{
			list[0] = "print";
			list[1] = "insert";
			list[2] = "remove";

			subCommands[0] =
			"print 'name'";

			subCommands[1] =
			"insert [option] 'name'\n\n"
			"options\n"
			"-t    - inserts to object of type tree";

			subCommands[2] =
			"remove [option] 'name'\n\n"
			"options\n"
			"-t    - removes from object of type tree\n"
			"-r    - resets the tree";
		}

		void help(string str)
		{
			for(int i = 0; i < str.size() ; i ++)
			{
				if(list[i] == str)
				{
					std::cout << "here is a list of some common print commands" << std::endl;
					cout << subCommands[i] << endl;
				}
			}
		}

		bool exists(string str)
		{
			for(int i = 0; i < sizeof(list)/sizeof(string); i ++)
			{
				if(list[i] == str)
					return true;
			}
			return false;
		}
		
	public:

		void run(string command, Tokenizer tokenizer)
		{
			if(exists(command))
			{
				if(tokenizer.hasNext())
				{
					string tok = tokenizer.getNext();
					if(tok == "-h")
					{
						help(command);
						return;
					}
					
					if(command == "print")
					{
						print(tok, tokenizer);
						return;
					}

					if(command == "insert")
					{
						insert(tok, tokenizer);
						return;
					}

					if(command == "remove")
					{
						remove(tok, tokenizer);
						return;
					}
				}
				else
				{
					cout << "'print -h' for list of subcommands" << endl;
				}
			}
		}

		void print(string option, Tokenizer tokenizer)
		{
			if(option == "tree")
			{
				tree.print();
			}
		}

		void insert(string option, Tokenizer tokenizer)
		{
			if(option == "-t")
			{
				if(tokenizer.hasNext())
				{
					string key = tokenizer.getString();
					if(key.size() > 0)
						if(tree.insert(key))
							cout << "'" << key << "' inserted successfully" << endl;

				}
			}
		}

		void remove(string option, Tokenizer tokenizer)
		{
			if(option == "-t")
			{
				if(tokenizer.hasNext())
				{
					string key = tokenizer.getString();
					if(key.size() > 0)
						if(tree.remove(key))
							cout << "'" << key << "' deleted successfully" << endl;

				}
			}
			else if(option == "-r")
			{
				if(tokenizer.hasNext())
				{
					string tok = tokenizer.getNext();
					if(tok == "tree")
					{
						tree.destroy();
					}
				}
			}
		}

		Commands()
		{
			init();
		}

		~Commands()
		{

		}

};