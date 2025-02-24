#include <stdio.h>
#include <assert.h>
#define ll long long
#define MAXN 1000005

ll prevalue[MAXN], accu_elements[MAXN], m;
int pre_3_operations[MAXN], t, operation_3_count = 0, sz = 0;

ll get_value(int array_pos, int tuple_pos) {
	int op = operation_3_count - pre_3_operations[sz];
	ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
	ll ret = prevalue[array_pos] + op * (m - (pre_elements + tuple_pos) + 1);
	return ret;
}

int main() {
	
	assert(scanf("%d%lld", &t, &m) == 2);
	while(t--) {
		int type;
		assert(scanf("%d", &type) == 1);
		if(type == 1) {
			int n; ll v, ans = 0;
			assert(scanf("%d%lld", &n, &v) == 2);
			while(sz > 0 && get_value(sz, 1) < v) {
				ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
				ans += accu_elements[sz] - pre_elements;
				sz--;
			}
			if(sz > 0) {
				ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
				if(get_value(sz, accu_elements[sz] - pre_elements) < v) {
					int op = operation_3_count - pre_3_operations[sz];
					ll c = (v - prevalue[sz]) / op;
					ll index = (op * c == v - prevalue[sz]) ? m - c + 1 : m - c;
					ans += accu_elements[sz] - index;
					accu_elements[sz] = index;
				}
			}
			printf("%lld\n", ans);
			sz++;
			prevalue[sz] = v;
			pre_3_operations[sz] = operation_3_count;
			accu_elements[sz] = sz == 1 ? n : accu_elements[sz - 1] + n;
		}
        else if(type == 2) {
            ll p;
            assert(scanf("%lld", &p) == 1);
        }
		else {
			operation_3_count++;
		}
	}
}