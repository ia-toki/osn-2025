#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  vector<long long> pre0(N + 1), pre1(N + 1);
  for (int i = 1; i <= N; ++i) {
    pre0[i] = pre0[i - 1] + A[i - 1];
    pre1[i] = pre1[i - 1] + 1LL * A[i - 1] * i;
  }

  while (Q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int X;
      scanf("%d", &X);
      // Do nothing
    } else if (t == 2) {
      int L, R;
      scanf("%d %d", &L, &R);
      printf("%lld\n", pre0[R + 1] - pre0[L]);
    } else if (t == 3) {
      int L, R;
      scanf("%d %d", &L, &R);
      ++R;
      printf("%lld\n", pre1[R] - pre1[L] - L * (pre0[R] - pre0[L]));
    }
  }
  return 0;
}
