#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
#include "figure.h"

//  values
#define WindowWidth 1029
#define WindowHeight 512

bool changes_flag = true;
int globalcounter = 0;

//  functions 
bool end_procedure(class RenderWindow& window);
using namespace sf;

Vector2f textZeropos(539, 13);
sf::Text text;

extern std::vector<int> cells_to_check;

int main()
{
    // create the window
    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "ReversiGame");
    
    sf::Font font;
    if (!font.loadFromFile("Ritalin.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the character size
    text.setCharacterSize(32); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);
    text.setPosition(textZeropos);

    if (!InitTextures()) return 0;

    //WeightCalculate(RevBoard);
    //Physics();
    // run the program as long as the window is open
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        mouseShedule(window);   // return changes_flag and put player coin on a table

        if (changes_flag == true)
        {
            Physics();
            WeightCalculate(RevBoard);
            std::cout << "draw activity\n";
            draw(window);
            //  fill vector with turns
            for (int i = 0; i < Board_Cells; i++)
            {
                if (RevBoard[i] == '0')
                {
                    cells_to_check.push_back(i);
                }
            }
            cells_to_check.clear();

        }
        // if steps is over, or right mouse waas pressed end cycle
        if ((globalcounter >= 60)||(Mouse::isButtonPressed(Mouse::Right))) break;
    }
    // посчитать кто победил
    return end_procedure(window);
}

bool end_procedure(class RenderWindow& window)
{
    int red = 0; int black = 0;

    for (int i = 0; i < Board_Cells; i++)
    {
        if (RevBoard[i] == 'R')
        {
            red++;
        }
        else if (RevBoard[i] == 'B')
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