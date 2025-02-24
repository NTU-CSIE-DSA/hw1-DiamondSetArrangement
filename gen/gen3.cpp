#include <stdio.h>
#include <vector>
#include <assert.h>
#include "jngen.h"
#define ll long long
#define MAXN 1000005
ll max(ll a, ll b) {
	return a > b ? a : b;
}
ll min(ll a, ll b) {
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

void process(int type, int n, ll pv) {
    if(type == 1) {
		ll v = pv, ans = 0;
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
        sz++;
        prevalue[sz] = v;
        pre_2_operations[sz] = operation_2_count;
        accu_elements[sz] = sz == 1 ? n : accu_elements[sz - 1] + n;
    }
    else if(type == 2) {
        ll p = pv;
        bsearch(p), bsearch(p - 1);
    }
    else {
        operation_2_count++;
    }
}

int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	parseArgs(argc, argv);

	int range_t = getOpt(0), range_n = getOpt(1);
	ll range_m = getOpt(2);
	ll range_v = range_m * range_t;
	ll range_p = 2 * range_m * range_t;
	t = range_t;
	m = rnd.next((ll)range_n * range_t, range_m);
	int opt = getOpt(3);

    std::vector<int> container;
	
    container.push_back(10);
    for(int i = 0; i < 10; i++) {
        if(opt & 1) container.push_back(1);
        if(opt & 2) container.push_back(2);
        if(opt & 4) container.push_back(3);
    }

	printf("%d %lld\n", t, m);

    ll pre = range_v * 0.8 * rnd.next(0.95, 1.0);
	while(t > 0) {
        int spec = 0;
        int type = rnd.choice(container);
		if(type == 10) {
            int u = max(t * 0.3, 1);
            int total_times = u * rnd.next(0.9, 1.1);
			int n = range_n * rnd.next(0.95, 1.0);
			if(rnd.next(1, 10) == 1) {
                pre = max(pre * rnd.next(0.95, 1.0), 1);
            }
            for(int i = 0; i < total_times; i++) {
                process(1, n, pre);
			    printf("1 %d %lld\n", n, pre);
            }
            t -= total_times;
            if(opt & 2) type = 2;
            else type = 1;
            spec = 1;
		}
        if(type == 2 && t > 0) {
			ll p;
			if(sz == 0) {
				p = rnd.next(1LL, range_p);
			}
			else {
				p = pre;
			}
			process(2, -1, p);
			printf("%d %lld\n", 2, p);
            t--;
            type = 1;
		}
        if(type == 1 && t > 0) {
            int n = range_n * rnd.next(0.95, 1.0);
            if(spec && sz > 0) {
                ll num = min(get_value(1, 1) + 1, range_v);
                process(1, n, num);
                printf("1 %d %lld\n", n, num);
            }
            else {
                pre = max(min(pre * rnd.next(0.95, 1.0), range_v), 1);
                process(1, n, pre);
                printf("1 %d %lld\n", n, pre);
            }
            t--;
		}
		
		if(type == 3 && t > 0) {
			process(3, -1, -1);
			printf("3\n");
            t--;
		}
	}
}