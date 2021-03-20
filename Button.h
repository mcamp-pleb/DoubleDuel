#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"

class Button
{
	private:
		bool m_isHighlighted;
		
		sf::RectangleShape	m_rectHighlight;
		sf::Text			m_name;
	public:
		Button();
		~Button();

		void SetTitle(const std::string &title);
		void SetFont(const sf::Font &font);
		void SetPos(const float &x, const float &y);
		void SetColor(sf::Color color);

		sf::FloatRect GetSize() { return m_rectHighlight.getLocalBounds(); };
		sf::FloatRect GetPos() { return m_rectHighlight.getGlobalBounds(); };
		bool IsHighlighted()const { return m_isHighlighted; };
		bool IsClicked(SystemSettings *settings);

		void Update();
		void CheckMouse(sf::Vector2f wPos);
		void Draw(SystemSettings *settings);

};

#endif