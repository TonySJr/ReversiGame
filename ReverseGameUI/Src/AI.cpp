#include "pch.h"
#include "FigureNames.h"


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
            AIWeightBoard[i]++;
        }
        else if (RevBoard[i] == 'B')
        {
            cells_to_check.at(i) = 0;
            AIWeightBoard[i]--;
        }
        cnt++;
    }
    /*
    for (int i = 0; i < Board_Cells; i++)
    {
       AIWeightBoard[i] = AIWeightBoard[i];
    
    }
    */
}