#include <stdio.h>

#define cal(i, j) dia[i].value + (op3_count - dia[i].op3) * (M - dia[i].pre - j + 1)

typedef struct diamond {
    long long value, cnt, op3, pre;
} Diamond;
int T;
long long M;
long long op3_count = 0, sz = 0;
Diamond dia[1000005];
long long bi_search(long long k) {
    if(sz == 0 || cal(1, 1) < k)
        return 0;
    long long l = 1, r = sz+1, m;
    while(l < r-1) {
        m = ((l+r) >> 1);
        if(cal(m, 1) >= k)
            l = m;
        else
            r = m;
    }
    long long l2 = 1, r2 = dia[l].cnt+1;
    while(l2 < r2-1) {
        m = ((l2+r2) >> 1);
        if(cal(l, m) >= k)
            l2 = m;
        else
            r2 = m;
    }
    return dia[l].pre + l2;

}
int main() {
    scanf("%d%lld", &T, &M);
    while (T--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            long long n;
            long long v;
            long long ans = 0;
            scanf("%lld%lld", &n, &v);
            while (sz > 0 && cal(sz, 1) < v) {
                ans += dia[sz].cnt;
                sz--;
            }
            if (sz > 0 && cal(sz, dia[sz].cnt) < v) {
                long long op = op3_count - dia[sz].op3;
                long long idx = M - dia[sz].pre + 1 - (v - dia[sz].value + op - 1) / op;
                ans += dia[sz].cnt - idx;
                dia[sz].cnt = idx;
            }
            printf("%lld\n", ans);
            sz++;
            dia[sz]={v, n, op3_count, sz == 0 ? 0 : dia[sz - 1].pre + dia[sz - 1].cnt};
        } else if (type == 2) {
            long long p;
            scanf("%lld", &p);
            printf("%lld\n", bi_search(p)-bi_search(p+1));
        } else if (type == 3) {
            op3_count++;
        }
        else{
            return -1;
        }
    }
}