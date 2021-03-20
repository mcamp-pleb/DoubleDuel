#ifndef HOSTGAMESTATE_H
#define HOSTGAMESTATE_H

#include <SFML\Network.hpp>
#include "GameState.h"
#include "NetworkController.h"
#include "Button.h"

class HostGameState : public GameState, NetworkController
{
	private:		
		sf::Text		sfm_text;
		sf::Clock		sfm_textTime;

		NetInfo			m_tempClient;
		Button			m_back;
	public:
		HostGameState();
		~HostGameState();

		virtual void Init(SystemSettings &settings);
		virtual void Cleanup();
	
		virtual void HandleEvents();
		virtual void Update();
		virtual void Draw();
};

#endif