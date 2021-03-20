#ifndef JOINGAMESTATE_H
#define JOINGAMESTATE_H

#include <SFML\Network.hpp>
#include "GameState.h"
#include "NetworkController.h"
#include "SystemSettings.h"
#include "Button.h"

enum
{
	HOST_1,
	HOST_2,
	HOST_3,
	MAXLIST
};

class JoinGameState : public GameState, NetworkController
{
private:
	bool			m_slotFilled[MAXLIST];
	bool			m_searchDone;
	bool			m_showSelector;

	int				m_currentHostSelected;
	int				m_hostIndex;
	
	sf::Text		sfm_text;
	sf::Clock		sfm_timer;
	sf::Clock		sfm_seacrhClock;
	sf::CircleShape sfm_pointer;

	Button			m_gameList[MAXLIST];
	Button			m_back;
	Button			m_refresh;
	Button			m_connect;

	NetInfo			m_hostList[MAXLIST];
public:
	JoinGameState();
	~JoinGameState();

	virtual void Init(SystemSettings &settings);
	virtual void Cleanup();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Draw();

	void ReceiveHostList();
	void ClearHostList();

	bool IsSearchDone()const { return m_searchDone; };
	bool IsSelected()const { return m_showSelector; };
	bool ConnectToHost();
};

#endif
