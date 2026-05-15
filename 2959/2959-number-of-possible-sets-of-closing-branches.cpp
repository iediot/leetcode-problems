#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
public:
	int numberOfSets(int n, int maxDistance, vector<vector<int>>&roads) {
		int count = 0;
		
		for (int mask = 0; mask < (1 << n); ++mask) {
			vector<vector<pair<int, int>>> adj(n);
			for (auto& r : roads) {
				int u = r[0];
				int v = r[1];
				int w = r[2];
				bool uKept = mask & (1 << u);
				bool vKept = mask & (1 << v);
				if (uKept && vKept) {
					adj[u].push_back({v, w});
					adj[v].push_back({u, w});
				}
			}

			bool valid = true;
			for (int start = 0; start < n && valid; ++start) {
				if (!(mask & (1 << start)))
					continue;

				vector<int> dist(n, INT_MAX);
				dist[start] = 0;
				priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
				pq.push({0, start});

				while (!pq.empty()) {
					auto [d, u] = pq.top();
					pq.pop();
					if (d > dist[u])
						continue;
					for (auto [v, w] : adj[u]) {
						if (d + w < dist[v]) {
							dist[v] = d + w;
                            pq.push({dist[v], v});
						}
					}
				}

                for (int j = 0; j < n; ++j) {
                    if (!(mask & (1 << j)))
                        continue;
                    if (dist[j] > maxDistance) {
                        valid = false;
                        break;
                    }
                }
			}   // <-- end of for (start)

            if (valid)
                ++count;
		}   // <-- end of for (mask)

        return count;
	}
};   // <-- end of class Solution

static void runTest(const string& name, int n, int maxDistance, vector<vector<int>> roads, int expected) {
    Solution sol;
    int got = sol.numberOfSets(n, maxDistance, roads);
    cout << name << ": got " << got << ", expected " << expected << "  -> " << (got == expected ? "PASS" : "FAIL") << "\n";
    assert(got == expected);
}

int main () {
    runTest("Example 1", 3, 5, {{0, 1, 2}, {1, 2, 10}, {0, 2, 10}}, 5);
    runTest("Example 2", 3, 5, {{0, 1, 20}, {0, 1, 10}, {1, 2, 2}, {0, 2, 2}}, 7);
    runTest("Example 3", 1, 10, {}, 2);
    runTest("No roads", 3, 5, {}, 4);
    runTest("maxDistance = 0", 3, 0, {{0, 1, 1}, {1, 2, 1}}, 4);
    cout << "\nAll tests passed.\n";
    return 0;
}
