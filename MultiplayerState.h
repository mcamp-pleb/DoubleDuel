#ifndef MULTIPLAYERSTATE_H
#define MULTIPLAYERSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include "GameState.h"
#include "SystemSettings.h"
#include "NetworkController.h"
#include "Player.h"
#include "GridBoard.h"
#include "EndGame.h"

//PLAYER and P mean the same thing but refrence the player in two diferent ways
// could be done better
enum
{
	PLAYER_1,
	PLAYER_2,
	MAX_PLAYERS,
	P_1 = 1,
	P_2,
	OUT,
	IN,
	INIT,
	TOHOST,
	TOCLIENT,
	DISCONNECT,
	REMATCH
};

class MultiplayerState : public GameState, NetworkController
{
private:
	SystemSettings *m_Settings;
	Player			m_players[MAX_PLAYERS];
	GridBoard		m_board;
	EndGame			m_winner;

	int m_currentMachinePlayer;

	bool highlightGrid;
	bool m_disconnected;

	sf::RectangleShape	m_bg;
	sf::Text			m_turnText;
	sf::TcpListener		m_host;
	sf::TcpSocket		m_tcpSocket;
	sf::Packet			packet;
	sf::Clock			timer;
public:
	MultiplayerState();
	~MultiplayerState();
	virtual void Init(SystemSettings &settings);
	virtual void Cleanup();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Draw();

	int UnpackType();

	void SynchronizeCards(const int &inOrOut);
	void Disconnect();
	void HandlePackets();
	void SendData();
	void PackType(const int &type);
	void PackPlayers();
	void UnpackPlayers();
	void PackCard(const int &ID, const int &square);
	void UnpackCard(const int &player);
	bool EndGameCheck();
};

#endif