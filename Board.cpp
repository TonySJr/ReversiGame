#include "pch.h"
#include "figure.h"
#include "FigureNames.h"
#include "UI.h"
#include "Board.h"
#include "AI.h"



void Board::setBoardCell(int& cell, char& color)
{
    p_Board[cell] = color;
}
void Board::setBoardCell(int cell, char color)
{
    p_Board[cell] = color;
}
char Board::getBoardCellFigure(int cell)
{
	return p_Board[cell];
}
int Board::getBoardSize()
{
    return p_Board.size();
}
Vector2i Board::array_walls(int x, int y)
{
    Vector2i result(x, y);
    //  если вышли за границы массива
    //  поднимаем флаг и возвращаем нулевой вектор
    if ((x > (COLUMS-1)) || (y > (ROWS-1)) || (x < 0) || (y < 0))
    {
        m_board_end_flag = true;
        result.x = 0;
        result.y = 0;
    }
    return result;
}
void Board::Physics(sf::Vector2i& cell_pos)
{
    // место последней монетки
    Vector2i Position = cell_pos;
    // массив векторов клеток, которые необходимо перевернуть
    Vector2i coins_array[8];
    //создать вектор дл€ клеток необходимых дл€ закрашивани€
    std::vector<Vector2i> Cells_to_revert;
    if (p_button_flag == 'B')    //Black coin
    {
        //  провер€ем все направлени€ по очереди из массива направлений
        for (int i = 0; i < m_array_Dir.size(); i++)
        {
            Vector2i tempVector(0, 0);
            int j = 0;
            m_board_end_flag = false;
            bool end_flag = false;
            int coin_count = 0;
            //  провер€ем каждое направление пока не дойдем до конца доски или 
            //  не найдем свою монетку после монетки противника 
            while ((m_board_end_flag == false) && (end_flag == false) && (j < 8))
            {
                // check all directions to the opponentТs coin
                Vector2i vector_safe = array_walls((Position.x + (m_array_Dir[i]).x + tempVector.x), (Position.y + (m_array_Dir[i]).y) + tempVector.y);
                if ((p_Board[vector_safe.x + vector_safe.y * ROWS] == 'R') && (m_board_end_flag == false))
                {
                    tempVector += (m_array_Dir[i]);
                    coins_array[j] = Vector2i(vector_safe.x, vector_safe.y);
                    coin_count++;
                }
                else if ((p_Board[vector_safe.x + vector_safe.y * ROWS] == 'B') && (m_board_end_flag == false))
                {
                    //  если на пути проверки нашли свою монетку
                    //  завершаем цикл записыванием клеток в вектор дл€ переворота

                    for (int k = 0; k < coin_count; k++)
                    {
                        Cells_to_revert.push_back(coins_array[k]);
                        coins_array[k] = Vector2i(0, 0);
                    }

                    //  завершаем направление
                    end_flag = true;
                }
                else
                {

                    //  если не R то скипаем направление
                    end_flag = true;
                }
                j++;
            }
            for (int k = 0; k < coin_count; k++)
            {
                coins_array[k] = Vector2i(0, 0);
            }
            coin_count = 0;
        }
        //закрасить все клетки своим цветом
        for (Vector2i it : Cells_to_revert)
        {
            p_Board[(int)it.x + (int)(it.y) * ROWS] = 'B';
        }
        Cells_to_revert.clear();
    }
    else                //red coin
    {
        for (int i = 0; i < m_array_Dir.size(); i++)
        {
            Vector2i tempVector(0, 0);
            int j = 0;
            m_board_end_flag = false;
            bool end_flag = false;
            int coin_count = 0;
            //  провер€ем каждое направление пока не дойдем до конца доски или 
            //  не найдем свою монетку после монетки противника 
            while ((m_board_end_flag == false) && (end_flag == false) && (j < 8))
            {
                // check all directions to the opponentТs coin
                Vector2i vector_safe = array_walls((Position.x + (m_array_Dir[i]).x + tempVector.x), (Position.y + (m_array_Dir[i]).y) + tempVector.y);
                if ((p_Board[vector_safe.x + vector_safe.y * ROWS] == 'B') && (m_board_end_flag == false))
                {
                    tempVector += (m_array_Dir[i]);
                    coins_array[j] = Vector2i(vector_safe.x, vector_safe.y);
                    coin_count++;
                }
                else if ((p_Board[vector_safe.x + vector_safe.y * ROWS] == 'R') && (m_board_end_flag == false))
                {
                    //  если на пути проверки нашли свою монетку
                    //  закрашиваем все клетки между.

                    for (int k = 0; k < coin_count; k++)
                    {
                        Cells_to_revert.push_back(coins_array[k]);
                        coins_array[k] = Vector2i(0, 0);
                    }

                    //  завершаем направление
                    end_flag = true;
                }
                else
                {
                    //  если не R то скипаем направление
                    end_flag = true;
                }
                j++;
            }
            for (int k = 0; k < coin_count; k++)
            {
                coins_array[k] = Vector2i(0, 0);
            }
            coin_count = 0;
        }
        //закрасить все клетки своим цветом
        for (Vector2i it : Cells_to_revert)
        {
            p_Board[(int)it.x + (int)(it.y) * ROWS] = 'R';
        }
        Cells_to_revert.clear();
    }
    
}
void Board::DrawBoard(class RenderWindow& window)
{
    window.clear(Color::Black);
    window.draw(BoardSprite1.spritefigure());
    window.draw(BoardSprite2.spritefigure());
    std::string s;
    text.setFillColor(sf::Color::Black);
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLUMS; x++)
        {
            switch (p_Board[x + y * ROWS])
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
            // draw last board ----------



            switch (p_LastBoard[x + y * ROWS])
            {
            case 'B':
            {
                BlackCoin.setPos((float)x + 8.08f, (float)y);
                window.draw(BlackCoin.spritefigure());
                break;
            }
            case 'R':
            {
                RedCoin.setPos((float)x + 8.08f, (float)y);
                window.draw(RedCoin.spritefigure());
                break;
            }
            default:
                break;
            }

            s = std::to_string(x + y * ROWS);
            text.setString(s);
            text.setPosition(textZeropos + Vector2f(64 * x, 64 * y));
            window.draw(text);


        }
    }

    //  draw user coin
    text.setFillColor(sf::Color::Green);
    s = std::to_string(User1.last_coin().x + (User1.last_coin().y * 8));
    text.setString(s);
    text.setPosition(textZeropos + Vector2f(64 * User1.last_coin().x, 64 * User1.last_coin().y));
    window.draw(text);
    //  draw last coid
    text.setFillColor(sf::Color::Red);
    s = std::to_string(Jarvis.getBestPos());
    text.setString(s);
    int y1 = Jarvis.getBestPos() / 8;
    int x1 = Jarvis.getBestPos() - (y1 * 8);
    text.setPosition(textZeropos + Vector2f(64 * x1, 64 * y1));
    window.draw(text);

    //  draw possible ai moves
    text.setFillColor(sf::Color::Blue);
    for (auto cell : Jarvis.getMovesVector())
    {

        s = std::to_string(cell);
        text.setString(s);
        int y2 = cell / 8;
        int x2 = cell - (y2 * 8);
        text.setPosition(textZeropos + Vector2f(64 * x2, 64 * y2));
        ColoredSquare.ColorChange(0,255,0,128);
        ColoredSquare.setPos((float)x2, (float)y2);
        window.draw(ColoredSquare.spritefigure());
        window.draw(text);
    }
    // endlast coin
    window.display();
    changes_flag = false;
}

