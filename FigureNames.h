#pragma once
#include <SFML/Graphics.hpp>
#define ROWS 8
#define COLUMS 8
#define Board_Cells 64
using namespace sf;

extern char RevBoard[Board_Cells];
extern int AIWeightBoard[Board_Cells];
extern class figure Board;
extern class figure Board2;
extern class figure BlackCoin;
extern class figure RedCoin;
extern class figure ColoredSquare;

// AI THINGS
extern bool AI_turn_flag;

