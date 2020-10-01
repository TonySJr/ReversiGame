#include "pch.h"
#include "FigureNames.h"
#include "AI.h"

std::array<int, Board_Cells> AIWeightBoard = { 0 };
std::array<char, Board_Cells> TempBoard = { 0 };    // board to check turns

std::vector<int> cells_to_check;
int cnt_black_coins = 0;
void WeightCalculate(std::array<char,Board_Cells> board)
{
    cnt_black_coins = 0;
    for (auto& cell : board)
    {
        if (cell == 'B')
        {
            cnt_black_coins++;
        }
    }
    std::cout << "Black coins - \t" << cnt_black_coins << std::endl;
}

void AI_turn(std::array<char,Board_Cells> &RevBoard)
{
    std::vector<int> test;
    //  walk through all cells and fill the vector
    for (int it = 0;it < RevBoard.size()-1;it++)
    {
        if (RevBoard[it] == 'R')
        {
            std::cout << "it -" << it << std::endl;
            test.push_back(it);
        }

    }
    // debug print console
    for(auto i : test)
    {
        std::cout << i << std::endl;

    }
    
}