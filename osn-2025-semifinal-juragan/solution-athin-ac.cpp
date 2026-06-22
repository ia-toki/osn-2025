#include <bits/stdc++.h>
using namespace std;

long long n;
long long h[100007], p[100007], a[100007];

int main() {
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) scanf("%lld", &h[i]);
	for (int i = 0; i < n; i++) scanf("%lld", &p[i]);
	
	long long num0 = 0;
	for (int i = 0; i < n; i++) {
		if (p[i] == 0) num0++;
		a[i] = h[i] - p[i];
	}
	
	long long ans = 0;
	long long sum = 0;
	long long last = 0;
	
	for (int i = 0; i < n; i++) {
		sum += a[i];
		if (i - last == num0) {
			sum -= a[last];
			last++;
		}
		while (a[last] < 0 && last <= i) {
			sum -= a[last];
			last++;
		}
		if (sum < 0) {
			sum = 0;
			last = i + 1;
		}
		ans = max(ans, sum);
	}
	
	printf("%lld\n", ans);
}
