#pragma once
#include "pch.h"
#include "FigureNames.h"

/*
    Класс Искусственного интеллекта 


*/

class AI
{
public:
    AI()
    {

    }

    void AI_turn(std::vector<int>& turns);
    int GetCellWeight(int cell);
    void addCelltoCheck(int cell);

    void AIWeightBoardfill(int value);

    void findPossibleMoves();
    std::vector<int>& getMovesVector();
    void MovesVectorClear();

    int getBestPos();
    bool AI_turn_flag = false;

private:
    Vector2i array_walls(int x, int y);
    void WeightCalculate();
    void CopyBoardAI();
    void Physics();
private:


    int m_best_pos = 0;
    int m_cnt_black_coins = 0;
    Vector2i m_AI_last_coin = Vector2i(0, 0);


    std::array<char, Board_Cells> m_TempBoard = { '0' };    // board to check turns

    std::array<int, Board_Cells> m_AIWeightBoard =    { 5,1,3,2,2,3,1,5,
                                                        1,1,1,1,1,1,1,1,
                                                        3,1,3,2,2,3,1,3,
                                                        2,1,2,1,1,2,1,2,
                                                        2,1,2,1,1,2,1,2,
                                                        3,1,3,2,2,3,1,3,
                                                        1,1,1,1,1,1,1,1,
                                                        5,1,3,2,2,3,1,5 };
    std::vector<int> m_cells_to_check;
    int cnt_black_coins = 0;

    //  Physics stuff
    bool m_AI_board_end_flag = false;

    std::array<Vector2i, 8> m_array_Dir = { sf::Vector2i(0,-1),sf::Vector2i(-1,-1),
    sf::Vector2i(-1,0),sf::Vector2i(-1,1),sf::Vector2i(0,1),sf::Vector2i(1,1),
    sf::Vector2i(1,0),sf::Vector2i(1,-1) };
};