# [HW1-P4] Diamond Set Arrangement Tutorial

## Solution

### Naive Solution

A simple idea is to **store each diamond individually** in an array.

- For each operation:
  - Directly simulate **removal**, **search**, and **update**.
- However, **this is inefficient**:
  - **Type 1**: Removing elements and inserting N new elements is **slow**.
  - **Type 2**: Searching through all elements is **slow**.
  - **Type 3**: Updating every element individually is **slow**.

Thus, we **skip the details** of this naive approach.

---

### Observation 1: Monotonicity

- After every **Type 3 operation**, the diamond values **increase with rank**.
- Sorting is always **descending**, and values stay **monotonically decreasing** after updates.

Thus, we can maintain a **monotonic stack** (non-increasing order) to represent the multiset.

#### Handling Each Operation:

- **Type 1 (Insert and Remove):**
  - Check the top group of the stack:
    - If the smallest value is **less than** $v$, **remove** it.
    - Continue until no such diamonds remains.
  - **Insert** new $N$ diamonds with value $v$.

- **Type 2 (Multiplicity Query):**
  - Since the diamonds are sorted, use **binary search** to find diamonds with value $p$.

- **Type 3 (Global Increase):**
  - Update each diamond's value **naively**.
  - **Time complexity becomes too high** if done directly.

---

### Observation 2: Group Storage and Lazy Updates

Instead of storing each diamond individually, **group diamonds** by insertion time.
Also, we can do lazy update in operation 3. That is, we can calulate the updated value of each diamond only when we need, as long as we know how many type 3 operations are done during the time.

Each **group** stores three values:
- `init_value`: the initial value of diamonds in this group.
- `prefix_elements`: total number of diamonds up to this group.
- `prefix_op3`: number of Type 3 operations at the time of insertion.

Additionally, maintain a **global counter**:
- `accu_op3`: total number of Type 3 operations done so far.

---

#### How to Compute the Current Value

Suppose we want the **$k^{th}$ diamond**.  
The actual value is calculated by:

`value = init_value + (accu_op3 - prefix_op3) * (M - (elements_before_group + position_in_group) + 1)`

Where:
- `elements_before_group` = number of diamonds inserted before this group.
- `position_in_group` = position inside the group.

This allows **lazy update**: values are computed **only when needed**.

---

#### Final Handling of Operations:

- **Type 1 (Insert and Remove):**
  - Remove top groups if their minimum diamond is **$< v$**.
  - Adjust partial groups if necessary.
  - Insert a new group for the $N$ diamonds of value $v$.
  - **Time Complexity:** amortized **$O(N)$** over $T$ operations.

- **Type 2 (Multiplicity Query):**
  - Find the rank of first diamond **$\geq p$** and **$\geq p-1$** using **binary search** over groups.
  - Answer is the difference of two ranks.
  - **Time Complexity:** **$O(log T)$** or **$O(log(T) + log(N))$**.

- **Type 3 (Global Update):**
  - Simply **increment** `accu_op3` by 1.
  - **Time Complexity:** **$O(1)$**.

---

### Time Complexity Summary

- **Type 1:** amortized **$O(N)$** over all operations.
- **Type 2:** **$O(log T)$** or **$O(log(T) + log(N))$** per query.
- **Type 3:** **$O(1)$** per update.

**Overall Total:**  

$O(N + T(\log T))\quad \text{or} \quad O(N + T(\log T + \log N))$


---


## Sample Code

```c=
#include <stdio.h>
#define ll long long
#define MAXN (1000000 + 5)

typedef struct diamond_array {
    ll init_value, prefix_elements;
    int prefix_op3;
} Diamond_array;

Diamond_array stk[MAXN];
int stk_sz, accu_op3;
ll M;

ll array_size(int stk_pos) {
    if(stk_pos == 1) {
        return stk[stk_pos].prefix_elements;
    }
    else {
        return stk[stk_pos].prefix_elements - stk[stk_pos - 1].prefix_elements;
    }
}

ll get_value(int stk_pos, int arr_pos) {
	int op = accu_op3 - stk[stk_pos].prefix_op3;
	ll elements_before_array = stk[stk_pos].prefix_elements - array_size(stk_pos);
	ll value = stk[stk_pos].init_value + op * (M - (elements_before_array + arr_pos) + 1);
	return value;
}

ll bsearch(ll target) {
	int l = 1, r = stk_sz, best = -1;
	while(l <= r) {
		int mid = (l + r) / 2;
		if(target >= get_value(mid, array_size(mid))) {
			best = mid;
			r = mid - 1;    
		}
		else {
			l = mid + 1;
		}
	}
	if(best == -1) return stk[stk_sz].prefix_elements + 1;
	else {
		int op = accu_op3 - stk[best].prefix_op3;
		if(op == 0) {
			return stk[best].prefix_elements - array_size(best) + 1;
		}
		ll c = (target - stk[best].init_value) / op;
		ll index = M - c + 1;
        if(index > stk[best].prefix_elements - array_size(best) + 1) {
            return index;
        }
        else {
            return stk[best].prefix_elements - array_size(best) + 1;
        }
	}
}

int main() {
    int T;
    scanf("%d%lld", &T, &M);

    for(int i = 0; i < T; i++) {
        int t;
        scanf("%d", &t);
        if(t == 1) {
            int N; ll v, remove_total = 0;
            scanf("%d%lld", &N, &v);
            while(stk_sz && v > get_value(stk_sz, 1)) {
                remove_total += array_size(stk_sz);
                stk_sz--;
            }
            if(stk_sz > 0) {
				if(get_value(stk_sz, array_size(stk_sz)) < v) {
					int op = accu_op3 - stk[stk_sz].prefix_op3;
					ll c = (v - stk[stk_sz].init_value) / op;
					ll index = (op * c == v - stk[stk_sz].init_value) ? M - c + 1 : M - c;
					remove_total += stk[stk_sz].prefix_elements - index;
					stk[stk_sz].prefix_elements = index;
				}
			}
            stk_sz++;
            stk[stk_sz].init_value = v;
            stk[stk_sz].prefix_op3 = accu_op3;
            if(stk_sz == 0) {
                stk[stk_sz].prefix_elements = N;
            }
            else {
                stk[stk_sz].prefix_elements = stk[stk_sz - 1].prefix_elements + N;
            }
            printf("%lld\n", remove_total);
        }
        else if(t == 2) {
            ll p;
            scanf("%lld", &p);
			ll start = bsearch(p), end = bsearch(p - 1);
			printf("%lld\n", end - start);
        }
        else {
            accu_op3++;
        }
    }
}
```
