#include <stdio.h>
#include <assert.h>
#define ll long long
#define MAXN 1000005

ll value[MAXN], cnt[MAXN];

int main() {
    int T, sz = 0; ll M;
    assert(scanf("%d%lld", &T, &M) == 2);

    for(int i = 0; i < T; i++) {
        int type;
        assert(scanf("%d", &type) == 1);
        if(type == 1) {
            int N; ll v, ans = 0;
            assert(scanf("%d%lld", &N, &v));
            while(sz > 0 && v > value[sz]) {
                ans += cnt[sz];
                sz--;
            }
            if(sz > 0 && value[sz] == v) {
                cnt[sz] += N;
            }
            else {
                sz++;
                value[sz] = v;
                cnt[sz] = N;
            }
            printf("%lld\n", ans);
        }
        else if(type == 2) {
            ll p;
            assert(scanf("%lld", &p));
            int l = 1, r = sz, best = -1;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(p == value[mid]) {
                    best = mid;
                    break;
                }
                else if(p > value[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            if(best == -1) {
                printf("0\n");
            }
            else {
                printf("%lld\n", cnt[best]);
            }
        }
        else if(type == 3) {
            
        }
    }
}