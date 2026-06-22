#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

int main()
{
	int N;
	long long D;
	scanf("%d%lld", &N, &D);
	
	long long A[N + 69];
	for(int i = 1; i <= N; i++)
	{
		scanf("%lld", A + i);
	}
	
	pair<long long, long long> pairs[N + 69];
	for(int i = 1; i <= N; i++)
	{
		long long w, c;
		w = A[i];
		c = 1;
		while(w % 2 == 0)
		{
			w /= 2;
			c *= 2;
		}
		pairs[i] = {w, c};
	}
	sort(pairs + 1, pairs + N + 1, greater<pair<long long, long long>> ());
	
	long long ans, curD;
	ans = 0;
	curD = D;
	for(int i = 1; i <= N; i++)
	{
		long long w, c;
		w = pairs[i].fr;
		c = pairs[i].sc;
		
		long long curC = min(c, curD);
		ans += curC * w;
		curD -= curC;
	}
	printf("%lld\n", ans);
}
