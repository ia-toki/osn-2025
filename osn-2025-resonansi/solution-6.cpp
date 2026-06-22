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
	
	multiset<pair<int, int> > ms;
	for (int i = 1; i <= n; i++) if (freq[i] > 0) {
		int lf = max(i - freq[i] + 1, 1), rg = i;
		ms.insert(make_pair(lf, 1));
		ms.insert(make_pair(rg + 1, -1));
	}

	cin >> q;
	for (int x, y; q--;) {
		cin >> x >> y; x--;
		int old = min(a[x], n + 1), left = max(old - freq[old] + 1, 1);
		if (old <= n && 1 <= left && left <= n) {
			auto it = ms.find(make_pair(left, 1));
			if (it != ms.end()) ms.erase(it);
		}
		freq[old]--;
		left = max(old - freq[old] + 1, 1);
		if (old <= n && freq[old] > 0) {
			if (1 <= left && left <= n) ms.insert(make_pair(left, 1));
		} else if (old <= n && freq[old] == 0) {
			auto it = ms.find(make_pair(old + 1, -1));
			if (it != ms.end()) ms.erase(it); // erase interval entirely
		}

		int nw = min(y, n + 1);
		left = max(nw - freq[nw] + 1, 1);
		if (nw <= n && freq[nw] > 0) {
			if (1 <= left && left <= n) {
				auto it = ms.find(make_pair(left, 1));
				if (it != ms.end()) ms.erase(it);
			}
		}
		freq[nw]++; 
		left = max(nw - freq[nw] + 1, 1);
		if (nw <= n) {
			if (1 <= left && left <= n) ms.insert(make_pair(left, 1));
			if (freq[nw] == 1) {
				ms.insert(make_pair(nw + 1, -1)); // add new interval
			}
		}
		a[x] = nw;
		
		// for (auto i : ms) cout << "(" << i.first << ", " << i.second << ") "; cout << endl;

		int lastRight = 0, cnt = 0, ans = 0;
		for (auto i : ms) {
			cnt += i.second;
			if (cnt == 1 && i.second == 1) {
				// detected range of 0s
				ans += i.first - 1 - lastRight;
			}
			if (cnt == 0 && i.second == -1) {
				// end of a set of intersecting intervals
				lastRight = i.first - 1;
			}
		}
		if (cnt == 0) ans += n - lastRight;
		cout << ans << endl;
	}

	return 0;
}