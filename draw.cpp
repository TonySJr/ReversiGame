#include "pch.h"
#include "FigureNames.h"
#include "figure.h"
#include "functions.h"

#define RED true

using namespace sf;
extern bool changes_flag;
extern Text text;
extern Vector2f textZeropos;

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
 
            ColoredSquare.ColorChange(AIWeightBoard[x + y * ROWS]);
            
            ColoredSquare.setPos(8.08f+x, y);           //textZeropos.x + (64 * x), textZeropos.y + (64 * y));
            window.draw(ColoredSquare.spritefigure());

            std::string s = std::to_string(AIWeightBoard[x + y * ROWS]);
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
bool button_flag = true;
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
            if (button_flag == RED)                    //red
            {
                RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'R';
                std::cout << "RED\n";
                globalcounter++;
                std::cout << " Turn - " << globalcounter << "\n";
            }
            else
            {
                RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'B';
                std::cout << "BLACK\n";
                globalcounter++;
                std::cout << " Turn - " << globalcounter << "\n";
            }
            button_delay = 0;
            button_flag = !button_flag;
            WeightCalculate();

            std::cout << "mouse activity\n";

            changes_flag = true;
        }
    }
    end = std::chrono::steady_clock::now();
    
}

/*

if (Mouse::isButtonPressed(Mouse::Left))
{
    if (button_delay > 1000)
    {
        mouse_Position = (Mouse::getPosition(window)) / 64; // window is a sf::Window
        // get the local mouse position (relative to a window)
        if (button_flag == RED)                    //red
        {
            RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'R';
            std::cout << "RED\n";
            globalcounter++;
            std::cout << " Turn - " << globalcounter << "\n";
        }
        else
        {
            RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'B';
            std::cout << "BLACK\n";
            globalcounter++;
            std::cout << " Turn - " << globalcounter << "\n";
        }
        button_delay = 0;
        button_flag = !button_flag;
        WeightCalculate();

        std::cout << "mouse activity\n";

        changes_flag = true;
    }
}
button_delay++;
if (button_delay > 100000) button_delay = 0;

}
*/