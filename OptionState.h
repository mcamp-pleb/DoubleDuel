#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "SystemSettings.h"
#include "Button.h"
#include "TextBox.h"
#include <string>
#include <vector>

class OptionState : public GameState
{
private:
	SystemSettings *m_Settings;

	std::vector<sf::VideoMode>	m_displayList;
	std::vector<sf::Text>		m_displayText;
	std::vector<sf::FloatRect>	m_resBox;

	Button	m_back;
	Button	m_apply;
	Button	m_resolution;
	Button	m_name;
	TextBox m_textBox;

	sf::RectangleShape sfm_scrollBar;
	sf::RectangleShape m_bg;

	const int m_textSpacing;
	int m_tempWidth;
	int m_tempHight;
	int	m_wheelDir;

	bool m_mouseScrollHeld;
	bool m_outOfBounds;
	bool m_reslist;
public:
	OptionState();
	~OptionState();

	void Init(SystemSettings &settings);
	void Cleanup();
	void HandleEvents();
	void Update();
	void Draw();

	void Back();
	void Apply();
	void ScrollBar();
	void MoveList(const float &currentDelta);
	
	unsigned int IntegrateNum(unsigned int x, unsigned int y);
};
#endif