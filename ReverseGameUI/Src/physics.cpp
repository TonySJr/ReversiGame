#include "pch.h"
#include "FigureNames.h"
#include "functions.h"
#include "figure.h"



extern Vector2i mouse_Position;
//extern char button_flag;
extern bool button_flag;
bool board_end_flag = false;
bool end_flag = false;
Vector2i UP(0, -1), UPLEFT(-1, -1), LEFT(-1, 0), LEFTDOWN(-1, 1), DOWN(0, 1), RIGHTDOWN(1, 1), RIGHT(1, 0), UPRIGHT(1, -1);
Vector2i* array_Dir[] = { &UP, &UPLEFT, &LEFT, &LEFTDOWN, &DOWN, &RIGHTDOWN, &RIGHT, &UPRIGHT };
void Physics()
{
    // место последней монетки
    Vector2i Position = mouse_Position;
    // массив векторов клеток, которые необходимо перевернуть
    Vector2i coins_array[8];
    if (button_flag == false)    //Black coin
    {
        for (int i = 0; i < (sizeof(array_Dir) / sizeof(array_Dir[0])); i++)
        {
            Vector2i tempVector(0, 0);
            int j = 0;
            board_end_flag = false;
            end_flag = false;
            int coin_count = 0;
            //  провер€ем каждое направление пока не дойдем до конца доски или 
            //  не найдем свою монетку после монетки противника 
            while ((board_end_flag == false) && (end_flag == false) && (j < 8))
            {
                // check all directions to the opponentТs coin
                Vector2i vector_safe = array_walls((Position.x + (*array_Dir[i]).x + tempVector.x), (Position.y + (*array_Dir[i]).y) + tempVector.y);
                if ((RevBoard[vector_safe.x + vector_safe.y * ROWS] == 'R') && (board_end_flag == false))
                {
                    tempVector += (*array_Dir[i]);
                    coins_array[j] = Vector2i(vector_safe.x, vector_safe.y);
                    coin_count++;
                }
                else if ((RevBoard[vector_safe.x + vector_safe.y * ROWS] == 'B') && (board_end_flag == false))
                {
                    //  если на пути проверки нашли свою монетку
                    //  закрашиваем все клетки между.
                    for (int k = 0; k < coin_count; k++)
                    {
                        RevBoard[coins_array[k].x + (coins_array[k].y) * ROWS] = 'B';
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
            coin_count = 0;
        }
    }
    else                //red coin
    {
        for (int i = 0; i < (sizeof(array_Dir) / sizeof(array_Dir[0])); i++)
        {
            Vector2i tempVector(0, 0);
            int j = 0;
            board_end_flag = false;
            end_flag = false;
            int coin_count = 0;
            //  провер€ем каждое направление пока не дойдем до конца доски или 
            //  не найдем свою монетку после монетки противника 
            while ((board_end_flag == false) && (end_flag == false) && (j < 8))
            {
                // check all directions to the opponentТs coin
                Vector2i vector_safe = array_walls((Position.x + (*array_Dir[i]).x + tempVector.x), (Position.y + (*array_Dir[i]).y) + tempVector.y);
                if ((RevBoard[vector_safe.x + vector_safe.y * ROWS] == 'B') && (board_end_flag == false))
                {
                    tempVector += (*array_Dir[i]);
                    coins_array[j] = Vector2i(vector_safe.x, vector_safe.y);
                    coin_count++;
                }
                else if ((RevBoard[vector_safe.x + vector_safe.y * ROWS] == 'R') && (board_end_flag == false))
                {
                    //  если на пути проверки нашли свою монетку
                    //  закрашиваем все клетки между.
                    for (int k = 0; k < coin_count; k++)
                    {
                        RevBoard[coins_array[k].x + (coins_array[k].y) * ROWS] = 'R';
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
            coin_count = 0;
        }

    }
}


void Swap(char* arr, int x1, int y1, int x2, int y2)
{
    std::cout << x1 << " " << y1 << std::endl;
    std::cout << x2 << " " << y2 << std::endl;
    //char temp = ChessBoard[y1][x1];
    //ChessBoard[y1][x1] = ChessBoard[y2][x2];
    //ChessBoard[y2][x2] = temp;
    arr[x2 + y2 * ROWS] = arr[x1 + y1 * ROWS];
    arr[x1 + y1 * ROWS] = '0';
}
Vector2i array_walls(int x, int y)
{
    Vector2i result(x, y);
    //  если вышли за границы массива
    //  поднимаем флаг и возвращаем нулевой вектор
    if ((x > COLUMS) || (y > ROWS) || (x < 0) || (y < 0))
    {
        board_end_flag = true;
        result.x = 0;
        result.y = 0;
    }
    return result;
}

