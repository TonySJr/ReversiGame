#include "pch.h"
#include "FigureNames.h"
#include "AI.h"

std::array<int, Board_Cells> AIWeightBoard = { 0 };
std::vector<int> cells_to_check(Board_Cells);

void WeightCalculate()
{
    int cnt = 0;
    for (int i = 0; i < Board_Cells; i++)
    {
        AIWeightBoard[i] = 0;
        cells_to_check.at(i) = cnt;
        if (RevBoard[i] == 'R')
        {
            cells_to_check.at(i) = 0;
            AIWeightBoard[i] = 255;
        }
        else if (RevBoard[i] == 'B')
        {
            cells_to_check.at(i) = 0;
            AIWeightBoard[i] = 255;
        }
        cnt++;
    }
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