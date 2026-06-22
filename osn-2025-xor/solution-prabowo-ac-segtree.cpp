#include <bits/stdc++.h>
using namespace std;

struct Node {
  int size;
  long long sum0;
  long long sum1;

  Node(): size(0), sum0(0), sum1(0) {}
  Node(int _size, long long _sum0, long long _sum1):
    size(_size), sum0(_sum0), sum1(_sum1) {}

  Node operator + (const Node &other) {
    return Node(size + other.size,
        sum0 + other.sum0,
        sum1 + other.sum1 + other.sum0 * size
    );
  }
};

struct Tree {
  int N, H;
  vector<bool> flipped;

  vector<vector<Node>> nodes;

  void build(vector<int> A) {
    N = A.size();
    assert((N & -N) == N); // N must be 2^k
    nodes.resize(N * 2 - 1);

    H = __builtin_ctz(N);
    flipped.assign(H, false);

    for (int i = 0; i < N; ++i) {
      nodes[i + N - 1] = {Node(1, A[i], A[i])};
    }
    for (int i = N - 2; i >= 0; --i) {
      for (int j = 0; j < nodes[i*2 + 1].size(); ++j) {
        nodes[i].push_back(nodes[i*2 + 1][j] + nodes[i*2 + 2][j]);
      }
      for (int j = 0; j < nodes[i*2 + 1].size(); ++j) {
        nodes[i].push_back(nodes[i*2 + 2][j] + nodes[i*2 + 1][j]);
      }
    }
  }

  Node query(int idx, int level, int l, int r, int ll, int rr) {
    if (l >= rr || r <= ll) return Node();
    if (l >= ll && r <= rr) {
      int node = 0;
      for (int i = level; i < H; ++i) {
        node <<= 1;
        if (flipped[i]) {
          node |= 1;
        }
      }
      return nodes[idx][node];
    }

    int lidx = idx * 2 + 1, ridx = idx * 2 + 2;
    if (flipped[level]) swap(lidx, ridx);
    int mid = (l + r) / 2;
    return query(lidx, level + 1, l, mid, ll, rr) +
           query(ridx, level + 1, mid, r, ll, rr);
  }

  Node query(int l, int r) {
    return query(0, 0, 0, N, l, r + 1);
  }

  void flip(int height) {
    int level = H - height - 1;
    flipped[level] = !flipped[level];
  }
} tree;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  tree.build(A);

  while (Q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int X;
      scanf("%d", &X);
      for (int i = 0; (1 << i) < N; ++i) {
        if (X >> i & 1) {
          tree.flip(i);
        }
      }
    } else if (t == 2 || t == 3) {
      int L, R;
      scanf("%d %d", &L, &R);
      Node result = tree.query(L, R);
      if (t == 2) {
        printf("%lld\n", result.sum0);
      } else {
        printf("%lld\n", result.sum1);
      }
    }
  }
  return 0;
}
