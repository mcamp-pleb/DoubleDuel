#ifndef SYSTEMSTRUC_H
#define SYSTEMSTRUC_H

#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>

//Static class may help
struct SystemSettings
{
	const int	resWidth = 1280;
	const int	resHight = 720;
	
	int Width	= 0;
	int Hight	= 0;
	int	Volume	= 0;

	std::string Title = "";
	std::string machineName = "Default";

	unsigned short	inPortUDP = 15770;
	unsigned short	outPortUDP = 15771;
	unsigned short	inPortTCP = 15660;
	unsigned short	outPortTCP = 15661;
	unsigned int	deltaTime;
	int				currentState;
	int				currentMachinePlayer;
	int				currentNetPos;
	
	bool			debug;
	bool			rematch = false;
	bool			changeState;
	bool			mouseHeld = false;

	sf::IpAddress		sfm_opponentIP = sf::IpAddress::None;
	std::string			sfm_opponentName = "";

	sf::RenderWindow	sfm_window;
	sf::View			sfm_view;
	sf::Font			sfm_Font;

	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;
	sf::Vector2f deltaPos;

	//Dynamicly sets aspect ratio based on window and view sizes
	sf::FloatRect setRatio()
	{
		float windowRatio = static_cast<float>(Width) / static_cast<float>(Hight);
		float viewRatio = static_cast<float>(resWidth) / static_cast<float>(resHight);
		float posX = 0.0f;
		float posY = 0.0f;
		float sizeX = 1.0f;
		float sizeY = 1.0f;

		bool letterBox = true;

		if (windowRatio < viewRatio)
		{
			letterBox = false;
		}

		if (letterBox)
		{
			sizeX = viewRatio / windowRatio;
			posX = (1 - sizeX) / 2.0f;
		}
		else
		{
			sizeY = windowRatio / viewRatio;
			posY = (1 - sizeY) / 2.0f;
		}

		return sf::FloatRect(posX, posY, sizeX, sizeY);
	}
};
#endif