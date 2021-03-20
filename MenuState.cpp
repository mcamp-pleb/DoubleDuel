#include "MenuState.h"
#include "DoubleDuel.h"
#include <SFML\Network.hpp>

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
	Cleanup();
}

void MenuState::Init(SystemSettings &settings)
{
	m_Settings = &settings;

	//Init Buttons
	m_title.setString("Double Duel");
	m_title.setFillColor(sf::Color::White);
	m_title.setCharacterSize(60);
	m_title.setFont(m_Settings->sfm_Font);
	m_title.setPosition(sf::Vector2f((m_Settings->resWidth / 2) - (m_title.getLocalBounds().width / 2),
		50.0f));

	m_btnHost.SetFont(m_Settings->sfm_Font);
	m_btnJoin.SetFont(m_Settings->sfm_Font);
	m_btnOptions.SetFont(m_Settings->sfm_Font);

	m_btnHost.SetTitle("Host");
	m_btnJoin.SetTitle("Join");
	m_btnOptions.SetTitle("Options");

	m_btnHost.SetPos((m_Settings->resWidth / 2.0f) - m_btnHost.GetSize().width / 2.0f, (m_Settings->resHight / 1.5f) + m_btnHost.GetSize().height);
	m_btnJoin.SetPos((m_Settings->resWidth / 2.0f) - m_btnJoin.GetSize().width / 2.0f, (m_Settings->resHight / 1.5f) + m_btnJoin.GetSize().height + 40);
	m_btnOptions.SetPos((m_Settings->resWidth / 2.0f) - m_btnOptions.GetSize().width / 2.0f, (m_Settings->resHight / 1.5f) + m_btnOptions.GetSize().height + 80);

	m_btnHost.SetColor(sf::Color::White);
	m_btnJoin.SetColor(sf::Color::White);
	m_btnOptions.SetColor(sf::Color::White);

	//Init Background
	m_bg.setSize(sf::Vector2f(m_Settings->resWidth, m_Settings->resHight));
	m_bg.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_bg.setFillColor(sf::Color(75, 75, 75, 255));

	m_Settings->sfm_opponentIP = sf::IpAddress::None;
	m_Settings->sfm_opponentName = "";
}

void MenuState::Cleanup()
{

}

void MenuState::HandleEvents()
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
			if (m_btnHost.IsClicked(m_Settings))
			{
				m_Settings->currentState = States::HOST;
				m_Settings->changeState = true;
			}
			if (m_btnJoin.IsClicked(m_Settings))
			{
				m_Settings->currentState = States::JOIN;
				m_Settings->changeState = true;
			}
			if (m_btnOptions.IsClicked(m_Settings))
			{
				m_Settings->currentState = States::OPTIONS;
				m_Settings->changeState = true;
			}
		}
	}
}

void MenuState::Update()
{
	m_btnHost.CheckMouse(m_Settings->worldPos);
	m_btnJoin.CheckMouse(m_Settings->worldPos);
	m_btnOptions.CheckMouse(m_Settings->worldPos);
}

void MenuState::Draw()
{
	m_Settings->sfm_window.clear();
	m_Settings->sfm_window.draw(m_bg);
	m_Settings->sfm_window.draw(m_title);
	m_btnHost.Draw(m_Settings);
	m_btnJoin.Draw(m_Settings);
	m_btnOptions.Draw(m_Settings);
	m_Settings->sfm_window.display();
}