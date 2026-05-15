#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    long long minimumCost(string source, string target,
                          vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
        vector<vector<pair<int,int>>> adj(26);
        for (size_t i = 0; i < cost.size(); ++i) {
            int u = original[i] - 'a';
            int v = changed[i]  - 'a';
            adj[u].push_back({v, cost[i]});
        }

        vector<vector<long long>> cache(26);

        auto dijkstra = [&](int start) -> vector<long long> {
            vector<long long> dist(26, LLONG_MAX);
            dist[start] = 0;
            priority_queue<pair<long long,int>,
                           vector<pair<long long,int>>,
                           greater<>> pq;
            pq.push({0, start});

            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                for (auto [v, w] : adj[u]) {
                    if (d + w < dist[v]) {
                        dist[v] = d + w;
                        pq.push({dist[v], v});
                    }
                }
            }
            return dist;
        };

        long long total = 0;
        for (size_t i = 0; i < source.size(); ++i) {
            int s = source[i] - 'a';
            int t = target[i] - 'a';
            if (s == t) continue;

            if (cache[s].empty()) cache[s] = dijkstra(s);

            if (cache[s][t] == LLONG_MAX) return -1;
            total += cache[s][t];
        }
        return total;
    }
};

static void runTest(const string& name, string source, string target,
                    vector<char> original, vector<char> changed,
                    vector<int> cost, long long expected) {
    Solution sol;
    long long got = sol.minimumCost(source, target, original, changed, cost);
    cout << name << ": got " << got << ", expected " << expected
         << "  -> " << (got == expected ? "PASS" : "FAIL") << "\n";
    assert(got == expected);
}

int main() {
    runTest("Example 1", "abcd", "acbe",
            {'a','b','c','c','e','d'}, {'b','c','b','e','b','e'},
            {2,5,5,1,2,20}, 28);

    runTest("Example 2", "aaaa", "bbbb",
            {'a','c'}, {'c','b'}, {1,2}, 12);

    runTest("Example 3 (impossible)", "abcd", "abce",
            {'a'}, {'e'}, {10000}, -1);

    runTest("Already equal", "hello", "hello",
            {'a'}, {'b'}, {1}, 0);

    runTest("Multi-edge min wins", "aa", "bb",
            {'a','a'}, {'b','b'}, {100,3}, 6);

    runTest("Indirect beats direct", "a", "b",
            {'a','a','c'}, {'b','c','b'}, {100,1,1}, 2);

    cout << "\nAll tests passed.\n";
    return 0;
}
