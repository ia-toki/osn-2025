#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MX = 1e5 + 5;
const int INF = 2e9 + 69;

vector<pair<int, pair<int, int> > > adj_all[MX];
int dist1[MX];

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, A, B;
	cin >> n >> m;
	A = 1; B = n;

	for (int u, v, w, z, i = 0; i < m; i++) {
		cin >> u >> v >> w >> z;
		adj_all[u].push_back(make_pair(v, make_pair(w, z)));
		adj_all[v].push_back(make_pair(u, make_pair(w, z)));
	}

	int q; cin >> q;
	for (int T; q--;) {
		cin >> T;
		for (int i = 1; i <= n; i++) {
			dist1[i] = INF;
		}

		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
		dist1[A] = 0;
		pq.push(make_pair(0, A));
		for (; !pq.empty(); pq.pop()) {
			int dst = pq.top().first;
			int nw = pq.top().second;
			if (dst > dist1[nw]) continue;
			for (pair<int, pair<int, int> > e : adj_all[nw]) {
				int nx = e.first;
				int wt = e.second.first;
				int tp = e.second.second;
				if (dist1[nw] + wt <= T) {
					if (dist1[nx] > dist1[nw] + wt) {
						dist1[nx] = dist1[nw] + wt;
						pq.push(make_pair(dist1[nx], nx));
					}
				} else {
					if (tp == 2 && dist1[nx] > dist1[nw] + wt) {
						dist1[nx] = dist1[nw] + wt;
						pq.push(make_pair(dist1[nx], nx));
					}
				}
			}
		}
		if (dist1[n] >= INF) dist1[n] = -1;
		cout << dist1[n] << endl;
	}

	return 0;
}