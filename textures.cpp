#include "pch.h"
#include "FigureNames.h"
#include "figure.h"
#include "functions.h"
using namespace sf;

/*
std::array<char,Board_Cells> RevBoard ={'0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','B','R','0','0','0',
                                        '0','0','0','R','B','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0'};

std::array<char,Board_Cells> LastBoard = { '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','B','R','0','0','0',
                                        '0','0','0','R','B','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0',
                                        '0','0','0','0','0','0','0','0' };
//
*/
figure BoardSprite1("Images/Board.png",0,0);
figure BoardSprite2("Images/Board.png", 517, 0);
figure BlackCoin(0, 0, "Images/BlackCoin.png",2.f,2.f);
figure RedCoin(0, 0, "Images/RedCoin.png",0.5f,0.5f);
figure ColoredSquare(0, 0, "Images/ColoredSquare2.png", 1.0f, 1.0f);

bool InitTextures()
{
    if (!BoardSprite1.textureready())
        return false;

    if (!BoardSprite2.textureready())
        return false;

    if (!BlackCoin.textureready())
        return false;

    if (!RedCoin.textureready())
        return false;


    if (!ColoredSquare.textureready())
        return false;

    //if all load return 1
    return true;
}
