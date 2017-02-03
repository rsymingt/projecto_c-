
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

using std::cout;
using std::endl;

using std::string;

class FileHandler
{
	public:

		static void readFile(string filename)
		{
			struct stat buffer;
  			if(stat (filename.c_str(), &buffer) == 0)
  			{
  				std::ifstream file(filename.c_str());

  				string str;

				file.seekg(0, std::ios::end);
				str.reserve(file.tellg());
				file.seekg(0, std::ios::beg);

				str.assign((std::istreambuf_iterator<char>(file)),
				            std::istreambuf_iterator<char>());


				cout << str << endl;

  				file.close();
  			}
  			else
  			{
  				cout << "file does not exists" << endl;
  			}
		}

		static void recurseDir(Tree *tree, string filename)
		{
			DIR *dp;
			struct dirent *ep;

			dp = opendir (filename.c_str());

			if (dp != NULL)
			{
				while ((ep = readdir(dp)))
					if(*(ep->d_name) != '.')
					{
						struct stat buffer;
						if(stat ((filename + "/" + ep->d_name).c_str(), &buffer) == 0)
			  			{
			  				if(buffer.st_mode & S_IFDIR)
			  				{
			  					recurseDir(tree, (filename + "/" + ep->d_name));
							}
							else if(buffer.st_mode & S_IFREG)
							{
								makeTree(tree, (filename + "/" + ep->d_name), 1);
							}
						}
						else
						{
							perror("file not found");
						}
					}

				closedir (dp);
			}
			else
				perror ("Couldn't open the directory");
		}

		static void makeTree(Tree *tree, string filename, int askAppend)
		{

			if(!tree->isEmpty() && askAppend == 0)
			{
				std::string answer;
				while(answer != "y" && answer != "Y" && answer != "n" && answer != "N")
				{
	  				std::cout << "would you like to append to existing tree? (Y/N) ";
	  				std::getline(std::cin, answer);
	  			}
	  			if(answer == "n" || answer == "N")
	  			{
	  				tree->destroy();
	  			}
  			}

			std::ifstream file(filename.c_str());

			string str;

			file.seekg(0, std::ios::end);
			str.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			str.assign((std::istreambuf_iterator<char>(file)),
			            std::istreambuf_iterator<char>());

			string para = "";
			{
				int scope;
				int i;
				for(scope = 0, i = 0; i < str.size(); i ++)
				{
					switch(str[i])
					{
						case '{':
							para+="{";
							scope ++;
							break;
						case '}':
							para+="}";
							scope --;
							break;

						case '\n':
							para += '\n';
							if(i < str.size()-1 && str[i+1] == '\n' && scope == 0 && para.size() > 0)
							{
								writeKeys(tree, para);
								para = "";
							}
							break;

						default:
							para += str[i];
							break;
					}
				}
			}
			writeKeys(tree, para);

			cout << "tree successful created from file '" << filename << "'" << endl;

			file.close();
		}

		static void writeFile(string filename, string contents)
		{
			std::ofstream file(filename.c_str());

			//ERASES ORIGINAL CONTENTS
			file << contents;

			file.close();
		}

		static string toLower(string str)
		{
			char lower[str.size() + 1];
			strcpy(lower, str.c_str());
			for(int i = 0; i < strlen(lower); i ++)
			{
				lower[i] = tolower(lower[i]);
			}
			str = lower;
			return str;
		}

		/*
		delimits keys and adds them into the tree with their corresponding keys
		*/
		static void writeKeys(Tree *tree, string para)
		{
			char c_para[para.size() + 1];
			strcpy(c_para, para.c_str());

			string key = "";

			{
				int i;
				for(i = 0; i < strlen(c_para); i ++)
				{
					switch(c_para[i])
					{
						case '(':
						case ')':
						case ' ':
						case '\n':
						case '\r':
						case '[':
						case ']':
						case ':':
						case '"':
						case '\'':
						case ',':
						case '_':
							if(key.size() > 0)
							{
								tree->insert(key, para);
								key = "";
							}
							break;

						default:
							key += c_para[i];
							break;
					}
				}
			}
		}
};
