#include "OptionState.h"
#include <fstream>

OptionState::OptionState()
	: m_tempWidth(0), m_tempHight(0), m_wheelDir(0), m_mouseScrollHeld(false), m_textSpacing(20), m_reslist(true)
{
}

OptionState::~OptionState()
{
	Cleanup();
}

void OptionState::Init(SystemSettings &settings)
{
	this->m_Settings = &settings;
	m_tempWidth = m_Settings->Width;
	m_tempHight = m_Settings->Hight;

	float	listSize = 0.0f;
	
	//Init Supported Resolutions
	//NOTE: the size of the text hevily depends on locations
	//NOTE: static_cast<float>(i * 50)
	m_displayList = sf::VideoMode::getFullscreenModes();
	for (unsigned int i = 0; i < m_displayList.size(); i++)
	{
		m_displayText.push_back(sf::Text(std::to_string(m_displayList[i].width) + " x " + std::to_string(m_displayList[i].height), m_Settings->sfm_Font));
		m_displayText[i].setPosition(sf::Vector2f(600.0f, static_cast<float>(i * (m_displayText[i].getCharacterSize() + m_textSpacing))));
		m_resBox.push_back(sf::FloatRect(m_displayText[i].getGlobalBounds()));
		listSize += m_displayText[i].getLocalBounds().height;
		
	}

	//Init Back and Apply Butons
	m_back.SetFont(m_Settings->sfm_Font);
	m_apply.SetFont(m_Settings->sfm_Font);
	m_resolution.SetFont(m_Settings->sfm_Font);
	m_name.SetFont(m_Settings->sfm_Font);

	m_back.SetTitle("Back");
	m_apply.SetTitle("Apply");
	m_resolution.SetTitle("Resolution");
	m_name.SetTitle("Name");

	m_back.SetPos(100.0f, static_cast<float>(m_Settings->resHight - 100));
	m_apply.SetPos(static_cast<float>(m_Settings->resWidth - (100 + m_apply.GetSize().width)), static_cast<float>(m_Settings->resHight - 100));
	m_resolution.SetPos(100.0f, static_cast<float>(m_Settings->resHight - 650));
	m_name.SetPos(100.0f, static_cast<float>(m_Settings->resHight - 600));

	m_back.SetColor(sf::Color::White);
	m_apply.SetColor(sf::Color::White);
	m_resolution.SetColor(sf::Color::White);
	m_name.SetColor(sf::Color::White);

	//Init TextBox
	m_textBox.Init(m_Settings);

	//Init Background
	m_bg.setSize(sf::Vector2f(m_Settings->resWidth, m_Settings->resHight));
	m_bg.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_bg.setFillColor(sf::Color(75, 75, 75, 255));

	//Init Scroll Bar
	//NOTE: Size static, but should change based on number in list
	//NOTE2: 15 = bar width; 1280 = resolution width; 13.8 = text + spacing total (number of resolutions displayed on the page)
	sfm_scrollBar.setSize(sf::Vector2f(15.0f, static_cast<float>(m_Settings->resHight / m_displayText.size()) * 13.8f));
	sfm_scrollBar.setPosition(sf::Vector2f(1280.0f - 15.0f, 0.0f));
}

void OptionState::Cleanup()
{

}

void OptionState::HandleEvents()
{
	sf::Event event;
	while (m_Settings->sfm_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Settings->sfm_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (m_back.IsClicked(m_Settings))
			{
				Back();
			}
			if (m_apply.IsClicked(m_Settings))
			{
				Apply();
			}
			if (m_resolution.IsClicked(m_Settings))
			{
				m_reslist = true;
			}
			if (m_name.IsClicked(m_Settings))
			{
				m_reslist = false;
			}
			if (m_reslist)
			{
				for (unsigned int i = 0; i < m_resBox.size(); i++)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_resBox[i].contains(m_Settings->worldPos))
					{
						m_tempWidth = m_displayList[i].width;
						m_tempHight = m_displayList[i].height;
					}
				}
			}
		case sf::Event::MouseButtonReleased:
			m_mouseScrollHeld = false;
			break;
		case sf::Event::MouseWheelMoved:
			if (m_reslist)
			{
				m_wheelDir = event.mouseWheel.delta;
			}
			break;
		case sf::Event::KeyPressed:
			if (!m_reslist)
			{
				m_textBox.HandleKey();
			}
		}
	}
}

void OptionState::Update()
{
	if (m_reslist)
	{
		ScrollBar();
	}
	m_back.CheckMouse(m_Settings->worldPos);
	m_apply.CheckMouse(m_Settings->worldPos);
	m_resolution.CheckMouse(m_Settings->worldPos);
	m_name.CheckMouse(m_Settings->worldPos);
}

void OptionState::Draw()
{
	m_Settings->sfm_window.clear();
	m_Settings->sfm_window.draw(m_bg);
	if (m_reslist)
	{
		for (unsigned int i = 0; i < m_displayText.size(); i++)
		{
			m_Settings->sfm_window.draw(m_displayText[i]);
		}
		m_Settings->sfm_window.draw(sfm_scrollBar);
	}
	else
	{
		m_textBox.Draw(m_Settings);
	}
	m_back.Draw(m_Settings);
	m_apply.Draw(m_Settings);
	m_resolution.Draw(m_Settings);
	m_name.Draw(m_Settings);
	m_Settings->sfm_window.display();
}

void OptionState::Back()
{
	//Return to Main Menu
	m_Settings->currentState = States::MAIN_MENU;
	m_Settings->changeState = true;
}

void OptionState::Apply()
{
	//Apply Name
	m_textBox.ApplyName(m_Settings);

	//Apply Resolution
	if (IntegrateNum(m_Settings->Width, m_Settings->Hight) != IntegrateNum(m_tempWidth, m_tempHight))
	{
		m_Settings->Width = m_tempWidth;
		m_Settings->Hight = m_tempHight;
		m_textBox.ApplyName(m_Settings);

		m_Settings->sfm_window.create(sf::VideoMode(m_Settings->Width, m_Settings->Hight), m_Settings->Title, sf::Style::Titlebar | sf::Style::Close);
		m_Settings->sfm_view.setViewport(m_Settings->setRatio());
		m_Settings->sfm_window.setView(m_Settings->sfm_view);
		
		
	}

	//Save Settings
	std::ofstream out("settings.ini");
	if (out.is_open())
	{
		out << m_Settings->Width << '\n';
		out << m_Settings->Hight << '\n';
		out << m_Settings->machineName;
		out.close();
	}
	else
	{
		//Problem
	}
}

void OptionState::ScrollBar()
{
	//Scroll with click and hold
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sfm_scrollBar.getGlobalBounds().contains(m_Settings->worldPos)) || m_mouseScrollHeld)
	{
		m_mouseScrollHeld = true;
		sfm_scrollBar.move(0.0f, m_Settings->deltaPos.y);
		MoveList(m_Settings->deltaPos.y);
	}

	//Scroll with mouse wheel
	//NOTE: Clean Up
	sfm_scrollBar.move(0.0f, -18.0f * m_wheelDir);
	MoveList(-18.0f * m_wheelDir);
	m_wheelDir = 0;

	//Check ScrollBar stays within bounds
	if (sfm_scrollBar.getPosition().y <= 0.0f)
	{
		sfm_scrollBar.setPosition(sfm_scrollBar.getPosition().x, 0.0f);
	}
	else if (sfm_scrollBar.getPosition().y + sfm_scrollBar.getLocalBounds().height >= static_cast<float>(m_Settings->resHight))
	{
		sfm_scrollBar.setPosition(sfm_scrollBar.getPosition().x, static_cast<float>(m_Settings->resHight) - sfm_scrollBar.getLocalBounds().height);
		m_outOfBounds = true;//for bottom bar
	}
}
	
	

void OptionState::MoveList(const float &currentDelta)
{
	//Only checks top and bottom bar: need to change
	bool topOB	= (m_displayText[0].getPosition().y > 0);

	if (!m_outOfBounds)
	{
		m_resBox.clear();
		for (unsigned int i = 0; i < m_displayText.size(); i++)
		{
			m_displayText[i].move(0.0f, -1.0f * currentDelta);
			m_resBox.push_back(sf::FloatRect(m_displayText[i].getGlobalBounds()));
			
		}
	}
	
	if(topOB)
	{
		m_resBox.clear();
		for (unsigned int i = 0; i < m_displayList.size(); i++)
		{
			m_displayText[i].setPosition(sf::Vector2f(600.0f, static_cast<float>(i * (m_displayText[i].getCharacterSize() + m_textSpacing))));
			m_resBox.push_back(sf::FloatRect(m_displayText[i].getGlobalBounds()));
		}
	}
	m_outOfBounds = false;
}

//Integrate two numbers into one
//NOTE: assumes both numbers are larger than zero
unsigned int OptionState::IntegrateNum(unsigned int x, unsigned int y)
{
	unsigned int temp = y;

	do
	{
		temp /= 10;
		x *= 10;
	}
	while (temp > 0);

	return x + y;
}