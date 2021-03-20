#include "Button.h"

Button::Button()
	:m_isHighlighted(false)
{
	SetTitle("");
	m_rectHighlight.setFillColor(sf::Color(100, 100, 100));
}

Button::~Button()
{
}

void Button::SetTitle(const std::string &title)
{ 
	m_name.setString(title);
	Update();
}
void Button::SetFont(const sf::Font &font)
{
	m_name.setFont(font);
}
void Button::SetPos(const float &x, const float &y)
{
	m_name.setPosition(x, y);
	Update();
}

void Button::SetColor(sf::Color color)
{
	m_name.setColor(color);
}

void Button::CheckMouse(sf::Vector2f wPos)
{
	sf::FloatRect hitBox(m_rectHighlight.getGlobalBounds());
	if (hitBox.contains(wPos))
	{
		m_isHighlighted = true;
	}
	else
	{
		m_isHighlighted = false;
	}
}

bool Button::IsClicked(SystemSettings *settings)
{
	if (IsHighlighted() && GetPos().contains(settings->worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}
	
	return false;
}

void Button::Update()
{
	//size times 2 of position to make slightly latger than text
	m_rectHighlight.setSize(sf::Vector2f(m_name.getLocalBounds().width + 8.0f, m_name.getLocalBounds().height + 8.0f));
	m_rectHighlight.setPosition(sf::Vector2f(m_name.getGlobalBounds().left - 4.0f, m_name.getGlobalBounds().top - 4.0f));
}

void Button::Draw(SystemSettings *settings)
{
	if (IsHighlighted())
	{
		settings->sfm_window.draw(m_rectHighlight);
	}
	settings->sfm_window.draw(m_name);
}