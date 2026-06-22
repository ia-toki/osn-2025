#include <bits/stdc++.h>
using namespace std;

#define pb push_back

using ll = long long;

template<int MOD>
class Mint 
{
public:
    int v;
    Mint() : v(0) {}
    Mint(int64_t _v) {
        v = int((-MOD < _v && _v < MOD) ? (_v) : (_v % MOD));
        if (v < 0) v += MOD;
    }
 
    friend bool operator==(const Mint &a, const Mint &b) {return a.v == b.v;}
    friend bool operator!=(const Mint &a, const Mint &b) {return a.v != b.v;}
    friend bool operator< (const Mint &a, const Mint &b) {return a.v <  b.v;}
    friend bool operator<=(const Mint &a, const Mint &b) {return a.v <= b.v;}
    friend bool operator> (const Mint &a, const Mint &b) {return a.v >  b.v;}
    friend bool operator>=(const Mint &a, const Mint &b) {return a.v >= b.v;}
 
    Mint &operator+=(const Mint &a) {if ((v += a.v) >= MOD) v -= MOD; return *this;}
    Mint &operator-=(const Mint &a) {if ((v -= a.v) < 0) v += MOD; return *this;}
    Mint &operator*=(const Mint &a) {v = int(1ll * v * a.v % MOD); return *this;}
    Mint &operator/=(const Mint &a) {return (*this) *= inverse(a);}
 
    friend Mint fpow(Mint a, long long x) {
        Mint res = 1;
        for (; x; x /= 2, a *= a) if (x & 1) res *= a;
        return res;
    }
    friend Mint inverse(Mint a) {return fpow(a, MOD - 2);}
 
    Mint operator+ () const {return Mint( v);}
    Mint operator- () const {return Mint(-v);}
    Mint operator++() const {return *this += 1;}
    Mint operator--() const {return *this -= 1;}
 
    friend Mint operator+(Mint a, const Mint &b) {return a += b;}
    friend Mint operator-(Mint a, const Mint &b) {return a -= b;}
    friend Mint operator*(Mint a, const Mint &b) {return a *= b;}
    friend Mint operator/(Mint a, const Mint &b) {return a /= b;}
 
    friend istream &operator>>(istream &is, Mint &v) {return is >> v.v;}
    friend ostream &operator<<(ostream &os, const Mint &v) {return os << v.v;}
};
const int ModA = 1e9 + 7;
using MintA    = Mint<ModA>;

const int MAXN = 1e5 + 1;
const int MAXM = 5001;
const int LG = 13;

bitset<MAXM> prime;

int N, A[MAXN], P[MAXN];

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

    for (int i = 2; i < MAXM; ++i)
        prime[i] = true;
    for (int i = 2; i*i < MAXM; ++i) if (prime[i]) {
        for (int j = i*i; j < MAXM; j += i) 
            prime[j] = false;
    }

	for (int i = 0; i < N; ++i)
		cin >> A[i];

    MintA Z = 1;
    for (int p = 2; p < MAXM; ++p) if (prime[p])
    {
        memset(P, 0, sizeof(P));

        for (int i = 0; i < N; ++i) {
            while (A[i] % p == 0) {
                P[i]++;
                A[i] /= p;
            }
        }

        int max_pwr = *max_element(P, P + MAXN);
        if (max_pwr == 0) {
            continue;
        }

        MintA val = 1, sum = P[0] + 1;
        for (int i = 1; i < N; ++i)
        {
            if (P[i-1] == P[i]) {
                MintA tmp = sum;
                sum += val * P[i];
                val = tmp; 
            } else if (P[i-1] < P[i]) {
                sum += val * P[i-1];
                val = 0;
            } else {
                sum = val * (P[i]+1);
            }
        }

        Z *= P[N-1] * val + sum;
    }


	cout << Z << '\n';;
	return 0;
}
