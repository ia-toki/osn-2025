#include <bits/stdc++.h>
using namespace std;

const int MX = 200005;
int n, q, a[MX], freq[MX];

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		freq[min(a[i], n + 1)]++;
	}

	vector<int> pref(n + 2, 0);
	for (int i = 1; i <= n; i++) if (freq[i] > 0) {
		int lf = max(i - freq[i] + 1, 1), rg = i;
		pref[lf]++; pref[rg + 1]--;
	}
	for (int i = 1; i <= n + 1; i++) {
		pref[i] += pref[i - 1];
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (pref[i] == 0) {
			ans++;
		}
	}

	cin >> q;
	for (int x, y; q--;) {
		cin >> x >> y; x--;
		int old = min(a[x], n + 1), left = max(old - freq[old] + 1, 0);
		if (old <= n) {
			pref[left]--;
			if (1 <= left && left <= n && pref[left] == 0) ans++;
		}
		freq[old]--;

		int nw = min(y, n + 1);
		freq[nw]++; left = max(nw - freq[nw] + 1, 0);
		if (nw <= n) {
			bool wasZero = (pref[left] == 0);
			pref[left]++;
			if (1 <= left && left <= n && wasZero && pref[left] == 1) ans--;
		}
		a[x] = nw;

		cout << ans << endl;
	}

	return 0;
}