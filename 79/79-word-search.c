#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfs(char** board, int rows, int cols, char* word, int i, int j, int k) {
	if (word[k] == '\0') return 1;
	if (i < 0 || i >= rows || j < 0 || j >= cols) return 0;
	if (board[i][j] != word[k]) return 0;

	char tmp = board[i][j];
	board[i][j] = '#'; // visited
	
	int found = dfs(board, rows, cols, word, i+1, j, k+1) ||
		dfs(board, rows, cols, word, i-1, j, k+1) ||
		dfs(board, rows, cols, word, i, j+1, k+1) ||
		dfs(board, rows, cols, word, i, j-1, k+1);

	board[i][j] = tmp;
	return found;
}

int exist(char** board, int boardSize, int* boardColSize, char* word) {
	for(int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardColSize[0]; j++) {
			if (dfs(board, boardSize, boardColSize[0], word, i, j, 0))
				return 1;
		}
	}
	return 0;
}

int main() {
	int rows, cols;

	printf("Rows: ");
	scanf("%d", &rows);
	printf("Cols: ");
	scanf("%d", &cols);

	char** board = (char**)malloc(rows * sizeof(char*));
	for (int i = 0; i < rows; i++) {
		board[i] = (char*)malloc(cols * sizeof(char));
	}

	printf("Enter board row by row:\n");
	for (int i = 0; i < rows; i++) {
		char tmp[100];
		printf("Row %d: ", i);
		scanf("%99s", tmp);
		for (int j = 0; j < cols; j++) {
			board[i][j] = tmp[j];
		}
	}

	printf("\nBoard:\n");
	for (int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}

	char word[100];
	printf("\nWord to search for: ");
	scanf("%99s", word);

	int colSize = cols;
	int result = exist(board, rows, &colSize, word);

	printf("Result: %s\n", result ? "true" : "false");

	for (int i = 0; i < rows; i++) {
		free(board[i]);
	}
	free(board);
	return 0;
}
