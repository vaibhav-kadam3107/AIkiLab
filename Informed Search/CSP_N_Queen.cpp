#include <iostream>
#include <vector>

using namespace std;

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(vector<vector<char>>& board, int row, int col, int N) {
    // Check if there is a queen in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q')
            return false;
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q')
            return false;
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j) {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;
}

// Function to solve N-Queens problem using backtracking with CSP
bool solveNQueensUtil(vector<vector<char>>& board, int row, int N) {
    if (row == N)
        return true;

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 'Q';

            if (solveNQueensUtil(board, row + 1, N))
                return true;

            board[row][col] = '.'; // Backtrack
        }
    }

    return false;
}

// Function to solve N-Queens problem using CSP
void solveNQueens(int N) {
    vector<vector<char>> board(N, vector<char>(N, '.'));

    if (solveNQueensUtil(board, 0, N)) {
        cout << "Solution exists:\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "Solution does not exist\n";
    }
}

int main() {
    int N;
    cout << "Enter the number of queens (N): ";
    cin >> N;

    solveNQueens(N);

    return 0;
}

/*

This code implements a solution to the N-Queens problem using backtracking. The N-Queens problem involves placing N queens on an N×N chessboard such that no two queens can attack each other. Here’s a detailed explanation of the code:

isSafe Function:

This function checks whether it is safe to place a queen at board[row][col].
It ensures no other queens are placed in the same column, upper left diagonal, and upper right diagonal.
solveNQueensUtil Function:

This is a recursive utility function to solve the N-Queens problem.
It tries to place a queen in each column of the current row (row), and for each column, it checks if placing the queen is safe.
If placing the queen is safe, it places the queen and then recursively tries to place queens in the next row (row + 1).
If placing the queen leads to a solution, it returns true.
If placing the queen does not lead to a solution, it backtracks by removing the queen (sets the cell back to '.') and continues with the next column.
If no column in the current row is safe, it returns false.
solveNQueens Function:

This function initializes the chessboard and starts the solving process.
It creates an N×N board initialized with '.' indicating empty cells.
It calls solveNQueensUtil starting from the first row (0).
If solveNQueensUtil returns true, it prints the board showing the solution.
If solveNQueensUtil returns false, it prints that no solution exists.
main Function:

It prompts the user to enter the number of queens (N).
It then calls the solveNQueens function with the given N.

*/