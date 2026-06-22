#include <bits/stdc++.h>
using namespace std;

const int MX = 200005;
const int INF = 1000000000;
int n, q, a[MX], freq[MX];

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	cin >> q;

	while (q--) {
		int x, y; cin >> x >> y;
		a[x] = y;

		vector<int> freq(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (1 <= a[i] && a[i] <= n) freq[a[i]]++;
		}

		vector<int> dp(n + 1, INF);
		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int s = 0; s <= i; s++) {
				dp[i] = min(dp[i], dp[i - s] + max(0, s - freq[i]));
			}
		}
		cout << dp[n] << endl;
	}

	return 0;
}