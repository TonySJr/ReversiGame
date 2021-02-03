#include "pch.h"
#include "UI.h"
#include "FigureNames.h"
#include "Board.h"
#include "AI.h"


void UI::mouseShedule(RenderWindow& window)
{
    std::chrono::duration<double> elapsed_seconds = m_end - m_start;
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        m_start = std::chrono::steady_clock::now();
        if (elapsed_seconds.count() > 0.5f)
        {

            m_last_coin = (Mouse::getPosition(window)) / 64; // window is a sf::Window
            std::cout << "mouse activity\n" << Mouse::getPosition(window).x << Mouse::getPosition(window).y;
            // get the local mouse position (relative to a window)
            // red human turn
            // copy last board
            for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
            {
                ReversiBoard.p_LastBoard[i] = ReversiBoard.getBoardCellFigure(i);
            }
            ReversiBoard.setBoardCell(m_last_coin.x + m_last_coin.y * ROWS, 'R');
            //RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'R';
            std::cout << "\tRED - Human\n";
            globalcounter++;
            std::cout << "\tTurn -\t" << globalcounter << "\n";

            ReversiBoard.Physics(User1.last_coin());
            changes_flag = true;
            ReversiBoard.p_button_flag = 'B';
            Jarvis.AI_turn_flag = true;
            std::cout << "\tAI_turn_flag - " << Jarvis.AI_turn_flag << "\n";
        }
    }
    m_end = std::chrono::steady_clock::now();
}
void UI::mouseShedule2(RenderWindow& window,int x, int y)
{
    std::cout << "mouse activity\n";
    m_last_coin.x = x / 64; // window is a sf::Window
    m_last_coin.y = y / 64; // window is a sf::Window
    // get the local mouse position (relative to a window)
    // red human turn
    // copy last board
    for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
    {
        ReversiBoard.p_LastBoard[i] = ReversiBoard.getBoardCellFigure(i);
    }
    ReversiBoard.setBoardCell(m_last_coin.x + m_last_coin.y * ROWS, 'R');
    //RevBoard[mouse_Position.x + mouse_Position.y * ROWS] = 'R';
    std::cout << "\tRED - Human\n";
    globalcounter++;
    std::cout << "\tTurn -\t" << globalcounter << "\n";

    ReversiBoard.Physics(User1.last_coin());
    changes_flag = true;
    ReversiBoard.p_button_flag = 'B';
    Jarvis.AI_turn_flag = true;
    std::cout << "\tAI_turn_flag - " << Jarvis.AI_turn_flag << "\n";

}
Vector2i& UI::last_coin()
{
    return m_last_coin;
}
