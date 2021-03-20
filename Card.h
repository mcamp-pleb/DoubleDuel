#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"

enum
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	MAX_SIDES
};

class Card
{
private:
	int m_top;
	int m_bottom;
	int m_left;
	int m_right;

	int m_cardOwner;
	int m_cardID;

	bool m_highlighted;
	bool m_faceUp;
	bool m_renderCard;

	sf::Sprite	sfm_cardFront;
	sf::Sprite	sfm_cardBack;
	sf::RectangleShape	sfm_bgColor;
	sf::Texture	sfm_cardTexture;
	sf::Text	sfm_numberSides[MAX_SIDES];
	sf::FloatRect m_size;
	sf::FloatRect m_hitBox;
public:
	Card();
	void Init(const int &owner, const int &ID);
	void Clear();
	void SetFont(sf::Font &font);
	void SetPos(float x, float y);
	void SetScale(const float &scale);
	void SetTopNum(const int &top) { m_top = top; };
	void SetBottompNum(const int &bottom) { m_bottom = bottom; };
	void SetLeftNum(const int &left) { m_left = left; };
	void SetRightNum(const int &right) { m_right = right; };
	void SetCardOwner(const int &owner) { m_cardOwner = owner; };
	void SetCardID(const int &ID) { m_cardID = ID; };
	void SetFace(bool face);

	void MoveCard(const sf::Vector2f &deltaMove);
	void DrawCard(SystemSettings *settings);

	void MapCardSprites();
	void UpdateDigits(const int &top, const int &bottom, const int &left, const int &right);
	void UpdateCardColor();

	int GetTopNum()const { return m_top; };
	int GetBottompNum()const { return m_bottom; };
	int GetLeftNum()const { return m_left; };
	int GetRightNum()const { return m_right; };
	int GetCardOwner() const { return m_cardOwner; };
	int GetCardID() const { return m_cardID; };

	bool IsHighlighted() const { return m_highlighted; };
	bool IsFaceUp() const { return m_faceUp; };
	bool OutOfBounds();
	bool CheckWithin(const sf::Vector2f &mouseLocation);

	sf::FloatRect GetCardSize()const { return m_size; };
	sf::FloatRect GetCardCoordinates()const { return m_hitBox; };

	sf::Texture	GetTexture()const { return sfm_cardTexture; };
};
#endif