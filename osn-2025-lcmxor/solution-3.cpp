#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  sort(A.begin(), A.end());

  long long ans = 1LL * N * (N - 1) / 2;
  for (int i = 0; i < N; ) {
    int j = i;
    while (j < N && A[j] == A[i]) ++j;
    ans -= 1LL * (j - i) * (j - i - 1) / 2;
    i = j;
  }

  printf("%lld\n", ans);
  return 0;
}
