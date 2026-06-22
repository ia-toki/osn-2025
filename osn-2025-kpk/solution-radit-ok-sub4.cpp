#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

bitset<1000005> is_prime;
vector<int> primes;

const int N = 1e5;
const int MOD = 1e9 + 7;
int ar[N + 5];
int n;

LL dp[N][100];

void sieve(){
	is_prime.set();
	is_prime[0] = is_prime[1] = false;
	for(int i = 2;i <= 1000000; ++i){
		if(!is_prime[i]) continue;
		primes.push_back(i);
		if(i <= 2000){
			for(int j = i * i;j <= 1000000; j += i){
				is_prime[j] = false;
			}
		}
	}
}

vector<int> factors[N + 5];

LL rek(int pos, int idx_factor_before){
	if(pos == n) return 1;

	LL &ret = dp[pos][idx_factor_before];
	if(ret == -1){
		ret = 0;
		int cur_x = factors[max(0, pos - 1)][idx_factor_before];
		int num_factor = (int) factors[pos].size();
		for(int j = 0;j < num_factor; ++j){
			int cur_factor = factors[pos][j];
			if(lcm(1LL * cur_x, 1LL * cur_factor) == 1LL * ar[pos]) {
				ret += rek(pos + 1, j);
				if(ret >= MOD) ret -= MOD;
			}
		}
	}
	return ret;
}


int main(){
	sieve();
	scanf("%d", &n);
	for(int i = 0;i < n; ++i){
		scanf("%d", &ar[i]);
		int akar = sqrt(ar[i]);
		for(int j = 1;j <= akar; ++j){
			if(ar[i] % j == 0){
				factors[i].push_back(j);
				if(j * j != ar[i]) factors[i].push_back(ar[i] / j);
			}
		}
		sort(factors[i].begin(), factors[i].end());
	}

	memset(dp, -1, sizeof dp);

	int ans = 0;
	int siz = factors[0].size();
	for(int i = 0;i < siz; ++i){
		ans += int(rek(0, i));
		if(ans >= MOD) ans -= MOD;
	}

	printf("%d\n", ans);
	return 0;
}
