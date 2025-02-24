#include <stdio.h>
#include <assert.h>
#define MAXN 10005
int stk[MAXN], sz = 0;

int main() {
    int t, m;
    assert(scanf("%d%d", &t, &m) == 2);

    while(t--) {
        int type;
        assert(scanf("%d", &type) == 1);
        if(type == 1) {
            int n, v, ans = 0;
            assert(scanf("%d%d", &n, &v) == 2);
            while(sz > 0 && stk[sz] < v) {
                ans++;
                sz--;
            }
            for(int i = 0; i < n; i++) {
                stk[++sz] = v;
            }
            printf("%d\n", ans);
        }
        else if(type == 2) {
            int p, ans = 0;
            assert(scanf("%d", &p) == 1);
            for(int i = 1; i <= sz; i++) {
                if(stk[i] == p) {
                    ans++;
                }
            }
            printf("%d\n", ans);
        }
        else {
            for(int i = 1; i <= sz; i++) {
                stk[i] += m - i + 1;
            }
        }
    }
}