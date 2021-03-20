#include "GridBoard.h"

GridBoard::GridBoard()
	: m_lastCardPlaced(-1)
{
	//Init
	ClearCards();
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			m_squareHighlight[i][j] = false;
		}
	}

	//Clear out cards on board
	ClearCards();

	m_boardTexture.loadFromFile("image\\gameBoard.png");
	m_board.setTexture(m_boardTexture);

	//Center the board on a 1280x720 Res
	m_board.setPosition(sf::Vector2f((1280 / 2.0f) - (m_boardTexture.getSize().x / 2.0f), (720 / 2.0f) - (m_boardTexture.getSize().y / 2.0f)));

	//set hitbox
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			//NOTE: not even currently
			m_squareHitBox[i][j] = sf::FloatRect(sf::Vector2f(m_board.getGlobalBounds().left + (j * 171), m_board.getGlobalBounds().top + (i * 171)), sf::Vector2f(171.0f, 171.0f));
		}
	}
}

void GridBoard::ClearCards()
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		m_cardsOnBoard[i].Clear();
		m_gridSocket[i] = false;
	}
}

void GridBoard::InsertCard(const Card &card, int square)
{
	if (!m_gridSocket[square])
	{
		std::memcpy(&m_cardsOnBoard[square], &card, sizeof(card));
		m_cardsOnBoard[square].SetScale(1.0f);
		m_cardsOnBoard[square].SetFace(true);
		m_gridSocket[square] = true;
	}
	m_lastCardPlaced = square;
}

void GridBoard::UpdateBoard()
{
	switch (m_lastCardPlaced)
	{
	case SQUARE_1:
		CompareSquares(SQUARE_1, -1, -1, SQUARE_2, SQUARE_4);
		break;
	case SQUARE_2:
		CompareSquares(SQUARE_2, -1, SQUARE_1, SQUARE_3, SQUARE_5);
		break;
	case SQUARE_3:
		CompareSquares(SQUARE_3, -1, SQUARE_2, -1, SQUARE_6);
		break;
	case SQUARE_4:
		CompareSquares(SQUARE_4, SQUARE_1, -1, SQUARE_5, SQUARE_7);
		break;
	case SQUARE_5:
		CompareSquares(SQUARE_5, SQUARE_2, SQUARE_4, SQUARE_6, SQUARE_8);
		break;
	case SQUARE_6:
		CompareSquares(SQUARE_6, SQUARE_3, SQUARE_5, -1, SQUARE_9);
		break;
	case SQUARE_7:
		CompareSquares(SQUARE_7, SQUARE_4, -1, SQUARE_8, -1);
		break;
	case SQUARE_8:
		CompareSquares(SQUARE_8, SQUARE_5, SQUARE_7, SQUARE_9, -1);
		break;
	case SQUARE_9:
		CompareSquares(SQUARE_9, SQUARE_6, SQUARE_8, -1, -1);
		break;
	default:
		break;
	}

	for (int i = 0; i < MAX_SQUARES; i++)
	{
		GetHand(i).UpdateCardColor();
	}
}

//Compares squares around targeted square; 2 squares are the min and 4 the max
void GridBoard::CompareSquares(int targetSquare, int topSquare, int leftSquare, int rightSquare, int bottomSquare)
{
	if (topSquare > -1)
	{
		if (GetHand(targetSquare).GetTopNum() > GetHand(topSquare).GetBottompNum())
		{
			GetHand(topSquare).SetCardOwner(GetHand(targetSquare).GetCardOwner());
		}
	}
	if (leftSquare > -1)
	{
		if (GetHand(targetSquare).GetLeftNum() > GetHand(leftSquare).GetRightNum())
		{
			GetHand(leftSquare).SetCardOwner(GetHand(targetSquare).GetCardOwner());
		}
	}
	if (rightSquare > -1)
	{
		if (GetHand(targetSquare).GetRightNum() > GetHand(rightSquare).GetLeftNum())
		{
			GetHand(rightSquare).SetCardOwner(GetHand(targetSquare).GetCardOwner());
		}
	}
	if (bottomSquare > -1)
	{
		if (GetHand(targetSquare).GetBottompNum() > GetHand(bottomSquare).GetTopNum())
		{
			GetHand(bottomSquare).SetCardOwner(GetHand(targetSquare).GetCardOwner());
		}
	}
}

int	GridBoard::GetHighlightedSpace()
{
	int square = 0;

	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (GetHighlightedSquareBool(i, j))
			{
				return square;
			}
			square++;
		}
	}

	return -1;
}

void GridBoard::DrawBoard(SystemSettings *settings)
{
	settings->sfm_window.draw(m_board);
}

void GridBoard::DrawCards(SystemSettings *settings)
{
	for (int i = 0; i < MAX_SQUARES; i++)
	{
		if (m_gridSocket[i])
		{
			m_cardsOnBoard[i].DrawCard(settings);
		}
	}
}

void GridBoard::DrawHighlight(SystemSettings *settings, int row, int col)
{
	sf::RectangleShape selection(sf::Vector2f(m_squareHitBox[row][col].width, m_squareHitBox[row][col].height));

	selection.setPosition(m_squareHitBox[row][col].left, m_squareHitBox[row][col].top);
	
	settings->sfm_window.draw(selection);
}