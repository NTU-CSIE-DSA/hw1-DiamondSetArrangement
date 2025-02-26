#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

typedef struct diamond {
  int64_t v, num;
  int64_t prefix_total_element, prev_op3;
} Diamond;

int64_t get_real_value(Diamond d, int64_t i, int64_t op3_count, int64_t M);

int64_t op1(Diamond *stack, size_t *st_size, int64_t v, int64_t num,
    int64_t op3_count, int64_t M);

int main(void) {
  int64_t T, M;
  assert(scanf("%" SCNd64 "%" SCNd64, &T, &M) == 2);

  int64_t op3_count = 0;
  size_t st_size = 0;
  Diamond *stack = (Diamond*) malloc(sizeof(Diamond) * 1000000);

  for (int i = 0; i < T; ++i) {
    int operation;
    assert(scanf("%d", &operation) == 1);
    switch (operation) {
      case 1: {
        int64_t N, v;
        scanf("%" SCNd64 "%" SCNd64, &N, &v);
        int64_t removed = op1(stack, &st_size, v, N, op3_count, M);
        printf("%" SCNd64 "\n", removed);
        break;
      }
      case 2: {
        int64_t p;
        scanf("%" SCNd64, &p);
        // op2(stack, &stack_size, p);
        break;
      }
      case 3: {
        op3_count++;
        break;
      }
    }
  }
}

int64_t get_real_value(Diamond d, int64_t i, int64_t op3_count, int64_t M) {
  const int64_t remain_ops = op3_count - d.prev_op3;
  return d.v + remain_ops * (M - d.prefix_total_element - i + 1);
}

int64_t op1(Diamond *stack, size_t *st_size, int64_t v, int64_t num,
    int64_t op3_count, int64_t M) {
  int64_t removed = 0;
  while (*st_size > 0 && get_real_value(stack[(*st_size) - 1], 1, op3_count, M) < v) {
    removed += stack[(*st_size) - 1].num;
    (*st_size)--;
  }
  int64_t l = -1, r = stack[(*st_size) - 1].num + 1;
  while (r - l > 1) {
    int64_t mid = (l + r) >> 1;
    if (get_real_value(stack[(*st_size) - 1], mid, op3_count, M) >= v) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (*st_size > 0) {
    removed += stack[(*st_size) - 1].num - l;
    stack[(*st_size) - 1].num -= stack[(*st_size) - 1].num - l;
  }

  (*st_size)++;
  stack[(*st_size) - 1].v = v;
  stack[(*st_size) - 1].num = num;
  stack[(*st_size) - 1].prefix_total_element = (*st_size) > 1
    ? stack[(*st_size) - 2].prefix_total_element + stack[(*st_size) - 2].num
    : 0;
  stack[(*st_size) - 1].prev_op3 = op3_count;
  return removed;
}