#include "DoubleDuel.h"
#include "MenuState.h"
#include "MultiplayerState.h"
#include "HostGameState.h"
#include "JoinGameState.h"
#include "OptionState.h"
#include <fstream>

DoubleDuel::DoubleDuel(std::string versionNumber, bool debug)
{
	m_settings.Title = "Double Duel " + versionNumber;
	m_settings.debug = debug;
	Init();
}

void DoubleDuel::Init()
{
	//Read in settings
	std::ifstream initStream("settings.ini");
	if (!initStream.is_open())
	{
		std::ofstream ostream("settings.ini");
		ostream << m_settings.resWidth << '\n';
		ostream << m_settings.resHight << '\n';
		ostream << m_settings.machineName;
		ostream.close();

		m_settings.Width = m_settings.resWidth;
		m_settings.Hight = m_settings.resHight;
	}
	else
	{
		initStream >> m_settings.Width;
		initStream >> m_settings.Hight;
		initStream >> m_settings.machineName;
	}

	//Limit the name to 8 or less characters
	if (m_settings.machineName.size() > 8)
	{
		m_settings.machineName = m_settings.machineName.substr(0, 8);
	}

	//Setting up Rendering Environment
	m_settings.sfm_window.create(sf::VideoMode(m_settings.Width, m_settings.Hight), m_settings.Title, sf::Style::Titlebar | sf::Style::Close);
	m_settings.sfm_view.reset(sf::FloatRect(0.0f, 0.0f, static_cast<float>(m_settings.resWidth), static_cast<float>(m_settings.resHight)));
	m_settings.sfm_view.setViewport(m_settings.setRatio());
	m_settings.sfm_window.setView(m_settings.sfm_view);

	//loading up Font
	//NOTE: needs windows font directory
	if (!m_settings.sfm_Font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
	{
		m_settings.sfm_window.close();
	}

	//Init Starting State
	m_settings.currentState = States::MAIN_MENU;
	m_settings.changeState = true;
	m_states = NULL;
}

void DoubleDuel::Cleanup()
{
	delete m_states;
}

int	DoubleDuel::Run()
{
	ChangeState(m_settings.currentState);

	while (m_settings.sfm_window.isOpen())
	{
		if (m_settings.changeState)
		{
			ChangeState(m_settings.currentState);
		}
		
		//Get mouse location and Button hitboxes
		//Getting Delta mouse distance
		sf::Vector2f oldPos = m_settings.worldPos;

		m_settings.pixelPos = sf::Mouse::getPosition(m_settings.sfm_window);
		m_settings.worldPos = m_settings.sfm_window.mapPixelToCoords(m_settings.pixelPos);
		m_settings.deltaPos = m_settings.worldPos - oldPos;

		m_states->HandleEvents();
		m_states->Update();
		m_states->Draw();
	}

	Cleanup();

	return 0;
}

void DoubleDuel::ChangeState(int &newState)
{
	delete m_states;

	//Forward network info and skip Main Menu to start a rematch
	if (m_settings.rematch)
	{
		m_settings.rematch = false;
		m_settings.currentState = States::PLAY;
	}

	switch (newState)
	{
	case States::MAIN_MENU:
		m_states = new MenuState;
		break;
	case States::HOST:
		m_states = new HostGameState;
		break;
	case States::JOIN:
		m_states = new JoinGameState;
		break;
	case States::PLAY:
		m_states = new MultiplayerState;
		break;
	case States::OPTIONS:
		m_states = new OptionState;
		break;
	default:
		//Problem
		break;
	}

	m_states->Init(m_settings);
	m_settings.changeState = false;
}