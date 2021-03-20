#include "JoinGameState.h"

JoinGameState::JoinGameState()
	:m_searchDone(false), m_showSelector(false), m_currentHostSelected(-1), m_hostIndex(0)
{

}

JoinGameState::~JoinGameState()
{
}

void JoinGameState::Init(SystemSettings &settings)
{
	this->m_Settings = &settings;
	RetrieveLocalIP();

	//Set bools to false
	for (int i = 0; i < MAXLIST; i++)
	{
		m_slotFilled[i] = false;
	}

	//Set Buttons
	for (int i = 0; i < MAXLIST; i++)
	{
		m_gameList[i].SetFont(m_Settings->sfm_Font);
		m_gameList[i].SetTitle("Empty");
		m_gameList[i].SetPos((m_Settings->resWidth / 2.0f) - (m_gameList[i].GetPos().width / 2.0f), i * 50.0f + 100.0f);
		m_gameList[i].SetColor(sf::Color::White);
	}
	m_back.SetFont(m_Settings->sfm_Font);
	m_refresh.SetFont(m_Settings->sfm_Font);
	m_connect.SetFont(m_Settings->sfm_Font);

	m_back.SetTitle("Back");
	m_refresh.SetTitle("Refresh");
	m_connect.SetTitle("Connect");

	m_back.SetPos((50.0f),(m_Settings->resHight - 50.0f));
	m_refresh.SetPos((m_Settings->resWidth / 2.0f) - (m_refresh.GetPos().width / 2.0f), (m_Settings->resHight - 50.0f));
	m_connect.SetPos((m_Settings->resWidth - (m_connect.GetSize().width + 50.0f)), (m_Settings->resHight - 50.0f));

	m_back.SetColor(sf::Color::White);
	m_refresh.SetColor(sf::Color::White);
	m_connect.SetColor(sf::Color::White);

	//Set Selection GUI Properties
	sfm_pointer.setFillColor(sf::Color::Red);
	sfm_pointer.setRadius(7.0f);

	//Set Connecting Text
	sfm_text.setFont(m_Settings->sfm_Font);
	sfm_text.setString("Searching for connection");
	sfm_text.setPosition(sf::Vector2f((m_Settings->resWidth / 2.0f) - (sfm_text.getLocalBounds().width / 2.0f), 500.0f));
}

void JoinGameState::Cleanup()
{
	sfm_thisIP = sf::IpAddress::None;
	sfm_selector.clear();
	ClearHostList();
}

void JoinGameState::HandleEvents()
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
				if (m_gameList[HOST_1].IsClicked(m_Settings))
				{
					//connect to host 1
					m_showSelector = true;
					sfm_pointer.setPosition(m_gameList[HOST_1].GetPos().left - 14.0f, m_gameList[HOST_1].GetPos().top + m_gameList[HOST_1].GetPos().height / 4.0f);
					m_currentHostSelected = HOST_1;
				}
				if (m_gameList[HOST_2].IsClicked(m_Settings))
				{
					//connect to host 2
					m_showSelector = true;
					sfm_pointer.setPosition(m_gameList[HOST_2].GetPos().left - 14.0f, m_gameList[HOST_2].GetPos().top + m_gameList[HOST_2].GetPos().height / 4.0f);
					m_currentHostSelected = HOST_2;
				}
				if (m_gameList[HOST_3].IsClicked(m_Settings))
				{
					//connect to host 3
					m_showSelector = true;
					sfm_pointer.setPosition(m_gameList[HOST_3].GetPos().left - 14.0f, m_gameList[HOST_3].GetPos().top + m_gameList[HOST_3].GetPos().height / 4.0f);
					m_currentHostSelected = HOST_3;
				}
				//Refresh Host List
				if (m_refresh.IsClicked(m_Settings))
				{
					ClearHostList();
				}
				//Connect to the Selected Host
				if (m_connect.IsClicked(m_Settings))
				{
					//connect to the host
					if (ConnectToHost())
					{
						//Start Multiplayer as Player 2
						m_Settings->currentMachinePlayer = 2;
						m_Settings->currentState = States::PLAY;
						m_Settings->changeState = true;
					}
				}
				//Exit to Main Menu
				if (m_back.IsClicked(m_Settings))
				{
					m_Settings->currentState = States::MAIN_MENU;
					m_Settings->changeState = true;
				}
			}
		}
	}
}

void JoinGameState::Update()
{
	if (sfm_seacrhClock.getElapsedTime() > sf::seconds(8.0f))
	{
		m_searchDone = true;
	}
	if (sfm_timer.getElapsedTime() > sf::milliseconds(900) && !IsSearchDone())
	{
		//Manipulate text to show connection
		if (sfm_text.getString().substring(24, 3) != "...")
		{
			sfm_text.setString(sfm_text.getString() + ".");
		}
		else if (sfm_text.getString() == "Searching for connection...")
		{
			sfm_text.setString("Searching for connection");
		}
		sfm_timer.restart();
	}
	if (IsSearchDone())
	{
		sfm_text.setString("");
	}
	for (int i = 0; i < MAXLIST; i++)
	{
		m_gameList[i].CheckMouse(m_Settings->worldPos);
	}
	m_back.CheckMouse(m_Settings->worldPos);
	m_refresh.CheckMouse(m_Settings->worldPos);
	m_connect.CheckMouse(m_Settings->worldPos);

	ReceiveHostList();
}

void JoinGameState::Draw()
{
	m_Settings->sfm_window.clear();
	for (int i = 0; i < MAXLIST; i++)
	{
		m_gameList[i].Draw(m_Settings);
	}
	if (IsSelected())
	{
		m_Settings->sfm_window.draw(sfm_pointer);
	}
	m_back.Draw(m_Settings);
	m_refresh.Draw(m_Settings);
	m_connect.Draw(m_Settings);
	m_Settings->sfm_window.draw(sfm_text);
	m_Settings->sfm_window.display();
}

void JoinGameState::ReceiveHostList()
{
	if (!IsSearchDone())
	{
		NetInfo temp;
		ReceiveUDPConnection(temp);

		if (temp.sfm_otherIP != sf::IpAddress::None && temp.sfm_otherIP != m_hostList[0].sfm_otherIP &&
			temp.sfm_otherIP != m_hostList[1].sfm_otherIP && temp.sfm_otherIP != m_hostList[2].sfm_otherIP)
		{
			m_hostList[m_hostIndex] = temp;
			m_gameList[m_hostIndex].SetTitle(m_hostList[m_hostIndex].mstr_otherName);
			m_slotFilled[m_hostIndex] = true;
			m_hostIndex++;
		}
	}
}

void JoinGameState::ClearHostList()
{
	for (int i = 0; i < MAXLIST; i++)
	{
		m_slotFilled[i] = false;
		m_hostList[i] = NetInfo();
		m_gameList[i].SetTitle("Empty");
	}
	m_searchDone = false;
	m_showSelector = false;
	m_currentHostSelected = -1;
	m_hostIndex = 0;
	sfm_text.setString("Searching for connection");
	sfm_seacrhClock.restart();
}

bool JoinGameState::ConnectToHost()
{
	bool madeConnection = false;

	if (m_currentHostSelected < 0 || m_currentHostSelected > MAXLIST)
	{
		m_currentHostSelected = -1;
	}

	if (m_currentHostSelected != -1)
	{
		if (m_hostList[m_currentHostSelected].sfm_otherIP != sf::IpAddress::None)
		{
			//Send 20 UDP packets to compensate for lost packets and
			//confirm the client data was sent
			for (int i = 0; i < 20; i++)
			{
				SendUDPString(m_Settings->machineName, m_hostList[m_currentHostSelected].sfm_otherIP);
			}
			
			m_Settings->sfm_opponentIP = m_hostList[m_currentHostSelected].sfm_otherIP;
			m_Settings->sfm_opponentName = m_hostList[m_currentHostSelected].mstr_otherName;
			madeConnection = true;
		}
	}
	
	return madeConnection;
}