#include <iostream>
#include <limits>
using namespace std;

const size_t N = 3;
const unsigned PLAYERS_COUNT = 2;
const unsigned LINE_LENGTH = 3; 
const char EMPTY_FIELD = ' ';

void init(char field[][N], char ch) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            field[i][j] = ch;
    }
}

void print(const char field[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << "[" << field[i][j] << "]";
        cout << endl;
    }
}

bool areValidIndices(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

void input(char field[][N], int& x, int& y, int currentPlayer) {
    cout << "Player " << (char)('A' + currentPlayer) << ", enter your move (row and column): ";

    // Input validation loop
    while (!(cin >> x >> y) || !areValidIndices(x, y) || field[x][y] != EMPTY_FIELD) {
        cin.clear();                           // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid move. Try again: ";
    }
}

int getConsecutiveDirection(const char field[][N], int row, int coll, int rowMove, int collMove) {
    char ch = field[row][coll];

    int count = 0;
    while (areValidIndices(row, coll) && field[row][coll] == ch) {
        count++;
        row += rowMove;
        coll += collMove;
    }
    return count;
}

unsigned getConsecutiveOnLine(const char field[][N], int row, int coll, int rowMove, int collMove) {
    return getConsecutiveDirection(field, row, coll, rowMove, collMove) +
        getConsecutiveDirection(field, row, coll, -rowMove, -collMove) - 1; //because we count the starting point twice.
}

bool isWinningMove(const char field[][N], int row, int coll) {
    return getConsecutiveOnLine(field, row, coll, 0, 1) >= LINE_LENGTH || //horizontal
        getConsecutiveOnLine(field, row, coll, 1, 0) >= LINE_LENGTH || //vertical
        getConsecutiveOnLine(field, row, coll, 1, 1) >= LINE_LENGTH || //main diagonal
        getConsecutiveOnLine(field, row, coll, 1, -1) >= LINE_LENGTH;   //anti diagonal
}

int main() {
    char field[N][N];
    init(field, EMPTY_FIELD);
    print(field);

    bool haveWinner = false;
    int currentPlayer = 0;

    for (int move = 0; move < N * N && !haveWinner; ++move) {
        int row, col;
        input(field, row, col, currentPlayer);
        field[row][col] = 'A' + currentPlayer;
        print(field);

        haveWinner = isWinningMove(field, row, col);

        if (!haveWinner) {
            ++currentPlayer;
            currentPlayer %= PLAYERS_COUNT;
        }
    }

    if (haveWinner)
        cout << "Player " << (char)('A' + currentPlayer) << " wins!" << endl;
    else
        cout << "Draw!" << endl;

    return 0;
}