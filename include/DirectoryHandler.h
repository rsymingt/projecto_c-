
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

class DirectoryHandler
{

	private:


	public:

		void currentPath()
		{

		}

		void cd(string dir)
		{

		}

		void ls()
		{
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir ("./")) != NULL) {
				/* print all the files and directories within directory */
				cout << endl;
				while ((ent = readdir (dir)) != NULL) {
					if(*(ent->d_name) != '.')
					{
						string str(ent->d_name);
						if(str.find(".") != -1)
							cout << "\033[31m" << ent->d_name << "    ";
						else
							cout << "\033[32m" << ent->d_name << "    ";
					}
				}
				cout << "\033[0m";
				cout << endl;
				closedir (dir);
			} else {
				/* could not open directory */
				perror ("");
				//return EXIT_FAILURE;
			}
		}

		string getCurrentDirectory()
		{
			char *holder = get_current_dir_name();
			string str;
			if(holder)
			{
				str = holder;
				free(holder);
				int index = str.rfind('/');
				if(index != -1)
				{
					str = str.substr(index);
					str[0] = '~';
				}
			}
			return str;
		}

		DirectoryHandler()
		{

		}

		~DirectoryHandler()
		{

		}
};
