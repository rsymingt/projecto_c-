
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>

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

  			std::cout << "YES" << std::endl;
			std::ifstream file(filename.c_str());

			string str;

			file.seekg(0, std::ios::end);   
			str.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			str.assign((std::istreambuf_iterator<char>(file)),
			            std::istreambuf_iterator<char>());

			
			string last = str;
			for(int i = 0; (i = last.find("\n\n")) != -1;)
			{

				string para = last.substr(0, i + 2);
				int start = 0;
				for(; para[start] == '\n'; start ++);
				para = para.substr(start);


				writeKeys(tree, para);


				//cout << para;
				last = last.substr(i+2);
			}
			string para = last;

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

		static void writeKeys(Tree *tree, string para)
		{
			Tokenizer tokenizer(para, ' ');

			while(tokenizer.hasNext())
			{
				string tok = tokenizer.getNext();
				if(tok.find("\n") != -1)
				{
					Tokenizer endlineTokenizer(tok, '\n');
					while(endlineTokenizer.hasNext())
					{
						tok = endlineTokenizer.getNext();
						if(tok.size() > 0)
							tree->insert(tok, para);
					}
				}
				else
					if(tok.size() > 0)
						tree->insert(tok, para);
			}
		}
};
