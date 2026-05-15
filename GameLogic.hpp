#ifndef GAMELOGIC_HPP_INCLUDED
#define GAMELOGIC_HPP_INCLUDED
#include <vector>


class Move {
protected:
    int _r,_c,_g;
public:
    Move(int r,int c, int g);
    bool isMovesLeft(const std::vector<std::vector<int>>& grid);
    void findBestMove(std::vector<std::vector<int>> _grid);
    int evaluate(std::vector<std::vector<int>> _grid);
    int minimax(std::vector<std::vector<int>> _grid, bool isMax);
};

#endif // GAMELOGIC_HPP_INCLUDED
