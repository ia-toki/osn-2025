#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2e5;
LL pref[N + 5];
LL ar[N + 5];
int n, k;

LL recurse(LL pos, int pos_index, int idx_left, LL num_left_remaining){

    // fprintf(stderr, "RECURSE %lld %d %d %lld\n", pos, pos_index, idx_left, num_left_remaining);
    if(num_left_remaining >= n){
        return ar[idx_left] * n;    
    }

    LL num_per_idx = 1LL << pos_index;

    if(pos_index == k){
        LL res = ar[idx_left] * num_left_remaining;

        LL num_remaining = 1LL * n - num_left_remaining;
        LL num_idxes = num_remaining / num_per_idx;
        res += (pref[idx_left + num_idxes] - pref[idx_left]) * num_per_idx;
        LL remainder = num_remaining % num_per_idx;
        res += ar[idx_left + num_idxes + 1] * remainder;

        return res;
    }

    bool on = pos & (1LL << pos_index);
    if(on){
        // kanan
        // jangan lupa dikali 2 dulu semuanya
        if(num_left_remaining * 2 > n){
            return recurse(pos, pos_index + 1, idx_left, 2 * num_left_remaining - n);
        }

        LL next_num_per_idx = num_per_idx << 1;
        LL num_remaining = 1LL * n - 2 * num_left_remaining;

        LL num_idxes = num_remaining / next_num_per_idx;
        LL remainder = num_remaining % next_num_per_idx;

        LL idx_next = idx_left + num_idxes + 1;
        LL num_idx_next_remaining = next_num_per_idx - remainder;
        return recurse(pos, pos_index + 1, idx_next, num_idx_next_remaining);
    }   
    else{
        // kiri
        return recurse(pos, pos_index + 1, idx_left, min(num_left_remaining << 1, 1LL * n));
    }
}

LL process(LL pos){
    // starts from index 0 --> like reversing the binary
    return recurse(pos, 0, 1, 1LL);
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= n; ++i){
        scanf("%lld", &ar[i]);
        pref[i] = pref[i - 1] + ar[i];
    }
    LL l = 1;
    LL r = k <= 17 ? (1 << k) : 200000;

    // this is for first 200000 arrays, change if want to be in the input
    l--;
    r--;
    for(LL i = l; i <= r; i++){
        LL total = process(i);
        printf("%lld\n", total);
    }

    return 0;
}
