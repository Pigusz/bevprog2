#include "GameLogic.hpp"
#include <vector>

using namespace std;

Move::Move(int r, int c, int g){
_r = r;
_c = c;
_g = g;
}

int Move::evaluate(vector<vector<int>> _grid) {

}

bool Move::isMovesLeft(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < _g; i++) {
        for (int j = 0; j < _g; j++) {
            if (grid[i][j] == 0)
                return true;
        }
    }
    return false;
}

int Move::minimax(vector<vector<int>> _grid, bool isMax) {
    int score = evaluate(_grid);
    if (score == 10 || score == -10) return score;
    if (!isMovesLeft(_grid)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i=0; i<_g; i++) {
            for (int j=0; j<_g; j++) {
                if (_grid[i][j] == 0) {
                    _grid[i][j] = _g-1;
                    best = max(best, minimax(_grid, !isMax));
                    _grid[i][j] = 0;
                }
            }
        }
        return best;
    } else {
    }
}

void Move::findBestMove(vector<vector<int>> _grid) {
    int bestVal = -1000;
    _r=-1;
    _c=-1;

    for (int i = 0; i < _g; i++) {
        for (int j = 0; j < _g; j++) {
            if (_grid[i][j] == -1) {
                _grid[i][j] = 0;
                int moveVal = minimax(_grid, false);
                _grid[i][j] = -1;

                if (moveVal > bestVal) {
                    _r=i;
                    _c=j;
                    bestVal = moveVal;
                }
            }
        }
    }
}
