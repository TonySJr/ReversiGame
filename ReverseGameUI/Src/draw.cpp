#include "pch.h"
#include "FigureNames.h"
#include "figure.h"
#include "functions.h"
#include "AI.h"

#define RED false
#define AI_turn true

using namespace sf;
extern bool changes_flag;
extern Text text;
extern Vector2f textZeropos;
extern std::vector<int> cells_to_check;

void draw(class RenderWindow& window)
{
    window.clear(Color::Black);
    // draw board
    window.draw(Board.spritefigure());
    window.draw(Board2.spritefigure());
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMS; x++)
        {
            switch (RevBoard[x + y*ROWS])
            {
            case 'B':
            {
                BlackCoin.setPos((float)x, (float)y);
                window.draw(BlackCoin.spritefigure());
                break;
            }
            case 'R':
            {
                RedCoin.setPos((float)x, (float)y);
                window.draw(RedCoin.spritefigure());
                break;
            }
            default:
                break;
            }
            //  draw squares with indication of coin
            ColoredSquare.ColorChange(AIWeightBoard[x + y * ROWS]);
            ColoredSquare.setPos(8.08f+x, y);           //textZeropos.x + (64 * x), textZeropos.y + (64 * y));
            window.draw(ColoredSquare.spritefigure());
            //  get vectors values and draw it
            std::string s = std::to_string(cells_to_check.at(x + y * ROWS));
            text.setString(s);
            text.setPosition(textZeropos + Vector2f(64 * x, 64 * y));
            window.draw(text);
        }
    }

    // end the current frame
    window.display();
    changes_flag = false;
}
extern int globalcounter;
int button_delay = 0;
//char button_flag = 'R';
bool button_flag = false;
Vector2i mouse_Position;
std::chrono::steady_clock::time_point start, end;
void mouseShedule(class RenderWindow& window)
{

    std::chrono::duration<double> elapsed_seconds = end - start;
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        start = std::chrono::steady_clock::now();
        if (elapsed_seconds.count() > 0.5f)
        {
            mouse_Position = (Mouse::getPosition(window)) / 64; // window is a sf::Window
            // get the local mouse position (relative to a window)
            if (button_flag == RED)                    //red human turn
            {
                RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'R';
                std::cout << "RED\n";
                globalcounter++;
                std::cout << " Turn - " << globalcounter << "\n";
                button_flag = !button_flag;
            }
            else                                        // black AI turn
            {
                AI Jarvis;
                Jarvis.x = mouse_Position.x;
                Jarvis.y = mouse_Position.y;
                // AI back move
                RevBoard[Jarvis.x + Jarvis.y * ROWS] = 'B';
                std::cout << "AI turn\n";
                globalcounter++;
                std::cout << " Turn - " << globalcounter << "\n";
                button_flag = !button_flag;

            }
            /*
            //  human way to play game
            else
            {
                RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'B';
                std::cout << "BLACK\n";
                globalcounter++;
                std::cout << " Turn - " << globalcounter << "\n";
                button_flag = !button_flag;

            }
            */
            button_delay = 0;
            //button_flag = !button_flag;
            WeightCalculate();

            std::cout << "mouse activity\n";

            changes_flag = true;
        }
    }
    end = std::chrono::steady_clock::now();
    
}
