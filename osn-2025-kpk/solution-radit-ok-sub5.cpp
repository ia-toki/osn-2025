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

map<int, int> rev[MAX_K + 5];
vector<int> factors[MAX_K + 5];
vector<pii> factor_primes[MAX_K + 5];

int dp[N][250];

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

void generate_factor(int x, int idx, int cur){	
	if(idx == factor_primes[x].size()) {
		factors[x].push_back(cur);
		return;
	}
	int cur_next = cur;

	pii &now = factor_primes[x][idx];
	int cur_kali = now.fi;
	cur_next *= cur_kali;
	while(cur_kali > 0){
		generate_factor(x, idx + 1, cur_next);
		cur_next /= now.se;
		cur_kali /= now.se;
	}
}

void gen_factor(int x){
	int now = x;
	int idx_prime = 0;
	while(!is_prime[now] && now != 1){
		int prim = primes[idx_prime];
		if(now % prim == 0){
			int cnt = 0;

			int kali = 1;
			while(now % prim == 0){
				cnt++;
				now /= prim;
				kali *= prim;
			}
			factor_primes[x].push_back(mp(kali, prim));
		}
		idx_prime++;

	}
	if(now != 1){
		factor_primes[x].push_back(mp(now, now));
	}

	generate_factor(x, 0, 1);
	sort(factors[x].begin(), factors[x].end());
	for(int i = 0;i < factors[x].size(); ++i){
		rev[x][factors[x][i]] = i;
	}

}


int rek(int pos, int idx_factor_before){
	if(pos == n) return 1;

	int &ret = dp[pos][idx_factor_before];
	if(ret == -1){
		ret = 0;
		int cur_x = factors[ar[max(0, pos - 1)]][idx_factor_before];
		if(ar[pos] % cur_x != 0) return ret;

		int bagi = ar[pos] / cur_x;
		int cur_min_mult = 1;
		for(auto& [val, prim]: factor_primes[ar[pos]]){
			if(gcd(bagi, val) != 1) cur_min_mult *= val;
		}

		int hasil = ar[pos] / cur_min_mult;

		// fprintf(stderr, "REK %d %d %d %d %d\n", pos, idx_factor_before, cur_x, cur_min_mult, hasil);
		if(factors[hasil].size() == 0) gen_factor(hasil);
		for(int i = 0;i < factors[hasil].size(); ++i){
			int next_val = factors[hasil][i] * cur_min_mult;
			ret += rek(pos + 1, rev[ar[pos]][next_val]);
			if(ret >= MOD) ret -= MOD;
		}
	}
	return ret;
}



int main(){
	sieve();
	scanf("%d", &n);
	factors[1].push_back(1);
	for(int i = 0;i < n; ++i){
		scanf("%d", &ar[i]);
		int x = ar[i];
		if(factor_primes[x].size() > 0 || x == 1) continue;
		gen_factor(x);
	}
		

	memset(dp, -1, sizeof dp);

	int ans = 0;

	int siz = factors[ar[0]].size();
	for(int i = 0;i < siz; ++i){
		ans += rek(0, i);
		if(ans >= MOD) ans -= MOD;
	}
	printf("%d\n", ans);
	return 0;
}
