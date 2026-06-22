#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  auto build = [&](vector<long long> &pre0, vector<long long> &pre1) {
    pre0.resize(N + 1), pre1.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
      pre0[i] = pre0[i - 1] + A[i - 1];
      pre1[i] = pre1[i - 1] + 1LL * A[i - 1] * i;
    }
  };

  vector<long long> pre0, pre1;

  int x = 0;
  while (Q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int X;
      scanf("%d", &X);
      x ^= X;
    } else if (t == 2 || t == 3) {
      if (pre0.empty()) {
        for (int i = 0; i < N; ++i) {
          if (i < (i ^ x)) swap(A[i], A[i ^ x]);
        }
        build(pre0, pre1);
      }

      int L, R;
      scanf("%d %d", &L, &R);
      ++R;

      if (t == 2) {
        printf("%lld\n", pre0[R] - pre0[L]);
      } else {
        printf("%lld\n", pre1[R] - pre1[L] - L * (pre0[R] - pre0[L]));
      }
    }
  }
  return 0;
}
