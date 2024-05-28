#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Structure to represent a node in the grid
struct Node
{
    int x, y;     // Coordinates
    int g, h, f;  // Costs
    Node *parent; // Parent node pointer

    Node(int _x, int _y)
    {
        x = _x;
        y = _y;
        g = 0;
        h = 0;
        f = 0;
        parent = nullptr;
    }
};

// Function to calculate Manhattan distance heuristic
int heuristic(Node *current, Node *goal)
{
    return abs(current->x - goal->x) + abs(current->y - goal->y);
}

// Function to check if a node is within the grid bounds and is traversable
bool isValid(int x, int y, int grid_width, int grid_height, vector<vector<int>> &grid)
{
    return x >= 0 && x < grid_width && y >= 0 && y < grid_height && grid[x][y] == 0;
}

// Function to reconstruct path from goal to start
vector<pair<int, int>> reconstructPath(Node *current)
{
    vector<pair<int, int>> path;
    while (current != nullptr)
    {
        path.emplace_back(current->x, current->y);
        current = current->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

// AO* algorithm
vector<pair<int, int>> ao_star(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> goal)
{
    int grid_width = grid.size();
    int grid_height = grid[0].size();

    priority_queue<Node *> open_list;
    unordered_set<Node *> closed_set;

    Node *start_node = new Node(start.first, start.second);
    start_node->h = heuristic(start_node, new Node(goal.first, goal.second));
    start_node->f = start_node->g + start_node->h;
    open_list.push(start_node);

    while (!open_list.empty())
    {
        Node *current = open_list.top();
        open_list.pop();

        if (current->x == goal.first && current->y == goal.second)
        {
            return reconstructPath(current);
        }

        closed_set.insert(current);

        // Explore neighbors
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                int next_x = current->x + dx;
                int next_y = current->y + dy;

                if (!isValid(next_x, next_y, grid_width, grid_height, grid))
                    continue;

                Node *neighbor = new Node(next_x, next_y);
                neighbor->g = current->g + 1;
                neighbor->h = heuristic(neighbor, new Node(goal.first, goal.second));
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                if (closed_set.find(neighbor) != closed_set.end())
                    continue;

                open_list.push(neighbor);
            }
        }
    }

    // No path found
    return {};
}

int main()
{
    // Example grid: 0 represents an empty cell, 1 represents an obstacle
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}};

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {3, 3};

    vector<pair<int, int>> path = ao_star(grid, start, goal);

    if (!path.empty())
    {
        cout << "Path found: ";
        for (const auto &p : path)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found!" << endl;
    }

    return 0;
}

/*Explanation:
Includes and Namespace:

#include <iostream>: Includes the standard input/output stream library.
#include <vector>: Includes the vector library.
using namespace std;: Allows use of standard library objects without the std:: prefix.
isSafe Function:

bool isSafe(const vector<int> &board, int row, int col, int n): Checks if placing a queen at position (row, col) is safe.
It checks the current column, the upper diagonal, and the lower diagonal for conflicts with existing queens.
If any queen is found in the same row or diagonals, it returns false. Otherwise, it returns true.
solveNQueens Function:

void solveNQueens(vector<int> &board, int col, int n, vector<vector<int>> &solutions): Recursively solves the N-queens problem.
If col equals n, it means all queens are placed correctly, and the current board configuration is added to solutions.
It iterates through each row in the current column to try placing a queen.
If placing a queen at (row, col) is safe, it places the queen and recursively attempts to place the rest.
It uses backtracking by removing the queen and trying the next possibility.
printSolution Function:

void printSolution(const vector<vector<int>> &solutions, int n): Prints all the solutions in a readable format.
It iterates through all solutions and prints each one in a grid format.
Queens are represented by " Q ", and empty spaces by " . ".
main Function:

int main(): The main function sets up the board and calls the function to solve the N-queens problem.
int n = 5;: Sets the size of the board to 5x5.
vector<int> board(n, -1);: Initializes the board with -1, indicating no queens are placed.
vector<vector<int>> solutions;: Initializes a vector to store all solutions.
solveNQueens(board, 0, n, solutions);: Calls the function to solve the N-queens problem starting from the first column.
If solutions are found, it prints them; otherwise, it indicates that no solution exists.
Summary:
This code solves the N-queens problem using a backtracking approach. It checks for safe positions to place queens on an n x n chessboard such that no two queens threaten each other. It stores all valid solutions and prints them in a human-readable format.*/