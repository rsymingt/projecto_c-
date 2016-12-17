
#include <iostream>
#include <limits>

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

	while(true){

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