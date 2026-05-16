#include "GameLogic.hpp"
#include <algorithm>

using namespace std;

GameLogic::GameLogic(int g) : _g(g), bestRow(-1), bestCol(-1) {}

bool GameLogic::isMovesLeft(const vector<vector<int>>& grid) {
    for (int i = 0; i < _g; i++) {
        for (int j = 0; j < _g; j++) {
            if (grid[i][j] == 0) return true;
        }
    }
    return false;
}

// Check for 5-in-a-row
int GameLogic::evaluate(const vector<vector<int>>& grid) {
    int dx[] = {1, 0, 1, 1};
    int dy[] = {0, 1, 1, -1};

    for (int r = 0; r < _g; r++) {
        for (int c = 0; c < _g; c++) {
            if (grid[r][c] == 0) continue;
            int player = grid[r][c];

            for (int dir = 0; dir < 4; dir++) {
                int count = 0;
                for (int step = 0; step < 5; step++) {
                    int nr = r + step * dx[dir];
                    int nc = c + step * dy[dir];
                    if (nr >= 0 && nr < _g && nc >= 0 && nc < _g && grid[nr][nc] == player) {
                        count++;
                    } else {
                        break;
                    }
                }
                if (count >= 5) {
                    return (player == 2) ? 1000 : -1000; // 2 is AI, 1 is Player
                }
            }
        }
    }
    return 0;
}

// Pruning strategy: Only test moves close to existing pieces
bool GameLogic::hasNeighbor(const vector<vector<int>>& grid, int r, int c) {
    for (int i = max(0, r - 2); i <= min(_g - 1, r + 2); ++i) {
        for (int j = max(0, c - 2); j <= min(_g - 1, c + 2); ++j) {
            if (grid[i][j] != 0) return true;
        }
    }
    return false;
}

// Alpha-Beta Minimax
int GameLogic::minimax(vector<vector<int>>& grid, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(grid);
    if (score == 1000 || score == -1000) return score;
    if (depth == 0 || !isMovesLeft(grid)) return 0;

    if (isMax) {
        int best = -10000;
        for (int i = 0; i < _g; i++) {
            for (int j = 0; j < _g; j++) {
                if (grid[i][j] == 0 && hasNeighbor(grid, i, j)) {
                    grid[i][j] = 2; // AI
                    best = max(best, minimax(grid, depth - 1, !isMax, alpha, beta));
                    grid[i][j] = 0;
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best; // Prune
                }
            }
        }
        return (best == -10000) ? 0 : best;
    } else {
        int best = 10000;
        for (int i = 0; i < _g; i++) {
            for (int j = 0; j < _g; j++) {
                if (grid[i][j] == 0 && hasNeighbor(grid, i, j)) {
                    grid[i][j] = 1; // Player
                    best = min(best, minimax(grid, depth - 1, !isMax, alpha, beta));
                    grid[i][j] = 0;
                    beta = min(beta, best);
                    if (beta <= alpha) return best; // Prune
                }
            }
        }
        return (best == 10000) ? 0 : best;
    }
}

void GameLogic::findBestMove(vector<vector<int>> grid) {
    int bestVal = -10000;
    bestRow = -1;
    bestCol = -1;

    // First move optimization: Take the middle
    bool isEmpty = true;
    for (int r = 0; r < _g; r++) {
        for (int c = 0; c < _g; c++) {
            if (grid[r][c] != 0) { isEmpty = false; break; }
        }
    }
    if (isEmpty) {
        bestRow = _g / 2; bestCol = _g / 2; return;
    }

    for (int i = 0; i < _g; i++) {
        for (int j = 0; j < _g; j++) {
            if (grid[i][j] == 0 && hasNeighbor(grid, i, j)) {
                grid[i][j] = 2;
                int moveVal = minimax(grid, 2, false, -10000, 10000); // Depth 2
                grid[i][j] = 0;

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    // Fallback if no neighbor cell is found (safeguard)
    if (bestRow == -1) {
        for (int i = 0; i < _g; i++) {
            for (int j = 0; j < _g; j++) {
                if (grid[i][j] == 0) {
                    bestRow = i; bestCol = j; return;
                }
            }
        }
    }
}
