#ifndef DECK_H
#define	DECK_H

#include <random>
#include <time.h>

namespace Deck
{
	static bool initialized = false;
	
	static int Shuffle()
	{
		if (!initialized)
		{
			srand(static_cast<unsigned int>(time(0)));
			initialized = true;
		}
		
		return (rand() % 9) + 1;
	};
}

#endif
