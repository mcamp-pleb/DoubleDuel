//Mark Campanaro
//Double Duel
//Brookdale Community College
//Summer Semester 2017
//COMP-296-501RL

#include "DoubleDuel.h"

int main(int argc, char* argv[])
{
	bool		debug		= false;
	int			exitCode	= 0;
	std::string argOne		= "";
	
	if (argc > 1)
	{
		argOne = argv[argc - 1];
		if (argOne == "-debug")
		{
			debug = true;
		}
	}

	DoubleDuel	game("v4.103", debug);
	
	exitCode = game.Run();

	return exitCode;
}