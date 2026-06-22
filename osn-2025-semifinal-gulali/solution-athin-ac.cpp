#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> PII;

int n;
long long k, a;
priority_queue<PII> pq;

int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a);
		long long tmp = 1;
		while (a % 2 == 0) {
			a /= 2;
			tmp *= 2;
		}
		pq.push(PII(a, tmp));
	}
	
	long long ans = 0;
	while (k > 0 && !pq.empty()) {
		long long val = pq.top().first;
		long long num = pq.top().second;
		pq.pop();
		if (num < k) {
			ans += num * val;
			k -= num;
		} else {
			ans += k * val;
			k = 0;
		}
	}
	printf("%lld\n", ans);
}