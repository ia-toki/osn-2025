#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  while (Q--) {
    int t;
    scanf("%d", &t);

    if (t == 1) {
      int X;
      scanf("%d", &X);
      for (int i = 0; i < N; ++i) {
        if (i < (i ^ X)) {
          swap(A[i], A[i ^ X]);
        }
      }
    } else if (t == 2) {
      int L, R;
      scanf("%d %d", &L, &R);
      
      long long sum = 0;
      for (int i = L; i <= R; ++i) {
        sum += A[i];
      }
      printf("%lld\n", sum);
    } else if (t == 3) {
      int L, R;
      scanf("%d %d", &L, &R);
      
      long long sum = 0;
      for (int i = L; i <= R; ++i) {
        sum += 1LL * A[i] * (i - L + 1);
      }
      printf("%lld\n", sum);
    }
  }
  return 0;
}
