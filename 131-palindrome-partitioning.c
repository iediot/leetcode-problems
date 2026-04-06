#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int isPalindrome(char* s, int left, int right) {
	while (left < right) {
		if (s[left] != s[right])
			return 0;
		left++;
		right--;
	}
	return 1;
}

void backtrack(char* s, int start, int len, char*** result,
		int* returnSize, int* returnColumnSizes,
		char** current, int currentSize) {
	if (start == len) {
		result[*returnSize] = (char**)malloc(currentSize * sizeof(char*));
		for (int i = 0; i < currentSize; i++) {
			result[*returnSize][i] = strdup(current[i]);
		}
		returnColumnSizes[*returnSize] = currentSize;
		(*returnSize)++;
		return;
	}

	for (int end = start; end < len; end++) {
		if (isPalindrome(s, start, end)) {
			int subLen = end - start + 1;
			current[currentSize] = (char*)malloc((subLen + 1) * sizeof(char));
			strncpy(current[currentSize], s + start, subLen);
			current[currentSize][subLen] = '\0';

			backtrack(s, end + 1, len, result, returnSize,
			returnColumnSizes, current, currentSize + 1);

			free(current[currentSize]);
		}
	}
}

char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
	int len = strlen(s);
	int maxResults = 32768;

	char*** result = (char***)malloc(maxResults * sizeof(char**));
	*returnColumnSizes = (int*)malloc(maxResults * sizeof(int));
	*returnSize = 0;

	char** current = (char**)malloc(len * sizeof(char*));

	backtrack(s, 0, len, result, returnSize, *returnColumnSizes, current, 0);

	free(current);
	return result;
}

int main() {
	char s[100];
	printf("Enter string: ");
	scanf("%99s", s);

	int returnSize;
	int* returnColumnSizes;
	char*** result = partition(s, &returnSize, &returnColumnSizes);

	printf("Found %d partitions:\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("[");
		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%s", result[i][j]);
			if (j < returnColumnSizes[i] - 1)
				printf(", ");
			free(result[i][j]);
		}
		printf("]\n");
		free(result[i]);
	}

	free(result);
	free(returnColumnSizes);
	return 0;
}
