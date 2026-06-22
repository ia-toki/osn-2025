#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (lcm(1LL * A[i], 1LL * A[j]) < (A[i] ^ A[j])) {
        ++ans;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
