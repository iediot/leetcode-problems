import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Solution {
	public List<Integer> largestDivisibleSubset(int[] nums) {
		int n = nums.length;
		Arrays.sort(nums);

		int[] dp = new int[n];
		int[] parent = new int[n];
		Arrays.fill(dp, 1);
		Arrays.fill(parent, -1);

		int maxSize = 1, maxIdx = 0;

		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
					parent[i] = j;
				}
			}
			if (dp[i] > maxSize) {
				maxSize = dp[i];
				maxIdx = i;
			}
		}

		List<Integer> result = new ArrayList<>();
		int idx = maxIdx;
		while (idx != -1) {
			result.add(0, nums[idx]);
			idx = parent[idx];
		}

		return result;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("Array size: ");
		int n = sc.nextInt();

		int[] nums = new int[n];
		System.out.print("Enter " + n + " numbers: ");
		for (int i = 0; i < n; i++)
			nums[i] = sc.nextInt();

		Solution sol = new Solution();
		List<Integer> result = sol.largestDivisibleSubset(nums);

		System.out.println("Largest divisible subset: " + result);
		sc.close();
	}
}
