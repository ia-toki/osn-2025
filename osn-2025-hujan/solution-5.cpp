#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MX = 1e5 + 5;
const int INF = 2e9 + 69;

vector<pair<int, int> > adj_all[MX];
int dist1[MX], dist2[MX];

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m, A, B;
	cin >> n >> m;
	A = 1; B = n;

	for (int i = 1; i <= n; i++) {
		dist1[i] = INF;
		dist2[i] = INF;
	}
	dist2[n] = 0;
	for (int u, v, w, z, i = 0; i < m; i++) {
		cin >> u >> v >> w >> z;
		adj_all[u].push_back(make_pair(v, w));
		adj_all[v].push_back(make_pair(u, w));
		if (z == 2) {
			dist2[u] = min(dist2[u], w);
		}
	}

	// Dijkstra source A graph adj_all
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
	dist1[A] = 0;
	pq.push(make_pair(0, A));
	for (; !pq.empty(); pq.pop()) {
		int dst = pq.top().first;
		int nw = pq.top().second;
		if (dst > dist1[nw]) continue;
		for (pair<int, int> e : adj_all[nw]) {
			int nx = e.first;
			int wt = e.second;
			if (dist1[nx] > dist1[nw] + wt) {
				dist1[nx] = dist1[nw] + wt;
				pq.push(make_pair(dist1[nx], nx));
			}
		}
	}

	vector<pair<int, int> > arr;
	for (int i = 1; i <= n; i++) {
		if (dist1[i] >= INF || dist2[i] >= INF) continue;
		arr.push_back(make_pair(dist1[i], dist1[i] + dist2[i]));
	}
	sort(arr.begin(), arr.end());

	int q;
	cin >> q;
	vector<pair<int, int> > queries(q);
	for (int i = 0; i < q; i++) {
		cin >> queries[i].first;
		queries[i].second = i;
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(q);

	int j = 0; int res = INF;
	for (int i = 0; i < q; i++) {
		for (; j < (int)arr.size() && arr[j].first <= queries[i].first; j++) {
			res = min(res, arr[j].second);
		}
		ans[queries[i].second] = (res >= INF ? -1 : res);
	}

	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}