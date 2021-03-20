#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"

enum States
{
	MAIN_MENU,
	HOST,
	JOIN,
	PLAY,
	OPTIONS
};

class GameState
{
	public:
		GameState(){};
		virtual void Init(SystemSettings &settings) = 0;
		virtual void Cleanup() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
};
#endif