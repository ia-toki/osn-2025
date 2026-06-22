#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_N = 2e5;
const int MAX_K = 2e5;
LL ar[MAX_N + 5];

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0;i < n; ++i){
        scanf("%lld", &ar[i]);
    }

    vector<pii> v;
    v.push_back({0, n - 1});
    for(int i = 0;i < k; ++i){
        vector<pii> lef;
        vector<pii> rig;
        for(pii& x: v){
            int mid = x.fi + ((x.se - x.fi) >> 1);
            lef.push_back(mp(x.fi, mid));
            rig.push_back(mp(min(mid + 1, x.se), x.se));
        }

        v = lef;
        v.insert(v.end(), rig.begin(), rig.end());
    } 

    if(v.size() > MAX_K) v.resize(MAX_K);
    for(pii& x: v){
        int banyak = x.se - x.fi + 1;
        LL total = 0;
        int cnt = n / banyak;
        for(int i = x.fi; i <= x.se; ++i){
            total += ar[i];
        }
        total *= cnt;
        printf("%lld\n", total);
    }

    return 0;
}
