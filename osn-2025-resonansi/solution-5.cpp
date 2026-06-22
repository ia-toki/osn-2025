#include <bits/stdc++.h>
using namespace std;

const int MX = 200005;
const int NEGINF = -1000000000;
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

		vector<int> dp(n + 1, 0), pref(n + 1, 0);
		dp[0] = 0; pref[0] = 0;
		for (int i = 1; i <= n; i++) {
			int fi = freq[i];
			int best = NEGINF;

			int A = min(fi, i);
			for (int s = 1; s <= A; s++)
				best = max(best, dp[i - s] + s);
			if (i - fi >= 1)
				best = max(best, pref[i - fi - 1] + fi);

			if (best == NEGINF) best = dp[i - 1];
			dp[i] = best;
			pref[i] = max(pref[i - 1], dp[i]);
		}

		cout << n - dp[n] << endl;
	}

	return 0;
}