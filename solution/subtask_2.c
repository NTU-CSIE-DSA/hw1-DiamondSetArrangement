#include <stdio.h>
#include <assert.h>
#define MAXN 10000005
#define ll long long
ll init_value[MAXN];
int pre_ops[MAXN], ops = 0, sz = 0, m;

int bsearch(ll p) {
    int l = 1, r = sz, best = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(init_value[mid] + (ll)(ops - pre_ops[mid]) * (m - mid + 1) <= p) {
            best = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    if(best == -1) {
        return sz + 1;
    }
    else {
        return best;
    }
}

int main() {
    int t;
    assert(scanf("%d%d", &t, &m) == 2);

    while(t--) {
        int type;
        assert(scanf("%d", &type) == 1);
        if(type == 1) {
            int n, ans = 0; ll v;
            assert(scanf("%d%lld", &n, &v) == 2);
            while(sz > 0 && init_value[sz] + (ll)(ops - pre_ops[sz]) * (m - sz + 1) < v) {
                ans++;
                sz--;
            }
            for(int i = 0; i < n; i++) {
                sz++;
                init_value[sz] = v;
                pre_ops[sz] = ops;
            }
            printf("%d\n", ans);
        }
        else if(type == 2) {
            ll p;
            assert(scanf("%lld", &p) == 1);
            printf("%d\n", bsearch(p - 1) - bsearch(p));
        }
        else {
            ops++;
        }
    }
}