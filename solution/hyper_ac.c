#include <stdio.h>
#define int long long
#define MN 1000005

typedef struct {
    int val, num, op3, pre;
} DiaGrp;

int m, op3cnt = 0, sz = 0;
DiaGrp a[MN];

int getVal(int i, int j) {
    return a[i].val + (op3cnt - a[i].op3) * (m - a[i].pre - j + 1);
}

int search(int t) {
    if(sz == 0 || getVal(1, 1) < t) return 0;
    int l = 1, r = sz;
    while(l < r) {
        int m = (l+r+1)/2;
        if(getVal(m, 1) >= t) l = m;
        else r = m-1;
    }
    int ll = 1, rr = a[l].num;
    while(ll < rr) {
        int m = (ll+rr+1)/2;
        if(getVal(l, m) >= t) ll = m;
        else rr = m-1;
    }
    return a[l].pre + ll;
}

signed main() {
    int t;
    scanf("%lld %lld", &t, &m);
    while(t--) {
        int op;
        scanf("%lld", &op);
        if(op == 1) {
            int n, v;
            scanf("%lld %lld", &n, &v);
            int ans = 0;
            while(sz && getVal(sz, 1) < v) {
                ans += a[sz].num;
                --sz;
            }
            if(sz && getVal(sz, a[sz].num) < v) {
                int ops = op3cnt - a[sz].op3;
                int i = m - a[sz].pre + 1 - (v - a[sz].val + ops - 1) / ops;
                ans += a[sz].num - i;
                a[sz].num = i;
            }
            ++sz;
            a[sz].val = v;
            a[sz].num = n;
            a[sz].op3 = op3cnt;
            a[sz].pre = sz == 0 ? 0 : a[sz-1].pre + a[sz-1].num;
            printf("%lld\n", ans);
        } else if(op == 2) {
            int p;
            scanf("%lld", &p);
            printf("%lld\n", search(p) - search(p+1));
        } else if(op == 3) {
            ++op3cnt;
        }
    }
}
