#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b) {
	if(a[0] == b[0]) 
		return a[1] > b[1];
	return a[0] < b[0];
}

class Solution {
	public:
		int maxEnvelopes(vector<vector<int>>& envelopes) {
		sort(envelopes.begin(), envelopes.end(), cmp);
	
		vector<int> dp;
		for (auto& e : envelopes) {
			int h = e[1];
			auto it = lower_bound(dp.begin(), dp.end(), h);
			if (it == dp.end())
				dp.push_back(h);
			else *it = h;
		}
	
		return dp.size();
	}
};

int main() {
	int n;
	cout << "Number of envelopes: ";
	cin >> n;

	vector<vector<int>> envelopes(n, vector<int>(2));
	cout << "Enter each envelope as width height:\n";
	for (int i = 0; i < n; i++) {
		cout << "Envelope " << i << ": ";
		cin >> envelopes[i][0] >> envelopes[i][1];
	}

	cout << "\nEnvelopes entered:\n";
	for (auto& e : envelopes) {
		cout << "[" << e[0] << ", " << e[1] << "]\n";
	}
	
	Solution sol;
	int result = sol.maxEnvelopes(envelopes);
	cout << "\nMax envelopes: " << result << "\n";

	return 0;
}
