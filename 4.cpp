#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

constexpr int WIN_MASKS[] = {
    0b111000000, 0b000111000, 0b000000111,
    0b100100100, 0b010010010, 0b001001001,
    0b100010001, 0b001010100
};

bool won(const vector<int>& b, int player) {
    int mask = 0;
    for (int i = 0; i < 9; i++)
        if (b[i] == player)
            mask |= (1 << (8 - i));

    for (int w : WIN_MASKS)
        if ((mask & w) == w) return true;

    return false;
}

bool full(const vector<int>& b) {
    return all_of(b.begin(), b.end(), [](int v) { return v != 0; });
}

void draw(const vector<int>& b) {
    cout << "\033[2J\033[1;1H";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cout << "|";
            int v = b[y * 3 + x];
            cout << (v == 0 ? " " : (v == 1 ? "X" : "O"));
        }
        cout << "|\n";
    }
}

int minimax(vector<int>& b, bool aiTurn) {
    if (won(b, 2)) return 10;
    if (won(b, 1)) return -10;
    if (full(b)) return 0;

    int best = aiTurn ? -1000 : 1000;

    for (int i = 0; i < 9; i++) {
        if (b[i] == 0) {
            b[i] = aiTurn ? 2 : 1;
            int score = minimax(b, !aiTurn);
            b[i] = 0;

            best = aiTurn ? max(best, score)
                          : min(best, score);
        }
    }
    return best;
}

int bestMinimaxMove(vector<int> b) {
    int bestScore = -1000;
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (b[i] == 0) {
            b[i] = 2;
            int score = minimax(b, false);
            b[i] = 0;

            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int aiMove(vector<int> b, int difficulty) {
    if (difficulty == 10)
        return bestMinimaxMove(b);

    int smartChance = difficulty * 10;

    if (rand() % 100 < smartChance) {
        // win
        for (int i = 0; i < 9; i++) {
            if (b[i] == 0) {
                b[i] = 2;
                if (won(b, 2)) return i;
                b[i] = 0;
            }
        }

        // block
        if (difficulty >= 3) {
            for (int i = 0; i < 9; i++) {
                if (b[i] == 0) {
                    b[i] = 1;
                    if (won(b, 1)) return i;
                    b[i] = 0;
                }
            }
        }

        // center
        if (difficulty >= 5 && b[4] == 0)
            return 4;
    }

    // random
    vector<int> free;
    for (int i = 0; i < 9; i++)
        if (b[i] == 0) free.push_back(i);

    return free[rand() % free.size()];
}

int main() {
    srand((unsigned)time(nullptr));

    vector<int> board(9, 0);

    int difficulty;
    cout << "Choose difficulty (1-10): ";
    cin >> difficulty;
    difficulty = clamp(difficulty, 1, 10);

    while (true) {
        draw(board);

        // player move
        int spot;
        cout << "Your move (1-9): ";
        cin >> spot;
        spot--;

        if (spot < 0 || spot > 8 || board[spot] != 0)
            continue;

        board[spot] = 1;

        if (won(board, 1)) {
            draw(board);
            cout << "You win\n";
            break;
        }

        if (full(board)) {
            draw(board);
            cout << "Draw.\n";
            break;
        }

        // AI move
        int ai = aiMove(board, difficulty);
        board[ai] = 2;

        if (won(board, 2)) {
            draw(board);
            cout << "Computer wins\n";
            break;
        }
    }

    return 0;
}

