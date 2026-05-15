#include <bits/stdc++.h>
using namespace std;

int main() {
    	ios::sync_with_stdio(false);
    	cin.tie(nullptr);

    	freopen("muzeu.in",  "r", stdin);
    	freopen("muzeu.out", "w", stdout);

    	int n;
    	cin >> n;

    	vector<string> grid(n);
    	for (int i = 0; i < n; i++) cin >> grid[i];

    	vector<vector<int>> dist(n, vector<int>(n, -1));

    	deque<pair<int,int>> q;
	
	for (int i = 0; i < n; i++)
    		for (int j = 0; j < n; j++) {
        	if (grid[i][j] == '#') dist[i][j] = -2;
        	if (grid[i][j] == 'P') { dist[i][j] = 0; q.push_back({i, j}); }
    	}

	int dr[] = {-1, 0, 1,  0};
	int dc[] = { 0, 1, 0, -1};

	while (!q.empty()) {
    		auto [r, c] = q.front(); q.pop_front();
    		for (int d = 0; d < 4; d++) {
        	int nr = r + dr[d], nc = c + dc[d];
        	if (nr >= 0 && nr < n && nc >= 0 && nc < n
            		&& dist[nr][nc] == -1
            		&& grid[nr][nc] != '#') {
            	dist[nr][nc] = dist[r][c] + 1;
            	q.push_back({nr, nc});
        	}
    	}
}

    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++) {
            	cout << dist[i][j];
            	if (j < n - 1) cout << ' ';
        	}
        	cout << '\n';
    	}

    	return 0;
}
