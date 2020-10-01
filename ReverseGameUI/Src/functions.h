#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//bool LoadTexture();
Vector2i array_walls(int x, int y);
void Physics();
bool InitTextures();
void draw(class RenderWindow& example);
void mouseShedule(class RenderWindow& example);
void Swap(char*arr,int x1,int y1, int x2, int y2);
//	AI things
void WeightCalculate(std::array<char, Board_Cells> board);
void AI_turn(std::array<char, Board_Cells> &RevBoard);
