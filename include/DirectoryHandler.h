
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>

class DirectoryHandler
{

	private:
		string initialDir;

	public:

		void cd(string dir)
		{
			if((initialDir.find('/') != -1 || dir != "..") && chdir(dir.c_str()) < 0)
			{
				cout << "directory not found" << endl;
			}
			else
			{
				if(dir != "." && dir != "..")
					initialDir += "/" + dir;
				else if(dir == "..")
				{
					int index = initialDir.rfind('/');
					if(index != -1)
						initialDir = initialDir.substr(0, index);
				}
			}
		}

		string getCurrentDirectory()
		{
			return initialDir;
		}

		DirectoryHandler()
		{
			char *holder = get_current_dir_name();
			if(holder)
			{
				initialDir = holder;
				free(holder);
				int index = initialDir.rfind('/');
				if(index != -1)
				{
					initialDir = initialDir.substr(index);
					initialDir[0] = '~';
				}
			}
		}

		~DirectoryHandler()
		{

		}
};
