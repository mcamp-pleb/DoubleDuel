#ifndef GRIDBOARD_H
#define GRIDBOARD_H

#include <SFML/Graphics.hpp>
#include "SystemSettings.h"
#include "Card.h"

enum
{
	SQUARE_1,
	SQUARE_2,
	SQUARE_3,
	SQUARE_4,
	SQUARE_5,
	SQUARE_6,
	SQUARE_7,
	SQUARE_8,
	SQUARE_9,
	MAX_SQUARES,
	MAX_ROWS = 3,
	MAX_COLS = 3
};

class GridBoard
{
private:
	bool	m_gridSocket[MAX_SQUARES];
	bool	m_squareHighlight[MAX_ROWS][MAX_COLS];

	int		m_lastCardPlaced;

	Card	m_cardsOnBoard[MAX_SQUARES];
	
	sf::FloatRect	m_squareHitBox[MAX_ROWS][MAX_COLS];
	sf::Texture		m_boardTexture;
	sf::Sprite		m_board;
public:
	GridBoard();
	void SetHighlightedSquare(const bool &setBool, const int &row, const int &col) { m_squareHighlight[row][col] = setBool; };
	bool GetHighlightedSquareBool(const int &row, const int &col) {	return m_squareHighlight[row][col];	};
	bool IsOccupied(int square) { return m_gridSocket[square]; };
	int	GetHighlightedSpace();

	void ClearCards();
	void InsertCard(const Card &card, int square);
	void UpdateBoard();
	void CompareSquares(int targetSquare, int topSquare = -1, int leftSquare = -1, int rightSquare = -1, int bottomSquare = -1);
	void DrawBoard(SystemSettings *settings);
	void DrawCards(SystemSettings *settings);
	void DrawHighlight(SystemSettings *settings, int row, int col);

	Card &GetHand(int square) { return m_cardsOnBoard[square]; };

	sf::FloatRect GetHitBox(int row, int col)const { return m_squareHitBox[row][col]; }
};

#endif