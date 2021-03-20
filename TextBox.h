#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"

class TextBox
{
	private:
		std::string m_tempstr;
		
		sf::RectangleShape	m_textBox;
		sf::Text			m_textIn;
	public:
		TextBox();
		~TextBox();
		void Init(SystemSettings *settings);
		void Draw(SystemSettings *settings);
		void HandleKey();
		void ApplyName(SystemSettings *settings);
};

#endif