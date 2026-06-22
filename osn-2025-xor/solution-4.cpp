#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  int logN = __builtin_ctz(N) + 1;
  vector<long long> pre(N + 1);
  for (int i = 0; i < N; ++i) {
    pre[i + 1] = pre[i] + A[i];
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

      long long sum = 0;
      for (int i = 0; i < logN; ++i) {
        if (L + (1 << i) > R) break;
        if (!(L >> i & 1)) continue;

        int lx = ((L ^ X) >> i) << i;
        sum += pre[lx + (1 << i)] - pre[lx];
        L += 1 << i;
      }

      for (int i = logN - 1; i >= 0; --i) {
        if (L + (1 << i) > R) continue;

        int lx = ((L ^ X) >> i) << i;
        sum += pre[lx + (1 << i)] - pre[lx];
        L += 1 << i;
      }

      printf("%lld\n", sum);
    }
  }
  return 0;
}
