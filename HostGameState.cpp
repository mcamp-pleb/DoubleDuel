#include "HostGameState.h"

HostGameState::HostGameState()
{

}

HostGameState::~HostGameState()
{
	
}

void HostGameState::Init(SystemSettings &settings)
{
	this->m_Settings = &settings;
	RetrieveLocalIP();

	//Set temp client struct
	m_tempClient.mstr_otherName = "";
	m_tempClient.sfm_otherIP = sf::IpAddress::None;

	//Set Text
	sfm_text.setFont(m_Settings->sfm_Font);
	sfm_text.setString("Waiting for connection");
	sfm_text.setPosition(sf::Vector2f((m_Settings->resWidth / 2.0f) - (sfm_text.getLocalBounds().width / 2.0f), (m_Settings->resHight - 500.0f)));

	m_back.SetFont(m_Settings->sfm_Font);
	m_back.SetTitle("Back");
	m_back.SetPos((50.0f), (m_Settings->resHight - 50.0f));
	m_back.SetColor(sf::Color::White);
}

void HostGameState::Cleanup()
{
	sfm_thisIP = sf::IpAddress::None;
	sfm_selector.clear();
}

void HostGameState::HandleEvents()
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
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Exit to Main Menu
				if (m_back.IsClicked(m_Settings))
				{
					m_Settings->currentState = States::MAIN_MENU;
					m_Settings->changeState = true;
				}
			}
			break;
		}
	}
}

void HostGameState::Update()
{
	m_back.CheckMouse(m_Settings->worldPos);
	if (sfm_textTime.getElapsedTime() > sf::milliseconds(900))
	{
		//Manipulate text to show connection
		if (sfm_text.getString().substring(22, 3) != "...")
		{
			sfm_text.setString(sfm_text.getString() + ".");
		}
		else if (sfm_text.getString() == "Waiting for connection...")
		{
			sfm_text.setString("Waiting for connection");
		}
		sfm_textTime.restart();
	}
	//Send out Broadcast to Client
	SendUDPString(m_Settings->machineName, sf::IpAddress::Broadcast);
	ReceiveUDPConnection(m_tempClient);
	if (m_tempClient.sfm_otherIP != sf::IpAddress::None)
	{
		//Store Opponent Info
		m_Settings->sfm_opponentIP = m_tempClient.sfm_otherIP;
		m_Settings->sfm_opponentName = m_tempClient.mstr_otherName;
		
		//Start Multiplayer as Player 1
		m_Settings->currentMachinePlayer = 1;
		m_Settings->currentState = States::PLAY;
		m_Settings->changeState = true;
	}
}

void HostGameState::Draw()
{
	m_Settings->sfm_window.clear();
	m_back.Draw(m_Settings);
	m_Settings->sfm_window.draw(sfm_text);
	m_Settings->sfm_window.display();
}