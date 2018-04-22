#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define UNASSIGNED 0
#define N 9

void printBoard(int board[9][9]){
	printf("==============================================\n");
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			printf("%d\t", board[i][j]);
		}
		printf("\n");
	}
}

bool findSpot(int board[9][9], int & row, int & col){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(board[i][j] == UNASSIGNED){
				row = i;
				col = j;
				return false;
			}
		}
	}
	return true;
}

/* Got from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
 * 
 * Returns whether any assigned entry n the specified row matches 
 * the given number. */
bool UsedInRow(int board[N][N], int row, int num)
{
        for (int col = 0; col < N; col++)
                if (board[row][col] == num)
                        return true;
        return false;
}

/* Got from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
 * 
 * Returns whether any assigned entry in the specified column matches 
 * the given number. */
bool UsedInCol(int board[N][N], int col, int num)
{
        for (int row = 0; row < N; row++)
                if (board[row][col] == num)
                        return true;
        return false;
}

/* Got from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
 *
 * Returns whether any assigned entry within the specified 3x3 box matches 
 * the given number. */
bool UsedInBox(int board[N][N], int boxStartRow, int boxStartCol, int num)
{
        for (int row = 0; row < 3; row++)
                for (int col = 0; col < 3; col++)
                        if (board[row+boxStartRow][col+boxStartCol] == num)
                                return true;
        return false;
}

/* Got from: https://stackoverflow.com/questions/19022739/sudoku-solver-in-c
 * 
 * Returns whether it will be legal to assign num to the given row,col location. 
 * */
bool isSafe(int board[N][N], int row, int col, int num)
{
        return !UsedInRow(board, row, num) && !UsedInCol(board, col, num) &&
        !UsedInBox(board, row - row % 3 , col - col % 3, num);
}


bool solve(int board[9][9]){
	int x, y;
	printf("Examining %d, %d.\n", x, y);
	printBoard(board);
	if(findSpot(board, x, y)){
		return true;
	}
	for(int val = 1; val<10; val++){
		if(isSafe(board, x, y, val)){
			board[x][y] = val;
			if(solve(board))
			{
				return true;
			}
			printf("Backtracking.\n");
			board[x][y] = UNASSIGNED;
		}
	
	}
	return false;
}


int main(int argc, char** argv){
	int board[9][9] = {{ 0, 3, 0, 0, 0, 0, 0, 2, 0 },
		{ 0, 9, 0, 0, 0, 0, 0, 8, 5 },
		{ 5, 0, 0, 0, 8, 0, 4, 0, 0 },
		{ 4, 0, 7, 2, 0, 6, 8, 9, 0 },
		{ 0, 1, 0, 8, 0, 9, 0, 4, 0 },
		{ 0, 8, 9, 5, 0, 1, 3, 0, 2 },
		{ 0, 0, 3, 0, 1, 0, 0, 0, 9 },
		{ 9, 4, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 7, 0, 0, 0, 0, 0, 3, 0 }
	};

	bool complete = solve(board);
	if(complete){
		printf("Found a solution:\n\n");
		printBoard(board);
	} else {
		printf("No solution found.");
	}
}

