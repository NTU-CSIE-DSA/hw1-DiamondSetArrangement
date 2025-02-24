#include <stdio.h>
#include <assert.h>
#define ll long long
#define MAXN 1000005
inline ll max(ll a, ll b) {
	return a > b ? a : b;
}
inline ll min(ll a, ll b) {
	return a < b ? a : b;
}

ll prevalue[MAXN], accu_elements[MAXN], m;
int pre_2_operations[MAXN], t, operation_2_count = 0, sz = 0;

ll get_value(int array_pos, int tuple_pos) {
	int op = operation_2_count - pre_2_operations[array_pos];
	ll pre_elements = array_pos == 1 ? 0 : accu_elements[array_pos - 1];
	ll ret = prevalue[array_pos] + op * (m - (pre_elements + tuple_pos) + 1);
	return ret;
}

ll bsearch(ll target) {
	int l = 1, r = sz, best = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		ll pre_elements = mid == 1 ? 0 : accu_elements[mid - 1];
		if(target >= get_value(mid, accu_elements[mid] - pre_elements)) {
			best = mid;
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	if(best == -1) return accu_elements[sz] + 1;
	else {
		int op = operation_2_count - pre_2_operations[best];
		ll pre_elements = best == 1 ? 0 : accu_elements[best - 1];
		if(op == 0) {
			return pre_elements + 1;
		}
		ll c = (target - prevalue[best]) / op;
		ll index = m - c + 1;
		
		return max(index, pre_elements + 1);
	}
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
					int op = operation_2_count - pre_2_operations[sz];
					ll c = (v - prevalue[sz]) / op;
					ll index = (op * c == v - prevalue[sz]) ? m - c + 1 : m - c;
					ans += accu_elements[sz] - index;
					accu_elements[sz] = index;
				}
			}
			printf("%lld\n", ans);
			sz++;
			prevalue[sz] = v;
			pre_2_operations[sz] = operation_2_count;
			accu_elements[sz] = sz == 1 ? n : accu_elements[sz - 1] + n;
		}
		else if(type == 3) {
			operation_2_count++;
		}
		else {
			ll p;
			assert(scanf("%lld", &p) == 1);
			ll start = bsearch(p), end = bsearch(p - 1);
			printf("%lld\n", end - start);
		}
	}
}