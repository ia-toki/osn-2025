#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_N = 2e5;
const int MAX_K = 2e5;

int main(){
    int n, k;
    scanf("%d%d", &n, &k);

    // ignore the array, since already know from the constraints

    vector<int> v;
    v.push_back(1);
    for(int i = 0;i < k; ++i){
        vector<int> lef;
        vector<int> rig;
        for(int x: v){
            int now = x << 1;
            int num_lef = min(now, n);
            int num_rig = now - num_lef;
            lef.push_back(num_lef);
            rig.push_back(num_rig);
        }
        v = lef;
        v.insert(v.end(), rig.begin(), rig.end());
    }

    if (v.size() > MAX_K) v.resize(MAX_K);
    for(int x: v){
        printf("%d\n", x);
    } 
    return 0;
}
