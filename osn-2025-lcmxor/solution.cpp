#include <bits/stdc++.h>
using namespace std;

const int MAXA = 100005;

int main() {
  int N;
  scanf("%d", &N);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  vector<int> cnt(MAXA);
  for (int i = 0; i < N; ++i) {
    ++cnt[A[i]];
  }

  long long ans = 0;
  for (int i = 1; i < MAXA; ++i) {
    for (int j = i; j < MAXA; j += i) {
      if (lcm(i, j) < (i ^ j)) {
        ans += 1LL * cnt[i] * cnt[j];
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
