
#include <iostream>


#include "Tokenizer.h"
#include "Commands.h"

using std::cout;
using std::cin;
using std::endl;

using std::string;

int main()
{
	// const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  //   struct rlimit rl;
  //   int result;
	//
  //   result = getrlimit(RLIMIT_STACK, &rl);
  //   if (result == 0)
  //   {
  //       if (rl.rlim_cur < kStackSize)
  //       {
  //           rl.rlim_cur = kStackSize;
  //           result = setrlimit(RLIMIT_STACK, &rl);
  //           if (result != 0)
  //           {
  //               fprintf(stderr, "setrlimit returned result = %d\n", result);
  //           }
  //       }
  //   }

	Commands commands = Commands();

	std::string usr_input;
	Tokenizer tokenizer(' ');

	cout << "Welcome to Projecto type help for a list of commands" << endl <<
			"----------------------------------------------------" << endl << endl;

	while(true){

		cout << commands.getCurrentDirectory() << "$ " << std::flush;
		std::getline(cin, usr_input);

		tokenizer.setString(usr_input);
		if(tokenizer.hasNext())
		{
			string tok = tokenizer.getNext();

			if(tok == "q")
			{
				break;
			}

			commands.run(tok, tokenizer);
		}
	}

	return 0;
}
