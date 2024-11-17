#include <iostream>
#include <vector>
#include <map>
#include<chrono>
using namespace std;
using namespace std :: chrono;

vector<vector<bool>> Knight_board;
map<bool, char> mapping = {{true, 'K'}, {false, '-'}};
int COUNT = 0;
int TOTAL_ROWS, TOTAL_COLS;

void display(const vector<vector<bool>>& Knight_board) {
    for (int i = 0; i < TOTAL_ROWS; i++) {
        for (int j = 0; j < TOTAL_COLS; j++) {
            cout << mapping[Knight_board[i][j]] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool can_place(const vector<vector<bool>>& Knight_board, int row, int col) {
    int moves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
    };
    
    for (int i = 0; i < 8; i++) {
        int newRow = row + moves[i][0];
        int newCol = col + moves[i][1];
        
        if (newRow >= 0 && newRow < TOTAL_ROWS && newCol >= 0 && newCol < TOTAL_COLS) {
            if (Knight_board[newRow][newCol]) {
                return false;
            }
        }
    }
    return true;
}

void Nknights(vector<vector<bool>>& Knight_board, int k, int row, int col) {
    if (k == 0) {
        cout << "Solution : " << ++COUNT << endl;
        display(Knight_board);
        return;
    }
    
    if (row >= TOTAL_ROWS) {
        return;
    }
    
    if (col >= TOTAL_COLS) {
        Nknights(Knight_board, k, row + 1, 0);
        return;
    }
    
    int remaining_cells = (TOTAL_ROWS * TOTAL_COLS) - (row * TOTAL_COLS + col);
    if (remaining_cells < k) {
        return;
    }
    
    if (can_place(Knight_board, row, col)) {
        Knight_board[row][col] = true;
        Nknights(Knight_board, k - 1, row, col + 1);
        Knight_board[row][col] = false;  
    }
    
    Nknights(Knight_board, k, row, col + 1);
}

int main() {
    cout << "Enter the dimensions of the board(m*n):" << endl;
    cin >> TOTAL_ROWS >> TOTAL_COLS;
    
    
    cout << "Enter the number of knights to be used: " << endl;
    int k;
    cin >> k;
    
    if (k > TOTAL_ROWS * TOTAL_COLS) {
        cout << "Too many knights for the given board size!" << endl;
        return 1;
    }
    
    Knight_board.resize(TOTAL_ROWS, vector<bool>(TOTAL_COLS, false));
    auto start = high_resolution_clock::now();
    Nknights(Knight_board, k, 0, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout <<"time taken: " <<duration.count()<<" milliseconds" << endl;
    if (COUNT == 0) {
        cout << "No solution exists!" << endl;
    } else {
        cout << "Total number of solutions: " << COUNT << endl;
    }
    
    return 0;
}