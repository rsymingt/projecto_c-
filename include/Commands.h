
#include "Tree.h"
#include "FileHandler.h" 
#include "DirectoryHandler.h"

using std::string;
using std::cout;
using std::endl;

class Commands
{

	public:

		void run(string command, Tokenizer tokenizer)
		{
			if(exists(command))
			{
				if(command == "help")
				{
					help();
					return;
				}

				//list directories
				else if(command == "ls")
				{
					system(command.c_str());
					char *test = getenv("LAST");
					if(test)
						cout << test;
				}

				//change current director
				else if(command == "cd")
				{
					if(tokenizer.hasNext())
					{
						string tok = tokenizer.getNext();
						dh.cd(tok);
					}
				}

				//system rm
				else if(command == "rm")
				{
					if(tokenizer.hasNext())
					{
						string syscommand = command + " " + tokenizer.getString();
						system(syscommand.c_str());
						char *test = getenv("LAST");
						if(test)
							cout << test;
					}
					else
					{
						cout << "refer to man page for system commands" << endl;
					}
				}

				//make directory
				else if(command == "mkdir")
				{
					if(tokenizer.hasNext())
					{
						string dir = "mkdir " + tokenizer.getString();
						system(dir.c_str());
						char *test = getenv("LAST");
						if(test)
							cout << test;
					}
					else
					{
						cout << "refer to man page for system commands" << endl;
					}
				}

				else if(tokenizer.hasNext())
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

					else if(command == "insert")
					{
						insert(tok, tokenizer);
					}

					else if(command == "remove")
					{
						remove(tok, tokenizer);
					}

					else if(command == "create")
					{
						create(tok, tokenizer);
					}
				}
				else
				{
					cout << "'COMMAND -h' for list of subcommands" << endl;
				}
			}
		}

		string getCurrentDirectory()
		{
			return dh.getCurrentDirectory();
		}

		Commands()
		{
			init();
		}

		~Commands()
		{

		}
	
	private:

		string list[10];
		string listInfo[10];
		string subCommands[10];

		Tree tree;
		DirectoryHandler dh;

		void init()
		{
			list[0] = "print";
			list[1] = "insert";
			list[2] = "remove";
			list[3] = "create";
			list[4] = "help";
			list[5] = "ls";
			list[6] = "cd";
			list[7] = "q";
			list[8] = "mkdir";
			list[9] = "rm";

			//GOING TO BE USED WHEN HELP IS RUN;
			listInfo[0] = " - prints [option] name\n";
			listInfo[1] = " - insert [option] name\n";
			listInfo[2] = " - remove [option] name\n";


			subCommands[0] =
			"print [option] 'name'\n\n"
			"options\n"
			"-f - prints given filename or extended pathname";

			subCommands[1] =
			"insert [option] 'name'\n\n"
			"options\n"
			"-t    - inserts to object of type tree\n"
			"-f    - inserts content into file";

			subCommands[2] =
			"remove [option] 'name'\n\n"
			"options\n"
			"-t    - removes from object of type tree\n"
			"-r    - resets the tree\n"
			"-f    - removes said file";

			subCommands[3] = 
			"create [option] 'name'\n\n"
			"options\n"
			"-f    - run text editor on specified file\n"
			"-t    - create avl tree out of file";
		}

		void create(string option, Tokenizer tokenizer)
		{
			if(tokenizer.hasNext())
			{
				if(option == "-f")
				{
					string filename = "nano " + tokenizer.getNext();
					system(filename.c_str());
				}

				else if(option == "-t")
				{
					string filename = tokenizer.getNext();
					FileHandler::makeTree(&tree, filename);
				}
			}
		}

		void help(string str)
		{
			for(int i = 0; i < str.size() ; i ++)
			{
				if(list[i] == str)
				{
					cout << endl << "here is a list of some common print commands" << endl;
					cout << 	 "--------------------------------------------" << endl << endl;
					cout << subCommands[i] << endl;
					cout << endl << "--------------------------------------------" << endl << endl;
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

		void print(string option, Tokenizer tokenizer)
		{
			if(option == "tree")
			{
				tree.print();
			}

			//print a file
			else if(option == "-f")
			{
				if(tokenizer.hasNext())
				{
					string tok = tokenizer.getNext();
					FileHandler::readFile(tok, tokenizer);
				}
			}
			else
			{
				cout << "unknown command, type 'print -h' for help" << endl;
			}
		}

		void insert(string option, Tokenizer tokenizer)
		{
			//insert into tree
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

			//insert into a file
			else if(option == "-f")
			{
				if(tokenizer.hasNext())
				{
					string filename = tokenizer.getNext();
					if(tokenizer.hasNext())
					{
						string content = tokenizer.getNext();
						FileHandler::writeFile(filename, content);
					}
				}
			}

			//removes a directory and its contents CAREFUL!
			else if(option == "-d")
			{
				//left out for now...
			}

			//unknown command
			else
			{
				cout << "unknown command, type 'print -h' for help" << endl;
			}
		}

		void remove(string option, Tokenizer tokenizer)
		{
			//remove from tree
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

			//destroy entire tree
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

			//unknown command
			else
			{
				cout << "unknown commands, type 'remove -h' for help" << endl;
			}
		}

		void help()
		{

			cout << endl << "COMMANDS" << endl <<
							"--------" << endl;
							
			for(int i = 0; i < sizeof(list)/sizeof(string); i ++)
			{
				cout << list[i] << endl;
			}

			cout << "--------" << endl << endl;
		}

};