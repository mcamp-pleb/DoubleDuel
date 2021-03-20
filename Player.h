#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "SystemSettings.h"
#include "GridBoard.h"
#include "Card.h"

enum
{
	FACE_UP,
	FACE_DOWN,
	MAX_HAND = 5
};

class Player
{
private:
	int		m_posNum;
	int		m_score;
	int		m_handForeignID[MAX_HAND];
	int		m_currentCardHolding;
	
	bool	m_currentTurn;
	bool	m_holdingCard;
	
	Card	m_currentHand[MAX_HAND];

	sf::Text	sfm_playerName;
public:
	Player();

	void Init(std::string name, int pos, bool startingTurn, int face, SystemSettings *settings);
	
	void SetPlayerPos(const int &pos) { m_posNum = pos; };
	void SetTurnStatus(const bool &turn) { m_currentTurn = turn; };
	void SetScore(const int &score) { m_score = score; };
	void SetName(const std::string &name);
	void SetFont(sf::Font &font);
	void SetCurrentHeldCard(const int &ID) { m_currentCardHolding = ID; };

	int GetCurrentHeldCard()const { return m_currentCardHolding; };
	int GetScore()const { return m_score; };

	std::string GetPlayerName()const { return sfm_playerName.getString(); };
	Card &GetCard(const int &element) { return m_currentHand[element]; };
	
	void ResetCards();
	void ResetScore() { m_score = 0; };
	void ResetPos(const int &card);
	void IndexCards();
	void MoveCard(const sf::Vector2f &newLocation, const int &ID);
	void PlaceCard(GridBoard &gameboard);
	void RemoveCard(int handnum);
	void HoldCard() { m_holdingCard = true; };
	void DropCard();
	void CardFace(int face);

	bool MouseOnCard(const sf::Vector2f &mouseLocation);
	bool IsHoldingCard()const { return m_holdingCard; };
	bool GetTurnStatus()const { return m_currentTurn; };

	void DrawGUI(SystemSettings *settings);
};

#endif