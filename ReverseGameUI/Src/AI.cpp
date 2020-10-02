#include "pch.h"
#include "FigureNames.h"
#include "AI.h"
#include "functions.h"

std::array<int, Board_Cells> AIWeightBoard = { 0 };
std::array<char, Board_Cells> TempBoard = { 0 };    // board to check turns

std::vector<int> cells_to_check;
extern struct AI Jarvis;
extern char button_flag;
int cnt_black_coins = 0;
void WeightCalculate(std::array<char,Board_Cells> &board)
{
    cnt_black_coins = 0;
    for (auto& cell : board)
    {
        if (cell == 'B')
        {
            cnt_black_coins++;
        }
    }
    std::cout << "Black coins - \t" << cnt_black_coins << "\t";
}
void CopyBoardAI(std::array<char, Board_Cells> &board)
{
    for(int i = 0; i < board.size();i++)
        TempBoard[i] = board[i];
}
void AI_turn(std::vector<int> &turns)
{
    Vector2i last_coin;
    Jarvis.best_pos = 0;
    for (int turn = 0; turn < turns.size(); turn++)
    {
        CopyBoardAI(RevBoard);
        TempBoard[turns[turn]] = 'B';
        int y = turns[turn] / 8;
        int x = turns[turn] - y * 8;
        last_coin.y = y;
        last_coin.x = x;
        Physics(TempBoard,last_coin);
        for (int i = 0; i < TempBoard.size(); i++)
        {
            if ((i % 8) == 0)
            {
                std::cout << std::endl;
            }
            std::cout << TempBoard[i];
        }
        std::cout << "\nafter Temp Physics\n";
        WeightCalculate(TempBoard);std::cout << "last_coin = " << last_coin.x << " , " << last_coin.y << " Cell = " << turns[turn] << std::endl;
        if (cnt_black_coins > Jarvis.cnt_black_coins)
        {
            Jarvis.cnt_black_coins = cnt_black_coins;
            Jarvis.best_pos = turns[turn];
        }
    }
    // AI make move
    RevBoard[Jarvis.best_pos] = 'B';
    AIWeightBoard[Jarvis.best_pos] = 255;
    std::cout << "\n before Revboard Physics\n";
    for (int i = 0; i < RevBoard.size(); i++)
    {
        if ((i % 8) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << RevBoard[i];
    }
    last_coin.y = Jarvis.best_pos / 8;
    last_coin.x = Jarvis.best_pos - (last_coin.y * 8);
    Physics(RevBoard, last_coin);
    std::cout << "\n last coin \t" << last_coin.x << last_coin.y << std::endl;
    for (int i = 0; i < RevBoard.size(); i++)
    {
        if ((i % 8) == 0)
        {
            std::cout << std::endl;
        }
        std::cout << RevBoard[i];
    }
    std::cout << "\n after Revboard Physics\n";
    globalcounter++;
    std::cout << "\t---AI make Turn---\t\n";
    Jarvis.AI_turn_flag = false;
    button_flag = 'R';
}