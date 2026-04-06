#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(char** board, int row, int col, char c) {
	for (int i = 0; i < 9; i++) {
		if (board[row][i] == c) 
			return 0;
		if (board[i][col] == c) 
			return 0;
		if (board[3*(row/3) + i/3][3*(col/3) + i%3] == c)
			return 0;
	}
	return 1;
}

int solve(char** board) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == '.') {
				for (char c = '1'; c <= '9'; c++) {
					if (isValid(board, i, j, c)) {
						board[i][j] = c;
						if (solve(board))
							return 1;
						board[i][j] = '.';
					}
				}
				return 0;
			}
		}
	}
	return 1;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
	solve(board);
}

void printBoard(char** board) {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i != 0)
			printf("------+-------+------\n");
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j != 0)
				printf("| ");
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

int main() {
	char** board = (char**)malloc(9 * sizeof(char*));
	for (int i = 0; i < 9; i++)
		board[i] = (char*)malloc(9 * sizeof(char));

	printf("Enter the board (digits or '.'):\n");
	for (int i = 0; i < 9; i++) {
		char tmp[20];
		printf("Row %d: ", i);
		scanf("%19s", tmp);
		for (int j = 0; j < 9; j++) 
			board[i][j] = tmp[j];
	}

	printf("\nUnsolved:\n");
	printBoard(board);

	int colSize = 9;
	solveSudoku(board, 9, &colSize);

	printf("\nSolved:\n");
	printBoard(board);

	for (int i = 0; i < 9; i++)
		free(board[i]);
	free(board);
	return 0;
}
