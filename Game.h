#pragma once
#include "pch.h"
#include "FigureNames.h"
//	Game class have a methods to control the game flow
//	like start game/ pause game ens so on

class Game
{
public:
	Game()
	{


	}
	void startMenu();
	void startGame();
	bool endGame(class RenderWindow& window);
	void pauseGame();
	void UnpauseGame();
};

