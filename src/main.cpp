
#include <iostream>

#include "Tokenizer.h"
#include "Commands.h"

using std::cout;
using std::cin;
using std::endl;

using std::string;

void print(Tokenizer tokenizer);

int main()
{

	Commands commands;

	std::string usr_input;
	Tokenizer tokenizer(' ');

	cout << "Welcome to Projecto type help for a list of commands" << endl <<
			"____________________________________________________" << endl;
	while(true){

		cout << commands.getCurrentDirectory() << "$ ";
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