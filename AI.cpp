#include "pch.h"
#include "FigureNames.h"
#include "AI.h"
#include "functions.h"
#include "Board.h"
#include "UI.h"

/*
std::array<int, Board_Cells> AIWeightBoard = { 0 };
std::array<char, Board_Cells> TempBoard = { 0 };    // board to check turns
std::vector<int> cells_to_check;
extern struct AI Jarvis;
extern char button_flag;
*/
int cnt_black_coins = 0;


Vector2i AI::array_walls(int x, int y)
{
    Vector2i result(x, y);
    //  если вышли за границы массива
    //  поднимаем флаг и возвращаем нулевой вектор
    if ((x > COLUMS-1) || (y > ROWS-1) || (x < 0) || (y < 0))
    {
        m_AI_board_end_flag = true;
        result.x = 0;
        result.y = 0;
    }
    return result;
}
void AI::Physics()
{
    // место последней монетки
    Vector2i Position = m_AI_last_coin;
    // массив векторов клеток, которые необходимо перевернуть
    Vector2i coins_array[8];
    //создать вектор дл€ клеток необходимых дл€ закрашивани€
    std::vector<Vector2i> Cells_to_revert;

    //  провер€ем все направлени€ по очереди из массива направлений
    for (int i = 0; i < m_array_Dir.size(); i++)
    {
        Vector2i tempVector(0, 0);
        int j = 0;
        m_AI_board_end_flag = false;
        bool end_flag = false;
        int coin_count = 0;
        //  провер€ем каждое направление пока не дойдем до конца доски или 
        //  не найдем свою монетку после монетки противника 
        while ((m_AI_board_end_flag == false) && (end_flag == false) && (j < 8))
        {
            // check all directions to the opponentТs coin
            Vector2i vector_safe = array_walls((Position.x + (m_array_Dir[i]).x + tempVector.x), (Position.y + (m_array_Dir[i]).y) + tempVector.y);
            if ((m_TempBoard[vector_safe.x + vector_safe.y * ROWS] == 'R') && (m_AI_board_end_flag == false))
            {
                tempVector += (m_array_Dir[i]);
                coins_array[j] = Vector2i(vector_safe.x, vector_safe.y);
                coin_count++;
            }
            else if ((m_TempBoard[vector_safe.x + vector_safe.y * ROWS] == 'B') && (m_AI_board_end_flag == false))
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
        m_TempBoard[(int)it.x + (int)(it.y) * ROWS] = 'B';
    }
    Cells_to_revert.clear();
    
}

void AI::WeightCalculate()
{
    m_cnt_black_coins = 0;
    for (int cell = 0; cell < m_TempBoard.size();cell++)
    {
        if (m_TempBoard[cell] == 'B')
        {
            m_cnt_black_coins+= m_AIWeightBoard[cell];
        }
    }
    std::cout << "Black coins - \t" << m_cnt_black_coins << "\t" << m_AIWeightBoard[0];
}
void AI::CopyBoardAI()
{
    for(int i = 0; i < ReversiBoard.getBoardSize(); i++)
        m_TempBoard[i] = ReversiBoard.getBoardCellFigure(i);
}
void AI::AI_turn(std::vector<int> &turns)
{
    cnt_black_coins = 0;
    for (int turn = 0; turn < turns.size(); turn++)
    {
        CopyBoardAI();
        m_TempBoard[turns[turn]] = 'B';
        int y = turns[turn] / 8;
        int x = turns[turn] - y * 8;
        m_AI_last_coin.y = y;
        m_AI_last_coin.x = x;

        Jarvis.Physics();

        for (int i = 0; i < m_TempBoard.size(); i++)
        {
            if ((i % 8) == 0)
            {
                std::cout << std::endl;
            }
            std::cout << m_TempBoard[i];
        }
        std::cout << "\nafter Temp Physics\n";
        WeightCalculate();std::cout << "last_coin = " << m_AI_last_coin.x << " , " << m_AI_last_coin.y << " Cell = " << turns[turn] << std::endl;
        if (m_cnt_black_coins > cnt_black_coins)
        {
            cnt_black_coins = m_cnt_black_coins;
            m_best_pos = turns[turn];
        }
    }
    // AI make move
    ReversiBoard.setBoardCell(m_best_pos,'B');
    //m_AIWeightBoard[m_best_pos] = 255;
    std::cout << "\n before Revboard Physics\n";
    for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
    {
        if ((i % 8) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << ReversiBoard.getBoardCellFigure(i);
    }
    m_AI_last_coin.y = m_best_pos / 8;
    m_AI_last_coin.x = m_best_pos - (m_AI_last_coin.y * 8);
    //  Not the best ---------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!
    ReversiBoard.setBoardCell(m_best_pos, 'B');
    ReversiBoard.Physics(m_AI_last_coin);
    //  __________________________________________________________________________!!!!!
    std::cout << "\n last coin \t" << m_AI_last_coin.x << m_AI_last_coin.y << std::endl;
    for (int i = 0; i < ReversiBoard.getBoardSize(); i++)
    {
        if ((i % 8) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << ReversiBoard.getBoardCellFigure(i);
    }
    std::cout << "\n after Revboard Physics\n";
    globalcounter++;
    std::cout << "\t---AI make Turn---\t\n";
    AI_turn_flag = false;
    ReversiBoard.p_button_flag = 'R';
}

int AI::GetCellWeight(int cell)
{
    return m_AIWeightBoard[cell];
}

void AI::addCelltoCheck(int cell)
{
    m_cells_to_check.push_back(cell);
}

std::vector<int>& AI::getMovesVector()
{
    return m_cells_to_check;
}

void AI::MovesVectorClear()
{
    m_cells_to_check.clear();
}

void AI::AIWeightBoardfill(int value)
{
    m_AIWeightBoard.fill(value);
}

void AI::findPossibleMoves()
{
    //  check all cells. if find 'b' check for possible moves
    for (int cell = 0; cell < ReversiBoard.getBoardSize();cell++)
    {
        if (ReversiBoard.getBoardCellFigure(cell) == 'B')
        {
            // место последней монетки
            Vector2i Position;
            Position.y = cell / 8;
            Position.x = cell - (Position.y * 8);
            //  провер€ем все направлени€ по очереди из массива направлений
            for (int i = 0; i < m_array_Dir.size(); i++)
            {
                Vector2i tempVector(0, 0);
                int j = 0;
                m_AI_board_end_flag = false;
                bool end_flag = false;
                bool find_red_coin = false;
                //  провер€ем каждое направление пока не дойдем до конца доски или 
                //  не найдем свою монетку после монетки противника 
                while ((m_AI_board_end_flag == false) && (end_flag == false) && (j < 8))
                {
                    // check all directions to the opponentТs coin
                    Vector2i vector_safe = array_walls((Position.x + (m_array_Dir[i]).x + tempVector.x), (Position.y + (m_array_Dir[i]).y) + tempVector.y);
                    if ((ReversiBoard.p_Board[vector_safe.x + vector_safe.y * ROWS] == 'R') && (m_AI_board_end_flag == false))
                    {
                        tempVector += (m_array_Dir[i]);
                        find_red_coin = true;
                    }
                    else if ((ReversiBoard.p_Board[vector_safe.x + vector_safe.y * ROWS] == '0') && (m_AI_board_end_flag == false) && (find_red_coin == true))
                    {
                        //  если на пути проверки нашли пустое место
                        //  завершаем цикл записыванием клеток в вектор дл€ переворота
                        m_cells_to_check.push_back(vector_safe.x + vector_safe.y * ROWS);
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
            }
        }
    }
}

int AI::getBestPos()
{
    return m_best_pos;
}
