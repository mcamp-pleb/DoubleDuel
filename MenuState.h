#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "SystemSettings.h"
#include "Button.h"
#include <string>

enum Options
{
	MAX_LIST = 3
};

class MenuState : public GameState
{
	private:
		SystemSettings *m_Settings;

		Button	m_btnHost;
		Button	m_btnJoin;
		Button	m_btnOptions;

		sf::RectangleShape	m_bg;
		sf::Text			m_title;
	public:
		MenuState();
		~MenuState();

		void Init(SystemSettings &settings);
		void Cleanup();
		void HandleEvents();
		void Update();
		void Draw();
};
#endif