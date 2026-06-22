#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MX = 1e5 + 5;
const int INF = 2e9 + 69;

vector<pair<int, int> > adj_all[MX];
int dist1[MX];

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, A, B;
	cin >> n >> m;
	A = 1; B = n;

	for (int u, v, w, z, i = 0; i < m; i++) {
		cin >> u >> v >> w >> z;
		adj_all[u].push_back(make_pair(v, w));
		adj_all[v].push_back(make_pair(u, w));
	}

	for (int i = 1; i <= n; i++) {
		dist1[i] = INF;
	}

	// BFS source A graph adj_all
	queue<pair<int, int> > qq;
	dist1[A] = 0;
	qq.push(make_pair(0, A));
	for (; !qq.empty(); qq.pop()) {
		int dst = qq.front().first;
		int nw = qq.front().second;
		if (dst > dist1[nw]) continue;
		for (pair<int, int> e : adj_all[nw]) {
			int nx = e.first;
			int wt = e.second;
			if (dist1[nx] > dist1[nw] + wt) {
				dist1[nx] = dist1[nw] + wt;
				qq.push(make_pair(dist1[nx], nx));
			}
		}
	}

	if (dist1[n] >= INF) dist1[n] = -1;
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int x; cin >> x;
		cout << dist1[n] << endl;
	}

	return 0;
}