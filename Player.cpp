#include "Player.h"

Player::Player()
	:m_holdingCard(false), m_score(0)
{
	
}

void Player::Init(std::string name, int pos, bool startingTurn, int face, SystemSettings *settings)
{
	SetName(name);
	SetPlayerPos(pos);
	SetTurnStatus(startingTurn);
	SetFont(settings->sfm_Font);
	IndexCards();
	ResetCards();
	CardFace(face);
}

void Player::SetName(const std::string &name)
{
	sfm_playerName.setString(name);
}

void Player::SetFont(sf::Font &font)
{
	sfm_playerName.setFont(font);
	for (int i = 0; i < MAX_HAND; i++)
	{
		m_currentHand[i].SetFont(font);
	}
}

void Player::ResetCards()
{
	
	
	for (int i = 0; i < MAX_HAND; i++)
	{
		m_currentHand[i].Init(m_posNum, i);
		ResetPos(i);
	}
}

void Player::ResetPos(const int &card)
{
	float multiplyier = 0;

	if (m_posNum == 1)
	{
		multiplyier = 50.0f;
	}
	else if (m_posNum == 2)
	{
		multiplyier = 1059.0f;
	}
	
	//TEMP hand placement -> 27 is based on the scaling; should equal 144
	m_currentHand[card].SetPos(multiplyier, card * (m_currentHand[card].GetCardSize().height - 27));//i * (171.0f / 1.5f) + 50.0f);
}

//creates an array of indexed card id's
void Player::IndexCards()
{
	for (int i = 0; i < MAX_HAND; i++)
	{
		m_handForeignID[i] = m_currentHand[i].GetCardID();
	}
}

//Searches for card position and moves that card
void Player::MoveCard(const sf::Vector2f &newLocation, const int &ID)
{
	int cardPos = 0;
	for (int i = 0; i < MAX_HAND; i++)
	{
		if (m_currentHand[i].GetCardID() == ID)
		{
			cardPos = i;
		}
	}

	m_currentHand[cardPos].MoveCard(newLocation);
}

void Player::PlaceCard(GridBoard &gameboard)
{
	//Redundent: Might need change
	switch (GetCurrentHeldCard())
	{
	case 100:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 100], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 100);
		break;
	case 101:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 100], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 100);
		break;
	case 102:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 100], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 100);
		break;
	case 103:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 100], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 100);
		break;
	case 104:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 100], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 100);
		break;
	case 200:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 200], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 200);
		break;
	case 201:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 200], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 200);
		break;
	case 202:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 200], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 200);
		break;
	case 203:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 200], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 200);
		break;
	case 204:
		gameboard.InsertCard(m_currentHand[GetCurrentHeldCard() - 200], gameboard.GetHighlightedSpace());
		RemoveCard(GetCurrentHeldCard() - 200);
		break;
	}
}

void Player::RemoveCard(int handnum)
{
	m_currentHand[handnum].Clear();
}

void Player::DropCard()
{
	m_holdingCard = false;
	for (int i = 0; i < MAX_HAND; i++)
	{
		ResetPos(i);
	}
}

void Player::CardFace(int face)
{
	switch (face)
	{
	case FACE_UP:
		for (int i = 0; i < MAX_HAND; i++)
		{
			m_currentHand[i].SetFace(true);
		}
		break;
	case FACE_DOWN:
		for (int i = 0; i < MAX_HAND; i++)
		{
			m_currentHand[i].SetFace(false);
		}
		break;
	default:
		break;
	}
}

void Player::DrawGUI(SystemSettings *settings)
{
	if (m_posNum == 1)
	{
		sfm_playerName.setPosition(sf::Vector2f(200.0f, 0.0f));
	}
	else if (m_posNum == 2)
	{
		sfm_playerName.setPosition(sf::Vector2f(1280.0f - (sfm_playerName.getLocalBounds().width + 230.0f) , 0.0f));
	}
	for (int i = 0; i < MAX_HAND; i++)
	{
		m_currentHand[i].DrawCard(settings);
	}
	settings->sfm_window.draw(sfm_playerName);
}

bool Player::MouseOnCard(const sf::Vector2f &mouseLocation)
{
	for (int i = 0; i < MAX_HAND; i++)
	{
		if (m_currentHand[i].CheckWithin(mouseLocation))
		{
			if (!IsHoldingCard())
			{
				m_currentCardHolding = m_currentHand[i].GetCardID();
				return true;
			}
		}
	}
	return false;
}