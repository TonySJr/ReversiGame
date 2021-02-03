#include "pch.h"
#include "figure.h"
#include "FigureNames.h"
#include "Board.h"
#include "Game.h"

bool Game::endGame(class RenderWindow& window)
{

    int red = 0; int black = 0;

    for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
    {
        if (ReversiBoard.getBoardCellFigure(i) == 'R')
        {
            red++;
        }
        else if (ReversiBoard.getBoardCellFigure(i) == 'B')
        {
            black++;
        }
    }

    std::cout << " RED - " << red << " BLACK - " << black << "\n";
    Texture RED_texture, Black_texture, draw_texture;

    if (!RED_texture.loadFromFile("Images/RedCoin.png"))
    {
        // error...
        std::cout << "WINtexturefail\n";
        return 0;
    }
    if (!Black_texture.loadFromFile("Images/BlackCoin.png"))
    {
        // error...
        std::cout << "WINtexturefail\n";
        return 0;
    }
    if (!draw_texture.loadFromFile("Images/draw.png"))
    {
        // error...
        std::cout << "WINtexturefail\n";
        return 0;
    }
    Sprite WINSPRITE;
    WINSPRITE.setTextureRect(sf::IntRect(0, 0, WindowWidth, WindowHeight));

    if (red > black)
    {
        WINSPRITE.setTexture(RED_texture);
        RED_texture.setRepeated(true);
    }
    else if (black > red)
    {
        WINSPRITE.setTexture(Black_texture);
        Black_texture.setRepeated(true);
    }
    else
    {
        WINSPRITE.setTexture(draw_texture);
    }
    // rework for time mouse procedure

    changes_flag = true;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (Mouse::isButtonPressed(Mouse::Left))
                return 0;
        }
        if (changes_flag == true)
        {
            window.clear(Color::Black);
            // draw board
            window.draw(WINSPRITE);
            window.display();
            changes_flag = false;
        }
    }

}
