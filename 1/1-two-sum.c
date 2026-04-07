#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	int* result = (int*)malloc(2 * sizeof(int));

	for (int i = 0; i < numsSize; i++) {
		for (int j = i + 1; j < numsSize; j++) {
			if (nums[i] + nums[j] == target) {
				result[0] = i;
				result[1] = j;
				*returnSize = 2;
				return result;
			}
		}
	}
	*returnSize = 0;
	return NULL;
}

int main() {
	int numsSize;
	printf("Array size: ");
	scanf("%d", &numsSize);

	int* nums = (int*) malloc(numsSize * sizeof(int));

	printf("Enter %d numbers: ", numsSize);
	for (int i = 0; i < numsSize; i++) {
		scanf("%d", &nums[i]);
	}

	int target;
	printf("Target: ");
	scanf("%d", &target);
	
	int returnSize;
	int* result = twoSum(nums, numsSize, target, &returnSize);
	if(result == NULL) {
		printf("No solution found!\n");
	} else {
		printf("Indices: [%d, %d] (values %d + %d = %d)\n",
				result[0], result[1],
				nums[result[0]], nums[result[1]],
				target);
	}

	free(result);
	free(nums);
	return 0;
}
