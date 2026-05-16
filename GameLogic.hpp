#ifndef GAMELOGIC_HPP_INCLUDED
#define GAMELOGIC_HPP_INCLUDED

#include <vector>

class GameLogic {
public:
    int bestRow, bestCol;
    int _g;

    GameLogic(int g);
    bool isMovesLeft(const std::vector<std::vector<int>>& grid);
    int evaluate(const std::vector<std::vector<int>>& grid);
    int minimax(std::vector<std::vector<int>>& grid, int depth, bool isMax, int alpha, int beta);
    void findBestMove(std::vector<std::vector<int>> grid);
    bool hasNeighbor(const std::vector<std::vector<int>>& grid, int r, int c);
};

#endif // GAMELOGIC_HPP_INCLUDED
