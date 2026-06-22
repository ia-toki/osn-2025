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
	// fprintf(stderr, "rek %d %d %d\n", pos, bit, prim);
	if(pos == n) return 1;

	int &ret = dp[pos][bit];
	if(ret == -1){
		ret = 0;
		int next_bit = 0;
		for(int i = 0;i < factors[pos].size() && next_bit == 0; ++i){
			if(factors[pos][i].fi == prim) next_bit = factors[pos][i].se;
		}
		if(bit > next_bit) return ret;
		if(bit < next_bit) return ret = rek(pos + 1, next_bit, prim);

		// bit == next_bit
		for(int i = 0;i <= bit; ++i){
			ret += rek(pos + 1, i, prim);
			if(ret >= MOD) ret -= MOD;
		}
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
			exists[prim] = true;
		}
		idx_prime++;
	}
	if(now != 1){
		factors[idx].push_back(mp(now, 1));
		exists[now] = true;
	}
	num_factors[x] = factors[idx];
	// sort(factors[idx].begin(), factors[idx].end());
}

int main(){
	sieve();
	scanf("%d", &n);
	for(int i = 0;i < n; ++i){
		scanf("%d", &ar[i]);
		gen_factors(i);
	}

	LL ans = 1;
	for(int prim: primes){
		if(exists[prim]){
			LL kali = 1, cnt = 0;
			while(kali <= 1LL * MAX_K){
				kali *= prim;
				cnt++;
			}

			for(int i = 0;i < n; ++i){
				for(int j = 0;j <= cnt; ++j) dp[i][j] = -1;
			}
			int num = 0;
			for(int i = 0;i < factors[0].size() && num == 0; ++i){
				if(factors[0][i].fi == prim) num = factors[0][i].se;
			}

			int ret = 0;
			for(int i = 0;i <= num; ++i){
				ret += rek(0, i, prim);
				if(ret >= MOD) ret -= MOD;
			}
			ans *= ret;
			ans %= MOD;
			// fprintf(stderr, "AFTER %d: %lld\n", prim, ans);		
		}
	}
	printf("%lld\n", ans);
	return 0;
}
