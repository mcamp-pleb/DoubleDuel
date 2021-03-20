#ifndef DOUBLEDUEL_H
#define DOUBLEDUEL_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"
#include "GameState.h"

class DoubleDuel
{
	private:
		SystemSettings	m_settings;
		
		GameState	*m_states;
	public:
				DoubleDuel(std::string versionNumber, bool debug);
		void	Init();
		int		Run();
		void	ChangeState(int &newState);
		void	Cleanup();
};
#endif