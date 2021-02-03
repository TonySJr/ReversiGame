#pragma once
#include "pch.h"
#include "FigureNames.h"
#include <iostream>

/*
	 ласс доски включает массив(доску) 
	имеет методы установки и просмотра соответствующей клетки доски


*/


class Board : sf::RenderWindow
{
public:
	Board()
	{
		p_Board.fill('0');
		p_LastBoard.fill('0');
		p_Board[27] = 'B';
		p_Board[28] = 'R';
		p_Board[35] = 'R';
		p_Board[36] = 'B';

	}

	void setBoardCell(int& cell, char& color);
	void setBoardCell(int cell, char color);
	char getBoardCellFigure(int cell);
	int getBoardSize();
	Vector2i array_walls(int x, int y);
	void Physics(sf::Vector2i& cell_pos);
	//	---
	void DrawBoard(class RenderWindow& window);
	void DrawBoard(class RenderWindow& window, std::array<char, Board_Cells>& board);



private:

	bool m_board_end_flag = false;

	std::array<Vector2i, 8> m_array_Dir = { sf::Vector2i(0,-1),sf::Vector2i(-1,-1),
	sf::Vector2i(-1,0),sf::Vector2i(-1,1),sf::Vector2i(0,1),sf::Vector2i(1,1),
	sf::Vector2i(1,0),sf::Vector2i(1,-1)};
	//sf::Vector2i UP1(0, -1) , UPLEFT(-1, -1), LEFT(-1, 0), LEFTDOWN(-1, 1), DOWN(0, 1),
	//RIGHTDOWN(1, 1), RIGHT(1, 0), UPRIGHT(1, -1);
	//sf::Vector2i* m_array_Dir[] = { &UP, &UPLEFT, &LEFT, &LEFTDOWN, &DOWN, &RIGHTDOWN, &RIGHT, &UPRIGHT };
public:
	std::array<char, Board_Cells> p_LastBoard;
	std::array<char, Board_Cells> p_Board;
	/*
	std::array<char, Board_Cells> p_Board =	  { 'R','R','R','0','B','0','0','0',
												'B','R','R','B','B','B','0','0',
												'B','R','R','B','B','B','0','B',
												'0','B','R','R','R','B','R','B',
												'R','R','B','B','B','B','B','B',
												'0','B','0','B','B','B','0','B',
												'0','0','0','B','B','R','B','0',
												'0','0','0','B','B','B','0','R' };
												*/
	//	÷вет фишки дл€ просчета физики
	char p_button_flag = 'R';


};


