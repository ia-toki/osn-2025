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

  vector<pair<int, int>> cnt;
  for (int i = 0; i < N; ) {
    int j = i;
    while (j < N && A[j] == A[i]) ++j;
    cnt.emplace_back(A[i], j - i);
    i = j;
  }

  long long ans = 0;
  for (int i = 0; i < cnt.size(); ++i) {
    for (int j = i; j < cnt.size(); ++j) {
      if (lcm(cnt[i].first, cnt[j].first) < (cnt[i].first ^ cnt[j].first)) {
        if (i == j) {
          ans += 1LL * cnt[i].second * (cnt[i].second - 1) / 2;
        } else {
          ans += 1LL * cnt[i].second * cnt[j].second;
        }
      }
    }
  }

  printf("%lld\n", ans);
  return 0;
}
