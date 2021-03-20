#include "EndGame.h"
#include "GameState.h"

EndGame::EndGame()
{
	
}

EndGame::~EndGame()
{

}

void EndGame::Init(SystemSettings *settings)
{
	m_dialogBox.setSize(sf::Vector2f(500.0f, 300.0f));
	m_dialogBox.setPosition(sf::Vector2f((settings->resWidth / 2.0f) - (m_dialogBox.getSize().x / 2.0f), 
											(settings->resHight / 2.0f) - (m_dialogBox.getSize().y / 2.0f)));
	m_dialogBox.setFillColor(sf::Color(0, 0, 0, 220));

	m_message.setFont(settings->sfm_Font);
	m_clientMessage.setFont(settings->sfm_Font);
	m_rematch.SetFont(settings->sfm_Font);
	m_exit.SetFont(settings->sfm_Font);

	m_message.setString("");
	m_clientMessage.setString("Waiting for Host");
	m_rematch.SetTitle("Rematch");
	m_exit.SetTitle("Exit");

	m_clientMessage.setPosition(m_dialogBox.getGlobalBounds().left + (m_dialogBox.getGlobalBounds().width / 2.0f) - (m_clientMessage.getLocalBounds().width / 2.0f),
		m_dialogBox.getGlobalBounds().top + (m_dialogBox.getGlobalBounds().height - 120.0f));

	m_rematch.SetPos(m_dialogBox.getGlobalBounds().left + 10.0f, 
					(m_dialogBox.getGlobalBounds().top + m_dialogBox.getGlobalBounds().height) - (m_rematch.GetSize().height + 20.0f));

	m_exit.SetPos((m_dialogBox.getGlobalBounds().left + m_dialogBox.getGlobalBounds().width) - (m_exit.GetSize().width + 10.0f),
					(m_dialogBox.getGlobalBounds().top + m_dialogBox.getGlobalBounds().height) - (m_exit.GetSize().height + 20.0f));

	m_message.setFillColor(sf::Color::White);
	m_clientMessage.setFillColor(sf::Color::White);
	m_rematch.SetColor(sf::Color::White);
	m_exit.SetColor(sf::Color::White);
}

void EndGame::SetWinner(std::string player)
{
	m_message.setString(player + " Wins");
	m_message.setPosition(m_dialogBox.getGlobalBounds().left + (m_dialogBox.getGlobalBounds().width / 2.0f) - (m_message.getLocalBounds().width / 2.0f),
		m_dialogBox.getGlobalBounds().top + 40.0f);
}

int EndGame::HandleButtons(SystemSettings *settings)
{
	if (settings->currentMachinePlayer == 1)
	{
		if (m_rematch.IsClicked(settings))
		{
			return 1;
		}
		if (m_exit.IsClicked(settings))
		{
			return 2;
		}
	}
	return 0;
}

void EndGame::Update(SystemSettings *settings)
{
	m_rematch.CheckMouse(settings->worldPos);
	m_exit.CheckMouse(settings->worldPos);
}

void EndGame::Draw(SystemSettings *settings)
{
	settings->sfm_window.draw(m_dialogBox);
	settings->sfm_window.draw(m_message);
	if (settings->currentMachinePlayer == 1)
	{
		m_rematch.Draw(settings);
		m_exit.Draw(settings);
	}
	else
	{
		settings->sfm_window.draw(m_clientMessage);
	}
}