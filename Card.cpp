#include "Card.h"
#include "Deck.h"

//need random nums
Card::Card()
	: m_highlighted(false), m_renderCard(true)
{

}

void Card::Clear()
{
	m_top = 0;
	m_bottom = 0;
	m_left = 0;
	m_right = 0;

	m_cardOwner = 0;
	m_cardID = 0;

	m_highlighted = false;
	m_faceUp = false;
	m_renderCard = false;
	
	m_hitBox = m_size = sf::FloatRect(0, 0, 0, 0);
}

void Card::Init(const int &owner, const int &ID)
{
	SetCardOwner(owner);
	SetCardID((owner * 100) + ID);

	//shuffleing redo
	m_top = Deck::Shuffle();
	m_bottom = Deck::Shuffle();
	m_left = Deck::Shuffle();
	m_right = Deck::Shuffle();

	for (int i = 0; i < MAX_SIDES; i++)
	{
		switch (i)
		{
		case TOP:
			sfm_numberSides[i].setString(std::to_string(m_top));
			break;
		case BOTTOM:
			sfm_numberSides[i].setString(std::to_string(m_bottom));
			break;
		case LEFT:
			sfm_numberSides[i].setString(std::to_string(m_left));
			break;
		case RIGHT:
			sfm_numberSides[i].setString(std::to_string(m_right));
			break;

		}
		sfm_numberSides[i].setFillColor(sf::Color::Black);
	}

	//Init sprite
	sfm_cardTexture.loadFromFile("image\\card.png");
	MapCardSprites();

	//Init Card hitbox
	m_size = sfm_cardFront.getLocalBounds();
	m_hitBox = sfm_cardFront.getGlobalBounds();

	//Init Card color
	sfm_bgColor.setSize(sf::Vector2f(m_size.width, m_size.height));
	UpdateCardColor();

	//Scaling if needed
	SetScale(0.84210526315789473684210526315789f);
	
}

void Card::SetFont(sf::Font &font)
{
	for (int i = 0; i < MAX_SIDES; i++)
	{
		sfm_numberSides[i].setFont(font);
	}
}

void Card::SetPos(float x, float y)
{
	float spacing = 7.0f;
	
	//set the position of the card
	sfm_cardFront.setPosition(x, y);
	sfm_cardBack.setPosition(x, y);
	sfm_bgColor.setPosition(x, y);
	m_hitBox = sfm_cardFront.getGlobalBounds();
	m_size = sfm_cardFront.getLocalBounds();
	//set the positions of the numbers on the card
	for (int i = 0; i < MAX_SIDES; i++)
	{
		//NOTE: slightly slopy algorithm, but the positions center the numbers into the correct spaces
		//NOTE: the 7.0f is spacing
		switch (i)
		{
		case TOP:
			sfm_numberSides[i].setPosition((sfm_cardFront.getGlobalBounds().width / 2.0f) + x - (sfm_numberSides[i].getLocalBounds().width / 2.0f),
											sfm_cardFront.getPosition().y);
			break;
		case BOTTOM:
			sfm_numberSides[i].setPosition((sfm_cardFront.getGlobalBounds().width / 2.0f) + x - (sfm_numberSides[i].getLocalBounds().width / 2.0f),
											(sfm_cardFront.getGlobalBounds().height + y) - (sfm_numberSides[i].getCharacterSize() + spacing));
			break;
		case LEFT:
			sfm_numberSides[i].setPosition((sfm_cardFront.getGlobalBounds().left + spacing),
											y + (sfm_cardFront.getGlobalBounds().height / 2.0f) - (sfm_numberSides[i].getLocalBounds().height / 2.0f + spacing));
			break;
		case RIGHT:
			sfm_numberSides[i].setPosition((sfm_cardFront.getGlobalBounds().width + x - (sfm_numberSides[i].getLocalBounds().width + spacing)),
				y + (sfm_cardFront.getGlobalBounds().height / 2.0f) - (sfm_numberSides[i].getLocalBounds().height / 2.0f + spacing));
			break;
		}
	}
}

void Card::SetScale(const float &scale)
{
	sfm_cardFront.setScale(scale, scale);
	sfm_cardBack.setScale(scale, scale);
	sfm_bgColor.setScale(scale, scale);
	for (int i = 0; i < MAX_SIDES; i++)
	{
		sfm_numberSides[i].setCharacterSize(static_cast<unsigned int>(scale * sfm_numberSides[i].getCharacterSize()));
	}
}

void Card::SetFace(bool face)
{
	m_faceUp = face;
}

void Card::MapCardSprites()
{
	sfm_cardFront.setTexture(sfm_cardTexture);
	sfm_cardFront.setTextureRect(sf::IntRect(0, 0, 171, 171));
	sfm_cardBack.setTexture(sfm_cardTexture);
	sfm_cardBack.setTextureRect(sf::IntRect(171, 0, 171, 171));

	
}

void Card::UpdateDigits(const int &top, const int &bottom, const int &left, const int &right)
{
	sfm_numberSides[TOP].setString(std::to_string(top));
	sfm_numberSides[BOTTOM].setString(std::to_string(bottom));
	sfm_numberSides[LEFT].setString(std::to_string(left));
	sfm_numberSides[RIGHT].setString(std::to_string(right));
}

void Card::UpdateCardColor()
{
	switch (m_cardOwner)
	{
	case 1:
		sfm_bgColor.setFillColor(sf::Color::Blue);
		break;
	case 2:
		sfm_bgColor.setFillColor(sf::Color::Red);
		break;
	}
}

void Card::MoveCard(const sf::Vector2f &deltaMove)
{

	sfm_bgColor.move(deltaMove);
	sfm_cardFront.move(deltaMove);
	for (int i = 0; i < MAX_SIDES; i++)
	{
		sfm_numberSides[i].move(deltaMove);
	}
	m_hitBox = sfm_cardFront.getGlobalBounds();

	if (OutOfBounds())
	{
		if (m_hitBox.left < 0.0f)
		{
			m_hitBox.left = 00.0f;
		}
		if (m_hitBox.top < 0.0f)
		{
			m_hitBox.top = 0.0f;
		}
		if (m_hitBox.left > 1280 - m_hitBox.width)
		{
			m_hitBox.left = 1280 - m_hitBox.width;
		}
		if (m_hitBox.top > 720 - m_hitBox.height)
		{
			m_hitBox.top = 720 - m_hitBox.height;
		}

		SetPos(m_hitBox.left, m_hitBox.top);
	}

}

void Card::DrawCard(SystemSettings *settings)
{
	if (m_renderCard)
	{
		if (m_faceUp)
		{
			settings->sfm_window.draw(sfm_bgColor);
			settings->sfm_window.draw(sfm_cardFront);
			for (int i = 0; i < MAX_SIDES; i++)
			{
				settings->sfm_window.draw(sfm_numberSides[i]);
			}
		}
		else
		{
			settings->sfm_window.draw(sfm_cardBack);
		}
	}
}

bool Card::OutOfBounds()
{
	sf::Vector2f temp(m_hitBox.left, m_hitBox.top);
	
	if (temp.x < 0.0f)
	{
		return true;
	}
	if (temp.y < 0.0f)
	{
		return true;
	}
	if (temp.x > 1280 - m_hitBox.width)
	{
		return true;
	}
	if (temp.y > 720 - m_hitBox.height)
	{
		return true;
	}

	return false;
}

bool Card::CheckWithin(const sf::Vector2f &mouseLocation)
{
	return m_hitBox.contains(mouseLocation);
}
