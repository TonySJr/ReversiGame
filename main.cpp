#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
#include "figure.h"
#include "AI.h"
#include <thread>
#include "UI.h"
#include "Board.h" 
#include "Game.h"

Game Reversi;
// UI Class Init
UI User1;


bool changes_flag = true;
int globalcounter = 0;

//  functions 
bool end_procedure(class RenderWindow& window);
using namespace sf;

Vector2f textZeropos(520, 0);
sf::Text text;



//extern std::vector<int> cells_to_check;
AI Jarvis;
bool game_on = true;
Board ReversiBoard;
int main()
{
    //  --------------------------------------------------------------------------------------------[1]
    // create the window
    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "ReversiGame");


    
    sf::Font font;
    if (!font.loadFromFile("Ritalin.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font
    text.setStyle(sf::Text::Style::Bold);

    // set the character size
    text.setCharacterSize(16); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Black);
    text.setPosition(textZeropos);
    
    if (!InitTextures()) return 0;
    // first init board
    Jarvis.findPossibleMoves();
    for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
    {
        ReversiBoard.p_LastBoard[i] = ReversiBoard.getBoardCellFigure(i);
    }
    //  --------------------------------------------------------------------------------------------[2]
    // run the program as long as the window is open
    while (window.isOpen() && (game_on == true))
    {
        Event event;
        while ((window.pollEvent(event)) && (game_on == true))
        {
            // check the type of the event...
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // Lost focus
            case sf::Event::LostFocus:
                std::cout << "LOST FOCUS\n";
                break;
            case sf::Event::GainedFocus:
                std::cout << "Gained FOCUS\n";

            //  mouse event
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    User1.mouseShedule2(window, event.mouseButton.x, event.mouseButton.y);
                }
                if (event.mouseButton.button == sf::Mouse::Right) // should end game
                {
                    game_on = false;
                }
                break;
            }

            //  main gamecycle!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            default:

                if (changes_flag == true)
                {
                    ReversiBoard.DrawBoard(window);
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    //WeightCalculate(RevBoard);

                    if (Jarvis.AI_turn_flag)   //  if AI need to move
                    {
                        //  fill vector with turns
                        Jarvis.findPossibleMoves();
                        Jarvis.AI_turn(Jarvis.getMovesVector());
                    }

                    std::cout << "draw activity\n";
                    ReversiBoard.DrawBoard(window);
                    Jarvis.MovesVectorClear();
                }
                //Jarvis.AIWeightBoardfill(0);
                // if steps is over, or right mouse waas pressed end cycle
                if (globalcounter >= 60) game_on = false;

                break;
            }
        }
    }
    // посчитать кто победил
    //return end_procedure(window);
    return Reversi.endGame(window);
}

bool end_procedure(class RenderWindow& window)
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
    while(window.isOpen())
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