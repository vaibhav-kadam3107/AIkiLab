#include <bits/stdc++.h>
using namespace std;

#define pb push_back

// Function to find the solution path using DFS with backtracking
void giveans(vector<vector<int>> initial, vector<vector<int>> final, int i, int j, vector<pair<int, int>> ans) {
    // Base case: If the initial configuration matches the final configuration, print the answer
    if (initial == final) {
        for (auto move : ans) {
            cout << move.first << " " << move.second << "\n";
        }
        cout << "\n";
        return;
    }

    // Limit the depth of recursion to avoid infinite loops (arbitrary limit of 9 moves)
    if (ans.size() > 9) {
        return;
    }

    // Move the empty space (0) in all possible directions and recurse

    // Move down
    if (i + 1 < 3 && initial[i + 1][j] != final[i + 1][j]) {
        ans.pb({i + 1, j});
        swap(initial[i][j], initial[i + 1][j]);
        giveans(initial, final, i + 1, j, ans);
        swap(initial[i][j], initial[i + 1][j]);
        ans.pop_back();
    }
    // Move right
    if (j + 1 < 3 && initial[i][j + 1] != final[i][j + 1]) {
        ans.pb({i, j + 1});
        swap(initial[i][j + 1], initial[i][j]);
        giveans(initial, final, i, j + 1, ans);
        swap(initial[i][j + 1], initial[i][j]);
        ans.pop_back();
    }
    // Move up
    if (i - 1 >= 0 && initial[i - 1][j] != final[i - 1][j]) {
        ans.pb({i - 1, j});
        swap(initial[i][j], initial[i - 1][j]);
        giveans(initial, final, i - 1, j, ans);
        swap(initial[i][j], initial[i - 1][j]);
        ans.pop_back();
    }
    // Move left
    if (j - 1 >= 0 && initial[i][j - 1] != final[i][j - 1]) {
        ans.pb({i, j - 1});
        swap(initial[i][j], initial[i][j - 1]);
        giveans(initial, final, i, j - 1, ans);
        swap(initial[i][j], initial[i][j - 1]);
        ans.pop_back();
    }
}

int main(int argc, char const *argv[]) {
    // Initialize the initial and final 3x3 grids
    vector<vector<int>> initial(3, vector<int>(3, 0));
    vector<vector<int>> final(3, vector<int>(3, 0));
    
    // Read the initial configuration
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> initial[i][j];
        }
    }
    
    // Read the final configuration
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> final[i][j];
        }
    }

    // Vector to store the sequence of moves
    vector<pair<int, int>> ans;
    
    // Find the position of the empty space (0) and start the DFS
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (initial[i][j] == 0) {
                giveans(initial, final, i, j, ans);
            }
        }
    }

    return 0;
}


// 2 8 3
// 1 6 4
// 7 0 5

// 1 2 3
// 8 0 4
// 7 6 5



/*

Problem Description:
This code solves the 8-puzzle problem, a sliding puzzle that consists of a 3x3 grid with 8 numbered tiles and one empty space. The goal is to move the tiles around until they match a specified final configuration.

AI Search Used:
The code uses Depth-First Search (DFS) with backtracking. DFS explores paths to the maximum depth before backtracking and trying alternate paths.

Algorithm:
Initialization:
Read the initial and final states of the puzzle.
Identify the position of the empty space (denoted by 0) in the initial state.
DFS with Backtracking:
Swap the empty space with adjacent tiles.
Recursively check if the current state matches the final state.
Backtrack if the current state does not lead to a solution.

Detailed Breakdown:
Function Definitions:

giveans Function:
This function performs the DFS search and backtracks when necessary.
It prints the sequence of moves when the initial state matches the final state.
It recursively explores all possible moves of the empty space (0).
Base Cases and Limits:

If the current state matches the final state, it prints the sequence of moves stored in ans.
If the depth of recursion exceeds 9 moves, the function returns without further recursion to prevent infinite loops or excessive computation.
Recursive Exploration:

The function tries to move the empty space down, right, up, and left, respectively.
After each move, it recursively calls itself to explore the next state.
It backtracks by undoing the move (swapping back) and removing the move from the ans vector.
Main Function:

Reads the initial and final configurations from the input.
Initializes a vector to store the sequence of moves.
Finds the position of the empty space (0) in the initial configuration.
Calls giveans to start the DFS from the position of the empty space.
Example Input and Output:
Input:

Copy code
2 8 3
1 6 4
7 0 5

1 2 3
8 0 4
7 6 5
Output:

python
Copy code
1 2
2 1
...
(The output will be the sequence of moves leading to the solution, if one exists within the depth limit of 9 moves.)

Summary:
This code uses DFS with backtracking to solve the 8-puzzle problem by exploring all possible moves of the empty space and checking if the resulting state matches the final state. The search is limited to a depth of 9 moves to avoid infinite recursion and excessive computation. The solution sequence of moves is printed when found.








*/
