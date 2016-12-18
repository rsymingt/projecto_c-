
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using std::cout;
using std::endl;

using std::string;

class FileHandler
{
	public:

		static void readFile(string filename, Tokenizer tokenizer)
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

				if(tokenizer.hasNext())
				{
					std::ofstream fileout(tokenizer.getNext().c_str());

					for(int i = 0; i < str.size(); i ++)
					{
						if(str[i] == '\n')
							fileout << (int)str[i] << endl;
						else
							fileout << (int)str[i] << ",";
					}
					fileout << endl;
				}
				else
					cout << str << endl;

  				file.close();
  			}
  			else
  			{
  				cout << "file does not exists" << endl;
  			}
		}

		static void makeTree(Tree *tree, string filename)
		{
			struct stat buffer;   
  			if(stat (filename.c_str(), &buffer) == 0)
  			{

  				if(!tree->isEmpty()){
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
  			else
  			{
  				cout << "file does not exists" << endl;
  			}
		}

		static void writeFile(string filename, string contents)
		{
			std::ofstream file(filename.c_str());

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
						tree->insert(tok, para);
					}
				}
				else
					tree->insert(tok, para);
			}
		}
};
