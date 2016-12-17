
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using std::cout;
using std::endl;

using std::string;

class FileHandler
{
	public:

		static void readFile(Tree *tree, string filename)
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

				for(int last = 0; str.find("\r\n\r\n", last) != -1; last = str.find("\r\n\r\n", last) + 4)
				{
					string para = str.substr(last, str.find("\r\n\r\n", last));
					cout << para << endl;
					cout << "end para" << endl;
				}

  				file.close();
  			}
  			else
  			{
  				cout << "file does not exists" << endl;
  			}
		}
};
