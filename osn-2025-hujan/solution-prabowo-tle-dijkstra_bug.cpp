#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int u, const vector<vector<pair<int, int>>> &adj) {
  const int INF = 1000000005;

  int n = adj.size();
  vector<int> dist(n, INF);

  priority_queue<pair<int, int>> pq;
  pq.emplace(0, u);
  dist[u] = 0;
  while (!pq.empty()) {
    int u, d;
    tie(d, u) = pq.top();
    d = -d;
    pq.pop();

    // Commenting this should cause TLE
    // if (d > dist[u]) continue;

    for (auto [v, w] : adj[u]) {
      int nd = d + w;
      if (nd < dist[v]) {
        dist[v] = nd;
        pq.emplace(-nd, v);
      }
    }
  }

  for (int &d : dist) {
    if (d == INF) d = -1;
  }

  return dist;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<pair<int, int>>> adjRain(N), adjAll(N);
  for (int i = 0; i < M; ++i) {
    int U, V, W, Z;
    scanf("%d %d %d %d", &U, &V, &W, &Z);
    --U, --V;

    adjAll[U].emplace_back(V, W);
    adjAll[V].emplace_back(U, W);
    if (Z == 2) {
      adjRain[U].emplace_back(V, W);
      adjRain[V].emplace_back(U, W);
    }
  }

  vector<int> distAll = dijkstra(0, adjAll);
  vector<int> distRain = dijkstra(N - 1, adjRain);

  vector<pair<int, int>> rains;
  rains.emplace_back(-1, -1);
  for (int i = 0; i < N; ++i) {
    if (distAll[i] == -1 || distRain[i] == -1) continue;
    rains.emplace_back(distAll[i], distAll[i] + distRain[i]);
  }
  sort(rains.begin(), rains.end());
  for (int i = 2; i < rains.size(); ++i) {
    rains[i].second = min(rains[i].second, rains[i - 1].second);
  }

  int Q;
  scanf("%d", &Q);
  while (Q--) {
    int T;
    scanf("%d", &T);
    int idx = upper_bound(rains.begin(), rains.end(), pair<int, int>(T, 2e9)) - rains.begin() - 1;
    printf("%d\n", rains[idx].second);
  }

  return 0;
}
