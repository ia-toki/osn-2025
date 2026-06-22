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

		// min change to cover interval [i...j]
		vector<vector<int> > dp(n + 2, vector<int>(n + 2, INF));
		for (int t = 0; t <= n; t++) dp[t + 1][t] = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = i; j >= 1; j--) {
				int best = INF;
				int maxX = i - j + 1;
				for (int x = 1; x <= maxX; x++) {
					int prev = dp[j][i - x];
					if (prev < INF) {
						int cost = max(0, x - freq[i]);
						best = min(best, prev + cost);
					}
				}
				dp[j][i] = best;
			}
		}

		cout << dp[1][n] << endl;
	}

	return 0;
}