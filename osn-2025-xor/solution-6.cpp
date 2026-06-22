#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  vector<long long> pre0(N), pre1(N);
  for (int i = 0; i < N; ++i) {
    pre0[i] = pre1[i] = A[i];
  }
  int logN = __builtin_ctz(N) + 1;

  for (int k = 1; k < logN; ++k) {
    int len = 1 << (k - 1);
    for (int i = 0; i < N; i += len * 2) {
      for (int j = 0; j < len; ++j) {
        long long u = pre1[i + j], v = pre1[i + j + len];
        pre1[i + j] = u + v + pre0[i + j + len] * len;
        pre1[i + j + len] = u + v + pre0[i + j] * len;

        pre0[i + j] = pre0[i + j + len] = pre0[i + j] + pre0[i + j + len];
      }
    }
  }

  int X = 0;
  while (Q--) {
    int t;
    scanf("%d", &t);
    if (t == 1) {
      int x;
      scanf("%d", &x);
      X ^= x;
    } else {
      int L, R;
      scanf("%d %d", &L, &R);
      ++R;

      if (t == 2) {
        printf("%lld\n", pre0[X]);
      } else {
        printf("%lld\n", pre1[X]);
      }
    }
  }
  return 0;
}
