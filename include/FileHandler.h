
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
  				std::ifstream file(filename.c_str());

  				string str;

				file.seekg(0, std::ios::end);   
				str.reserve(file.tellg());
				file.seekg(0, std::ios::beg);

				str.assign((std::istreambuf_iterator<char>(file)),
				            std::istreambuf_iterator<char>());

				
				int last;
				for(last = 0; str.find("\n\n", last) != -1; last = str.find("\n\n", last) + 2)
				{
					string holder = str.substr(last, str.find("\n\n", last) + 2);
					cout << holder << "end" << endl;
				}
				cout << str.substr(last);

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
};
