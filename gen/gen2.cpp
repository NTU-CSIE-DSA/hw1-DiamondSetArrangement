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
    if(opt & 2) container.push_back(2);
    if(opt & 4) container.push_back(3);

	printf("%d %lld\n", t, m);
	for(int i = 1; i <= t - 3; i++) {
		
		int r = rnd.next(1, t / 50);
        int type;
        if(r <= 50) {
			if((opt & 2) && (opt & 4)) {
				if(rnd.next(1, 3) == 1) type = 2;
				else type = 3;
			}
			else type = rnd.choice(container);
        }
        else {
            type = 1;
        }
		
		if(type == 1) {
			int n = range_n; ll v;
			if(sz != 0) {
                int same_as_last;
				if(i <= t * 0.9) same_as_last = rnd.next(1, 40);
				else same_as_last = rnd.next(0, 2);
                ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
                if(same_as_last == 0) {
                    // same as last
                    v = get_value(sz, accu_elements[sz] - pre_elements) + 1;
                }
				else if(same_as_last == 1) {
					v = get_value(sz, accu_elements[sz] - pre_elements);
				}
                else {
                    v = max(get_value(sz, accu_elements[sz] - pre_elements) / 100LL * rnd.next(98LL, 100LL), 1LL);
                }
			}
			else {
				v = rnd.next((ll)(range_v * 0.45), (ll)(range_v * 0.5));
			}
			process(1, n, v);
			printf("1 %d %lld\n", n, v);
		}
		else if(type == 2) {
			ll p;
			if(sz == 0) {
				p = rnd.next(1LL, range_p);
			}
			else {
				int out_of_range = rnd.next(1, 10);
				if(out_of_range == 1) {
					p = get_value(1, 1) + 1;
				}
				else if(out_of_range == 10) {
					ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
					p = max(get_value(sz, accu_elements[sz] - pre_elements) - rnd.next(1, 10), 1);
				}
				else {
					int tuple_pos = max(rnd.next(1, 100) * sz / 100, 1);
					ll pre_elements = tuple_pos == 1 ? 0 : accu_elements[tuple_pos - 1]; 
					p = get_value(tuple_pos, max((accu_elements[tuple_pos] - pre_elements) / 100LL * rnd.next(1LL, 100LL), 1LL));
				}
			}
			process(2, -1, p);
			printf("%d %lld\n", 2, p);
		}
		else {
			process(3, -1, -1);
			printf("3\n");
		}
	}
	if(opt & 4) printf("3\n");
	else printf("2 100\n");
	if(sz) {
		ll pre_elements = sz == 1 ? 0 : accu_elements[sz - 1];
		printf("1 5 %lld\n", get_value(sz, accu_elements[sz] - pre_elements) + 1);
	}
	else {
		printf("1 5 %lld\n", 1);
	}
	if(sz) {
		printf("1 5 %lld\n", get_value(1, 1));
	}
	else {
		printf("1 5 %lld\n", range_v);
	}
}