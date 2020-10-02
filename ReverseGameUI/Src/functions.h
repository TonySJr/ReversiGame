#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//bool LoadTexture();
Vector2i array_walls(int x, int y);
void Physics();
void Physics(std::array<char, Board_Cells>& board,Vector2i &);
bool InitTextures();
void draw(class RenderWindow& example);
void mouseShedule(class RenderWindow& example);
void Swap(char*arr,int x1,int y1, int x2, int y2);
//	AI things
void WeightCalculate(std::array<char, Board_Cells> &board);
void AI_turn(std::vector<int> &turns);
void CopyBoardAI(std::array<char, Board_Cells> &board);
