#include "MultiplayerState.h"

MultiplayerState::MultiplayerState()
	:m_currentMachinePlayer(-1), highlightGrid(false), m_disconnected(true)
{

}

MultiplayerState::~MultiplayerState()
{
	Cleanup();
}

void MultiplayerState::Init(SystemSettings &settings)
{
	this->m_Settings = &settings;
	m_currentMachinePlayer = m_Settings->currentMachinePlayer - 1;

	//Init Background
	m_bg.setSize(sf::Vector2f(m_Settings->resWidth, m_Settings->resHight));
	m_bg.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_bg.setFillColor(sf::Color(75, 75, 75, 255));

	switch (m_currentMachinePlayer)
	{
	case PLAYER_1:
		m_host.listen(m_Settings->inPortTCP);
		m_host.accept(m_tcpSocket);
		m_players[PLAYER_1].Init(m_Settings->machineName, P_1, true, FACE_UP, m_Settings);
		m_players[PLAYER_2].Init(m_Settings->sfm_opponentName, P_2, false, FACE_DOWN, m_Settings);
		PackType(INIT);
		PackPlayers();
		SynchronizeCards(OUT);
		SendData();
		m_disconnected = false;
		break;
	case PLAYER_2:
		if (m_tcpSocket.connect(m_Settings->sfm_opponentIP, m_Settings->inPortTCP) != sf::Socket::Error)
		{
			m_players[PLAYER_1].Init(m_Settings->sfm_opponentName, P_1, true, FACE_DOWN, m_Settings);
			m_players[PLAYER_2].Init(m_Settings->machineName, P_2, false, FACE_UP, m_Settings);
			HandlePackets();
			m_disconnected = false;
		}
		break;
	default:
		//problem
		break;
	}
	m_turnText.setFont(settings.sfm_Font);
	

	sfm_selector.add(m_tcpSocket);
	m_winner.Init(m_Settings);
}

void MultiplayerState::Cleanup()
{
	sfm_selector.remove(m_tcpSocket);
	m_tcpSocket.disconnect();
	m_disconnected = true;
}

void MultiplayerState::HandleEvents()
{
	sf::Event event;
	while (m_Settings->sfm_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Disconnect();
			Cleanup();
			m_Settings->sfm_window.close();
			break;
		case sf::Event::KeyPressed:
			//Swaps Player 1 and 2 currently playing
			//Used just for debuging
			if (m_Settings->debug)
			{
				if (event.key.code == sf::Keyboard::S)
				{
					if (m_currentMachinePlayer == PLAYER_1)
					{
						m_Settings->currentMachinePlayer = P_2;
						m_currentMachinePlayer = PLAYER_2;
						m_players[PLAYER_2].SetTurnStatus(true);
						m_players[PLAYER_2].CardFace(FACE_UP);

						m_players[PLAYER_1].SetTurnStatus(false);
						m_players[PLAYER_1].CardFace(FACE_DOWN);
					}
					else
					{
						m_Settings->currentMachinePlayer = P_1;
						m_currentMachinePlayer = PLAYER_1;
						m_players[PLAYER_1].SetTurnStatus(true);
						m_players[PLAYER_1].CardFace(FACE_UP);

						m_players[PLAYER_2].SetTurnStatus(false);
						m_players[PLAYER_2].CardFace(FACE_DOWN);
					}
				}
			}
			break;
		case sf::Event::MouseMoved:
			if(!m_Settings->sfm_window.getViewport(m_Settings->sfm_view).contains(m_Settings->pixelPos))
			{
				m_Settings->mouseHeld = false;
				m_players[m_currentMachinePlayer].DropCard();
			}
			break;
		case sf::Event::MouseButtonPressed:
			//Debug quick exit
			if (m_Settings->debug)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					m_Settings->currentState = States::MAIN_MENU;
					m_Settings->changeState = true;
					break;
				}
			}
			if (EndGameCheck())
			{
				switch (m_winner.HandleButtons(m_Settings))
				{
				case 1:
					//Rematch
					m_Settings->rematch = true;
					PackType(REMATCH);
					SendData();
					Disconnect();
					Cleanup();
					m_Settings->currentState = States::MAIN_MENU;
					m_Settings->changeState = true;
				case 2:
					//Exit
					Disconnect();
					Cleanup();
					m_Settings->currentState = States::MAIN_MENU;
					m_Settings->changeState = true;
				default:
					break;
				}
				
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Placing the card down on the board
				if (m_players[m_currentMachinePlayer].IsHoldingCard())
				{
					int increment = 0; //NOTE: quick conversion of 3 x 3 sorting to 0 - 8 increment
					
					for (int i = 0; i < MAX_ROWS; i++)
					{
						for (int j = 0; j < MAX_COLS; j++)
						{
							if (m_board.GetHitBox(i, j).contains(m_Settings->worldPos) && !m_board.IsOccupied(increment))
							{
								m_players[m_currentMachinePlayer].PlaceCard(m_board);
								m_board.GetHand(m_board.GetHighlightedSpace()).SetPos(m_board.GetHitBox(i, j).left, m_board.GetHitBox(i, j).top);
								
								//Sync and Send data---
								switch (m_currentMachinePlayer)
								{
								case PLAYER_1:
									m_players[PLAYER_1].SetTurnStatus(false);
									m_players[PLAYER_2].SetTurnStatus(true);
									PackType(TOCLIENT);
									PackPlayers();
									PackCard(m_players[PLAYER_1].GetCurrentHeldCard(), increment);
									SendData();
									break;
								case PLAYER_2:
									m_players[PLAYER_1].SetTurnStatus(true);
									m_players[PLAYER_2].SetTurnStatus(false);
									PackType(TOHOST);
									PackPlayers();
									PackCard(m_players[PLAYER_2].GetCurrentHeldCard(), increment);
									SendData();
									break;
								}
								//--------------------
							}
							increment++;
						}
					}
					m_players[m_currentMachinePlayer].DropCard();
				}
				m_Settings->mouseHeld = false;
			}
			break;
		}
	}
	//Handle the network
	HandlePackets();
}

void MultiplayerState::Update()
{
	//Update players turn text
	if (m_players[PLAYER_1].GetTurnStatus())
	{
		m_turnText.setString(m_players[PLAYER_1].GetPlayerName() + "'s Turn");
		m_turnText.setFillColor(sf::Color::Blue);
	}
	else
	{
		m_turnText.setString(m_players[PLAYER_2].GetPlayerName() + "'s Turn");
		m_turnText.setFillColor(sf::Color::Red);
	}
	m_turnText.setPosition(sf::Vector2f((m_Settings->resWidth / 2.0f) - (m_turnText.getLocalBounds().width / 2.0f), 0.0f));
	
	//Update the state of the cards on the board
	m_board.UpdateBoard();

	//Update player score
	//NOTE: update must come before endgame or final turn will not count
	m_players[PLAYER_1].ResetScore();
	m_players[PLAYER_2].ResetScore();

	for (int i = 0; i < MAX_SQUARES; i++)
	{
		if (m_board.IsOccupied(i))
		{
			switch (m_board.GetHand(i).GetCardOwner())
			{
			case 1:
				m_players[PLAYER_1].SetScore(m_players[PLAYER_1].GetScore() + 1);
				break;
			case 2:
				m_players[PLAYER_2].SetScore(m_players[PLAYER_2].GetScore() + 1);
				break;
			}
		}
	}
	
	//Win or Loss check
	//NOTE: Once to game is over all playable functions will stop
	if (EndGameCheck())
	{
		if (m_players[PLAYER_1].GetScore() > m_players[PLAYER_2].GetScore())
		{
			//Player 1 wins
			m_winner.SetWinner(m_players[PLAYER_1].GetPlayerName());
		}
		else
		{
			//Player 2 wins
			m_winner.SetWinner(m_players[PLAYER_2].GetPlayerName());
		}
		m_winner.Update(m_Settings);
	}
	else
	{
		//moving the card by ID
		if (m_players[m_currentMachinePlayer].GetTurnStatus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_players[m_currentMachinePlayer].MouseOnCard(m_Settings->worldPos) || m_Settings->mouseHeld)
			{
				switch (m_players[m_currentMachinePlayer].GetCurrentHeldCard())
				{
				case 100:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 100);
					break;
				case 101:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 101);
					break;
				case 102:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 102);
					break;
				case 103:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 103);
					break;
				case 104:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 104);
					break;
				case 200:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 200);
					break;
				case 201:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 201);
					break;
				case 202:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 202);
					break;
				case 203:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 203);
					break;
				case 204:
					m_players[m_currentMachinePlayer].MoveCard(m_Settings->deltaPos, 204);
					break;
				}
				m_players[m_currentMachinePlayer].HoldCard();
				m_Settings->mouseHeld = true;
			}
		}

		//highlight the grid
		if (m_players[m_currentMachinePlayer].IsHoldingCard())
		{
			for (int i = 0; i < MAX_ROWS; i++)
			{
				for (int j = 0; j < MAX_COLS; j++)
				{
					if (m_board.GetHitBox(i, j).contains(m_Settings->worldPos))
					{
						m_board.SetHighlightedSquare(true, i, j);
					}
					else
					{
						m_board.SetHighlightedSquare(false, i, j);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < MAX_ROWS; i++)
			{
				for (int j = 0; j < MAX_COLS; j++)
				{
					m_board.SetHighlightedSquare(false, i, j);
				}
			}
		}

		
	}
	
	//Return to main menu when someone disconnects
	if (m_disconnected)
	{
		m_Settings->currentState = States::MAIN_MENU;
		m_Settings->changeState = true;
	}
}

void MultiplayerState::Draw()
{
	m_Settings->sfm_window.clear();
	m_Settings->sfm_window.draw(m_bg);
	m_board.DrawBoard(m_Settings);
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (m_board.GetHighlightedSquareBool(i, j))
			{
				m_board.DrawHighlight(m_Settings, i, j);
			}
		}
	}
	m_board.DrawCards(m_Settings);
	if (m_currentMachinePlayer == 0)
	{
		//Draw Player 1 cards over Player 2
		m_players[PLAYER_2].DrawGUI(m_Settings);
		m_players[PLAYER_1].DrawGUI(m_Settings);
	}
	else
	{
		//Draw Player 2 cards over Player 1
		m_players[PLAYER_1].DrawGUI(m_Settings);
		m_players[PLAYER_2].DrawGUI(m_Settings);
	}
	m_Settings->sfm_window.draw(m_turnText);
	if (EndGameCheck())
	{
		m_winner.Draw(m_Settings);
	}
	m_Settings->sfm_window.display();
}

void MultiplayerState::SynchronizeCards(const int &inOrOut)
{
	//Handle Network Data going in or out
	int id;
	int top, bottom, left, right;
	switch (inOrOut)
	{
	case IN:
		for (int loop = 0; loop < 10; loop++)
		{
			packet >> id >> top >> bottom >> left >> right;

			for (int player = 0; player < 2; player++)
			{
				for (int i = 0; i < 5; i++)
				{
					if (m_players[player].GetCard(i).GetCardID() == id)
					{
						m_players[player].GetCard(i).SetTopNum(top);
						m_players[player].GetCard(i).SetBottompNum(bottom);
						m_players[player].GetCard(i).SetLeftNum(left);
						m_players[player].GetCard(i).SetRightNum(right);
						m_players[player].GetCard(i).UpdateDigits(top, bottom, left, right);
					}
				}
			}
		}
		break;
	case OUT:
		for (int i = 0; i < 5; i++)
		{
			packet
				<< m_players[PLAYER_1].GetCard(i).GetCardID()
				<< m_players[PLAYER_1].GetCard(i).GetTopNum()
				<< m_players[PLAYER_1].GetCard(i).GetBottompNum()
				<< m_players[PLAYER_1].GetCard(i).GetLeftNum()
				<< m_players[PLAYER_1].GetCard(i).GetRightNum()

				<< m_players[PLAYER_2].GetCard(i).GetCardID()
				<< m_players[PLAYER_2].GetCard(i).GetTopNum()
				<< m_players[PLAYER_2].GetCard(i).GetBottompNum()
				<< m_players[PLAYER_2].GetCard(i).GetLeftNum()
				<< m_players[PLAYER_2].GetCard(i).GetRightNum();
		}
		break;
	default:
		//If not sending or receiving then don't do anything;
		break;
	}
}

void MultiplayerState::Disconnect()
{
	PackType(DISCONNECT);
	m_tcpSocket.send(packet);
	m_tcpSocket.disconnect();
	m_host.close();
	m_disconnected = true;
}

void MultiplayerState::SendData()
{
	switch (SendTCPData(m_tcpSocket, packet))
	{
	case sf::Socket::Done:
		break;
	case sf::Socket::NotReady:
	case sf::Socket::Partial:
		break;
	case sf::Socket::Disconnected:	//Create disconnect state/message
	case sf::Socket::Error:
		m_disconnected = true;
		break;
	default:
		break;
	}
	packet.clear();
}

void MultiplayerState::HandlePackets()
{
	sf::Socket::Status m = ReceiveTCPData(m_tcpSocket, packet);
	switch (m)
	{
	case sf::Socket::Done:
		//unpack first int and handle the data
		switch (UnpackType())
		{
		case INIT:
			UnpackPlayers();
			SynchronizeCards(IN);
			break;
		case TOHOST:
			UnpackPlayers();
			UnpackCard(PLAYER_2);
			break;
		case TOCLIENT:
			UnpackPlayers();
			UnpackCard(PLAYER_1);
			break;
		case DISCONNECT:
			Disconnect();
			break;
		case REMATCH:
			m_Settings->rematch = true;
			Disconnect();
			break;
		default:
			break;
		}
		packet.clear();
		break;
	case sf::Socket::NotReady:
	case sf::Socket::Partial:
		break;
	case sf::Socket::Disconnected:
	case sf::Socket::Error:
		m_disconnected = true;
		break;
	default:
		break;
	}
	
}

void MultiplayerState::PackType(const int &type)
{
	packet << type;
}

int MultiplayerState::UnpackType()
{
	int type;

	packet >> type;

	return type;
}

void MultiplayerState::PackPlayers()
{
	packet << m_players[PLAYER_1].GetTurnStatus() << m_players[PLAYER_2].GetTurnStatus();
}

void MultiplayerState::UnpackPlayers()
{
	bool p1, p2;

	packet >> p1 >> p2;
	m_players[PLAYER_1].SetTurnStatus(p1);
	m_players[PLAYER_2].SetTurnStatus(p2);
}

void MultiplayerState::PackCard(const int &ID, const int &square)
{
	packet << ID << square;
}

void MultiplayerState::UnpackCard(const int &player)
{
	int id, square, i, j;

	packet >> id >> square;

	//Manually puts card into correct square
	switch (square)
	{
	case 0:
		i = 0;
		j = 0;
		break;
	case 1:
		i = 0;
		j = 1;
		break;
	case 2:
		i = 0;
		j = 2;
		break;
	case 3:
		i = 1;
		j = 0;
		break;
	case 4:
		i = 1;
		j = 1;
		break;
	case 5:
		i = 1;
		j = 2;
		break;
	case 6:
		i = 2;
		j = 0;
		break;
	case 7:
		i = 2;
		j = 1;
		break;
	case 8:
		i = 2;
		j = 2;
		break;
	default:
		i = -1;
		j = -1;
		break;
	}
	if (i != -1 || j != -1)
	{
		if (player == PLAYER_1)
		{
			m_board.SetHighlightedSquare(true, i, j);
			m_players[PLAYER_1].SetCurrentHeldCard(id);
			m_players[PLAYER_1].PlaceCard(m_board);
			m_board.GetHand(square).SetPos(m_board.GetHitBox(i, j).left, m_board.GetHitBox(i, j).top);
		}
		else if (player == PLAYER_2)
		{
			m_board.SetHighlightedSquare(true, i, j);
			m_players[PLAYER_2].SetCurrentHeldCard(id);
			m_players[PLAYER_2].PlaceCard(m_board);
			m_board.GetHand(square).SetPos(m_board.GetHitBox(i, j).left, m_board.GetHitBox(i, j).top);
		}
	}
}

bool MultiplayerState::EndGameCheck()
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		if (!m_board.IsOccupied(i))
		{
			return false;
		}
	}
	return true;
}