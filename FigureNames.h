#pragma once
#include <SFML/Graphics.hpp>
#define ROWS 8
#define COLUMS 8
#define Board_Cells 64
//  values
#define WindowWidth 1029
#define WindowHeight 512
using namespace sf;
//	---
extern class UI User1;
extern class Board ReversiBoard;
extern class AI Jarvis;
//	---
//extern std::array<char,Board_Cells> RevBoard;
//extern std::array<char, Board_Cells> LastBoard;
//extern std::array<int, Board_Cells> AIWeightBoard;
extern class figure BoardSprite1;
extern class figure BoardSprite2;
extern class figure BlackCoin;
extern class figure RedCoin;
extern class figure ColoredSquare;


extern bool changes_flag;
extern Text text;
extern Vector2f textZeropos;
//extern std::vector<int> cells_to_check;

// AI THINGS
//extern bool AI_turn_flag;
extern int globalcounter;
extern bool changes_flag;
