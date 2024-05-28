#include<bits/stdc++.h>
using namespace std;

const int N = 8;

int calcEvaluationFunction(int (&board)[N])
{
	int cnt = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = i+1; j < 8; ++j)
		{
			if(board[i] == board[j])
				++cnt;
			else if(abs(i-j) == abs(board[i]-board[j]))
				++cnt;
		}
	}
	return 28-cnt;			
}

void printBoard(int (&board)[N])
{
	int grid[10][10];
	memset(grid, 0, sizeof grid);
	for(int i = 0; i < 8; ++i)
		grid[ board[i] ][i] = 1;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	return;
}

void copyBoard(int (&board1)[N], int (&board2)[N])
{
	for(int i = 0; i < 8; ++i)
		board1[i] = board2[i];
}
	
bool hillClimbing(int (&board)[N])
{
	int bestBoard[N], bestValue, boardValue;
	copyBoard(bestBoard, board);
	
	int cnt = 0;
	while(1)
	{
		int currBoard[N], currValue;
		copyBoard(currBoard, board);
		boardValue = bestValue = calcEvaluationFunction(board);
		
		if(bestValue == 28)
		{
			cout << "Reached Global Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 1;
		}
		
		++cnt;		
		for(int i = 0; i < 8; ++i)
		{
			int temp = currBoard[i];
			for(int j = 0; j < 8; ++j)
			{
				if(j == board[i])
					continue;
				currBoard[i] = j;
				currValue = calcEvaluationFunction(currBoard);
				if(currValue > bestValue)
				{
					bestValue = currValue;
					copyBoard(bestBoard, currBoard);
				}
			}
			currBoard[i] = temp;
		}
		if(bestValue <= boardValue)
		{
			cout << "Stucked in Local Maxima after " << cnt << " moves" << endl;
			printBoard(bestBoard);
			return 0;
		}
		copyBoard(board, bestBoard);
	}
}

int main()
{
	//~ freopen("output.txt", "w", stdout);
	srand(time(NULL));
	bool success = 0;
	int cnt = 1, board[N];
	while(1)
	{
		for(int i = 0; i < 8; ++i)
			board[i] = rand()%8;			
	
		cout << "======================== Iteration : " << cnt << endl;
		cout << "Initial Board" << endl;
		printBoard(board);
		success = hillClimbing(board);
		++cnt;
		
		if(success)
			break;
	}
	
	
	return 0;
}

/*

Problem Description:
The 8-Queens problem is a classic puzzle where the objective is to place 8 queens on an 8×8 chessboard such that no two queens threaten each other. This means no two queens can be in the same row, column, or diagonal.

AI Search Used:
The code uses a local search method known as hill climbing. Hill climbing is an optimization algorithm that continuously moves towards increasing value (in this context, decreasing the number of conflicts among queens) until it reaches a peak (local maximum) from where no better neighboring state is found.

Algorithm:
The hill climbing algorithm starts with a random configuration and iteratively makes local changes to improve the solution based on an evaluation function until it reaches an optimal or local maximum solution. Here's a step-by-step breakdown:

Generate a random initial configuration.
Evaluate the current configuration using an evaluation function that counts conflicts.
Generate neighboring configurations by moving one queen in its column and evaluate these neighbors.
Select the neighbor with the best (highest) evaluation score and move to this new configuration.
Repeat until no better neighbor is found (local maximum) or an optimal solution (no conflicts) is reached.

Detailed Breakdown:
Board Representation:

board is an array where board[i] represents the row position of the queen in column i.
Evaluation Function (calcEvaluationFunction):

Counts the number of conflicting pairs of queens. The total number of non-conflicting pairs is 28. The function returns 28 - cnt where cnt is the number of conflicts.
Print Board (printBoard):

Converts the board array into a 2D grid and prints it, showing 1 for queens and 0 for empty spaces.
Copy Board (copyBoard):

Copies one board configuration to another.
Hill Climbing (hillClimbing):

Starts with the initial board configuration and iteratively tries to improve it by moving queens to different rows within their columns.
For each position, it calculates the evaluation function and keeps the best configuration.
If no improvement is found (i.e., stuck in a local maximum), it prints the board and returns failure.
If an optimal solution (evaluation score 28) is found, it prints the board and returns success.
Main Function (main):

Initializes the board with a random configuration and repeatedly applies the hill climbing algorithm until a solution is found.
Prints the initial and resulting boards for each iteration.
This code demonstrates the use of hill climbing to solve the 8-Queens problem by iteratively improving a randomly generated board configuration based on an evaluation function that counts conflicts.








*/