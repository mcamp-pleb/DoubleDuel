#ifndef ENDGAME_H
#define ENDGAME_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class EndGame
{
	private:
		Button	m_rematch;
		Button	m_exit;

		sf::Text			m_message;
		sf::Text			m_clientMessage;
		sf::RectangleShape	m_dialogBox;
	public:
		EndGame();
		~EndGame();
		void Init(SystemSettings *settings);

		void SetWinner(std::string player);

		int HandleButtons(SystemSettings *settings);

		void Update(SystemSettings *settings);
		void Draw(SystemSettings *settings);
};

#endif