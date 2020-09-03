#include "pch.h"
#include "FigureNames.h"

int AIWeightBoard[Board_Cells] = {0};

void WeightCalculate()
{
    for (int i = 0; i < Board_Cells; i++)
    {
        AIWeightBoard[i] = 0;
        if (RevBoard[i] == 'R')
        {
            AIWeightBoard[i]++;
        }
        else if (RevBoard[i] == 'B')
        {
            AIWeightBoard[i]--;
        }
    }
    /*
    for (int i = 0; i < Board_Cells; i++)
    {
       AIWeightBoard[i] = AIWeightBoard[i];
    
    }
    */
}