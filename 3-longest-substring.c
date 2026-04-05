#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
	int map[128] = {0};
	int max = 0;
	int left = 0;

	for (int right = 0; s[right] != '\0'; right++) {
		if (map[(int)s[right]] > left) {
			left = map[(int)s[right]];
		}
		map[(int)s[right]] = right + 1;
		if (right - left + 1 > max) {
			max = right - left + 1;
		}
	}
	return max;
}

int main() {
	char s[1000];

	printf("Enter string: ");
	scanf("%999s", s);

	int result = lengthOfLongestSubstring(s);
	printf("Longest substring without repeating characters: %d\n", result);
	return 0;
}
