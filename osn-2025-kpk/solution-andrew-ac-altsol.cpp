#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

bitset<1000005> is_prime;
vector<int> primes;

const int N = 1e5;
const int MAX_K = 1e6;
const int MOD = 1e9 + 7;
int ar[N + 5];
int n;

vector<pii> num_factors[MAX_K + 5];
vector<pii> factors[N + 5];
bool exists[MAX_K + 5];
int dp[N][22];

vector<pii> compress[MAX_K + 5];


void sieve(){
	is_prime.set();
	is_prime[0] = is_prime[1] = false;
	for(int i = 2;i <= MAX_K; ++i){
		if(!is_prime[i]) continue;
		primes.push_back(i);
		if(i <= 2000){
			for(int j = i * i;j <= MAX_K; j += i){
				is_prime[j] = false;
			}
		}
	}
}



int rek(int pos, int bit, int prim){
	// fprintf(stderr, "rek %d %d %d\n", compress[prim][pos].fi, bit, prim);
	int &ret = dp[pos][bit];
	if(ret != -1) return dp[pos][bit];

	if(pos == compress[prim].size()) {
		int last_idx = compress[prim][pos - 1].fi;
		if(last_idx != n - 1) return ret = (bit == 0);
		return ret = 1;
	}	

	ret = 0;

	int last_idx = pos == 0 ? -1 : compress[prim][pos - 1].fi;
	int cur_idx = compress[prim][pos].fi;
	int next_bit = compress[prim][pos].se;

	if(cur_idx - last_idx > 1){
		if(bit > 0) return ret;
		return ret = rek(pos + 1, next_bit, prim);
	}

	if(bit > next_bit) return ret;
	if(bit < next_bit) return ret = rek(pos + 1, next_bit, prim);

	// bit == next_bit
	for(int i = 0;i <= next_bit; ++i){
		ret += rek(pos + 1, i, prim);
		if(ret >= MOD) ret -= MOD;
	}
	return ret;
}

void gen_factors(int idx){
	int x = ar[idx];
	if(num_factors[x].size() > 0){
		factors[idx] = num_factors[x];
		return;
	}
	int now = x;

	int idx_prime = 0;	
	while(!is_prime[now] && now != 1){
		int prim = primes[idx_prime];
		if(now % prim == 0){
			int cnt = 0;
			while(now % prim == 0){
				cnt++;
				now /= prim;
			}
			factors[idx].push_back(mp(prim, cnt));
		}
		idx_prime++;
	}
	if(now != 1){
		factors[idx].push_back(mp(now, 1));
	}
	num_factors[x] = factors[idx];
}

void gen_compress(int idx){
	for(pii& factor: factors[idx]){
		compress[factor.fi].push_back(mp(idx, factor.se));
	}
}

int main(){
	sieve();
	scanf("%d", &n);
	for(int i = 0;i < n; ++i){
		scanf("%d", &ar[i]);
		gen_factors(i);
		gen_compress(i);
	}

	LL ans = 1;
	for(int prim: primes){
		if(compress[prim].size() > 0){
			int max_bit = 0;

			int siz = (int) compress[prim].size();
			for(pii& now: compress[prim]) max_bit = max(max_bit, now.se);

			for(int i = 0;i <= siz; ++i){
				for(int j = 0;j <= max_bit; ++j){
					dp[i][j] = -1;
				}
			}

			int num = compress[prim][0].fi == 0 ? compress[prim][0].se : 0;

			int ret = 0;
			for(int i = 0;i <= num; ++i){
				ret += rek(0, i, prim);
				if(ret >= MOD) ret -= MOD;
			}
			ans *= ret;
			ans %= MOD;
			// fprintf(stderr, "AFTER %d: %lld\n", prim, ans);

			if(ans == 0) break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
