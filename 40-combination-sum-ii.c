#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void backtrack(int* candidates, int size, int target, int start,
		int* current, int currentSize, int** results,
		int* returnSize, int* returnColumnSizes) {
	if (target == 0) {
		results[*returnSize] = (int*)malloc(currentSize * sizeof(int));
		memcpy(results[*returnSize], current, currentSize * sizeof(int));
		returnColumnSizes[*returnSize] = currentSize;
		(*returnSize)++;
		return;
	}

	for (int i = start; i < size; i++) {
		if (candidates[i] > target) break;
		if (i > start && candidates[i] == candidates[i-1]) continue;

		current[currentSize] = candidates[i];
		backtrack(candidates, size, target - candidates[i], i + 1,
				current, currentSize + 1, results,
				returnSize, returnColumnSizes);
	}
}

int** combinationSum2(int* candidates, int candidatesSize, 
		int target, int* returnSize, int** returnColumnSizes) {
	qsort(candidates, candidatesSize, sizeof(int), cmp);

	int** results = (int**)malloc(500 * sizeof(int*));
	int* colSizes = (int*)malloc(500 * sizeof(int));
	*returnColumnSizes = colSizes;
	*returnSize = 0;

	int* current = (int*)malloc(candidatesSize * sizeof(int));

	backtrack(candidates, candidatesSize, target, 0,
			current, 0, results,
			returnSize, *returnColumnSizes);
	
	free(current);
	return results;
}

int main() {
	int n;
	printf("Number of candidates: ");
	scanf("%d", &n);

	int* candidates = (int*)malloc(n * sizeof(int));
	printf("Enter %d numbers: ", n);
	for (int i = 0; i < n; i++)
		scanf("%d", &candidates[i]);

	int target;
	printf("Target: ");
	scanf("%d", &target);

	int returnSize;
	int* returnColumnSizes;
	int** result = combinationSum2(candidates, n, target, 
			&returnSize, &returnColumnSizes);

	printf("Found %d combinations:\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("[");
		for (int j = 0; j < returnColumnSizes[i]; j++) {
			printf("%d", result[i][j]);
			if (j < returnColumnSizes[i] - 1)
				printf(", ");
		}
		printf("]\n");
		free(result[i]);
	}

	free(result);
	free(returnColumnSizes);
	free(candidates);
	return 0;
}
