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
  vector<vector<long long>> pre0(logN, vector<long long>(N));
  for (int i = 0; i < N; ++i) pre0[0][i] = A[i];

  auto pre1 = pre0;

  for (int k = 1; k < logN; ++k) {
    int len = 1 << (k - 1);
    for (int i = 0; i < N; i += len * 2) {
      for (int j = 0; j < len; ++j) {
        pre0[k][i + j] = pre0[k][i + j + len] = pre0[k - 1][i + j] + pre0[k - 1][i + j + len];
        pre1[k][i + j] = pre1[k - 1][i + j] + pre1[k - 1][i + j + len] + pre0[k - 1][i + j + len] * len;
        pre1[k][i + j + len] = pre1[k - 1][i + j + len] + pre1[k - 1][i + j] + pre0[k - 1][i + j] * len;
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

      int len = 0;
      long long sum0 = 0, sum1 = 0;
      for (int i = 0; i < logN; ++i) {
        if (L + (1 << i) > R) break;
        if (!(L >> i & 1)) continue;
        sum0 += pre0[i][L ^ X];
        sum1 += pre1[i][L ^ X] + pre0[i][L ^ X] * len;
        len += 1 << i;
        L += 1 << i;
      }

      for (int i = logN - 1; i >= 0; --i) {
        if (L + (1 << i) > R) continue;
        sum0 += pre0[i][L ^ X];
        sum1 += pre1[i][L ^ X] + pre0[i][L ^ X] * len;
        len += 1 << i;
        L += 1 << i;
      }

      if (t == 2) {
        printf("%lld\n", sum0);
      } else {
        printf("%lld\n", sum1);
      }
    }
  }
  return 0;
}
