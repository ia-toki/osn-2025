#include <bits/stdc++.h>
using namespace std;

struct Tree {
  int N, H;
  vector<long long> sum;
  vector<bool> flipped;

  void build(vector<int> A) {
    N = A.size();
    assert((N & -N) == N); // N must be 2^k
    sum.resize(N * 2 - 1);

    H = __builtin_ctz(N);
    flipped.assign(H, false);

    for (int i = 0; i < N; ++i) {
      sum[i + N - 1] = A[i];
    }
    for (int i = N - 2; i >= 0; --i) {
      sum[i] = sum[i*2 + 1] + sum[i*2 + 2];
    }
  }

  long long query(int idx, int level, int l, int r, int ll, int rr) {
    if (l >= rr || r <= ll) return 0LL;
    if (l >= ll && r <= rr) return sum[idx];

    int lidx = idx * 2 + 1, ridx = idx * 2 + 2;
    if (flipped[level]) swap(lidx, ridx);
    int mid = (l + r) / 2;
    return query(lidx, level + 1, l, mid, ll, rr) +
           query(ridx, level + 1, mid, r, ll, rr);
  }

  long long query(int l, int r) {
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
      printf("%lld\n", tree.query(L, R));
    }
  }
  return 0;
}
