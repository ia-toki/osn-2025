#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, q;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	vector<vector<int> > possible;
	for (int a = 1; a <= 5; a++) {
		for (int b = a; b <= 5; b++) {
			for (int c = b; c <= 5; c++) {
				for (int d = c; d <= 5; d++) {
					for (int e = d; e <= 5; e++) {
						vector<int> cr = {a, b, c, d, e};
						while (cr.size() != n) cr.pop_back();
						bool check = true;
						for (int i = 0; i < n; i++) {
							if (cr[i] > n) check = false;
						}
						if (check) {
							bool can = true;
							vector<int> cp = cr;
							while (!cr.empty()) {
								int sz = cr.size();
								vector<int> nx;
								for (int i : cr) if (i != sz) nx.push_back(i);
								cr = nx;
								if (sz == cr.size()) {
									can = false;
									break;
								}
							}
							if (can) possible.push_back(cp);
						}
					}
				}
			}
		}
	}

	cin >> q;
	for (int x, y, tt = 0; tt < q; tt++) {
		cin >> x >> y;
		a[x - 1] = y;

		vector<int> sa = a;
		sort(sa.begin(), sa.end());

		int ans = n + 1;
		for (auto v : possible) {
			int i = 0, j = 0;
			int same_val = 0;
			while (i < n && j < n) {
				if (sa[i] == v[j]) {
					same_val++;
					i++;
					j++;
				} else if (sa[i] > v[j]) {
					j++;
				} else {
					i++;
				}
			}
			ans = min(ans, n - same_val);
		}

		cout << ans << endl;
	}
}