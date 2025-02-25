# Problem Description

We provide two versions of the problem statement below: one with a story and one in a formal representation. Feel free to read either or both, depending on your preference.

## Story Version

A person named Michael has many diamonds. Each diamond has a specific **value**. Ze wants to organize zir diamonds. However, this task is time-consuming so that ze wants to design an DSA (Diamond Set Arrangement) to organize diamonds efficiently. Ze knows that you must be good at DSA (Diamond Set Arrangement) since ze knows that you are taking DSA (Data Structures and Algorithms) class in NTU CSIE. Initially, you are given integers $M$ and $T$. You need to perform $T$ operations, with three possible types of operations:
For the $i$-th operation:

1. Given $N$ and $v$, remove all diamonds from the set with a **value strictly less than** $v$, then output how many diamonds were removed. After that, add $N$ diamonds with value $v$ to the set.
2. Given $p$, output the number of diamonds in the set with **value** $p$.
3. Sort the diamonds in the plate in **descending order**. For the $j$-th ranked diamond, increase its value by $(M - j + 1)$. It is guaranteed that the total number of diamonds will not exceed $M$.

## Formal Version

You are given $M$ and $T$. Maintain a multiset $S$ of integers. [More about multiset](https://en.wikipedia.org/wiki/Multiset).
There are $T$ operations, for the $i$-th operation:

1. Given $N$ and $v$, remove all elements in $S$ that are **strictly less than** $v$. Then, add $N$ elements of $v$ to $S$. Output how many elements were removed.
2. Given $p$, output the multiplicity of $p$.
3. Sort $S$ in descending order as $s_1, s_2, ..., s_{|S|}$. Update each $s_j$ as $s_j + (M - j + 1)$. It is guaranteed that $|S| \leq M$.

## Input

The first line contains 2 space-separated integers $T$ and $M$.
The $i$-th line of the following $T$ lines contains one, two, or three integers depending on the incident:
1. $1$ $N_i$ $v_i$, indicating type 1 operation.
2. $2$ $p_i$, indicating type 2 operation.
3. $3$, indicating type 3 operation.

## Output

For type 1 operation, print the number of (diamonds removed / elements removed) per line.
For type 2 operation, print (the number of diamonds in the set with value $p$ / multiplicity of $p$) per line.

# Subtasks

## Subtask 1 (10 pts)

$1 \leq T \leq 10^3$

$1 \leq N \leq 10$

$1 \leq v \leq 2 \times 10^8$

$1 \leq p \leq 10^9$

$1 \leq M \leq 10^5$

## Subtask 2 (10 pts)

$1 \leq T \leq 10^4$

$1 \leq N \leq 10^3$

$1 \leq v \leq 2 \times 10^{12}$

$1 \leq p \leq 10^{13}$

$1 \leq M \leq 10^8$

## Subtask 3 (20 pts)

$1 \leq T \leq 10^6$

$1 \leq N \leq 10^6$

$1 \leq v \leq 10^{18}$

$1 \leq p \leq 2 \times 10^{18}$

$1 \leq M \leq 10^{12}$

Only operations 1 and 2 are present.

## Subtask 4 (20 pts)

$1 \leq T \leq 10^6$

$1 \leq N \leq 10^6$

$1 \leq v \leq 10^{18}$

$1 \leq p \leq 2 \times 10^{18}$

$1 \leq M \leq 10^{12}$

Only operations 1 and 3 are present.

## Subtask 5 (40 pts)

$1 \leq T \leq 10^6$

$1 \leq N \leq 10^6$

$1 \leq v \leq 10^{18}$

$1 \leq p \leq 2 \times 10^{18}$

$1 \leq M \leq 10^{12}$

All operations are present.

# Sample Testcases

## Sample Input 1

```
5 20
1 5 4
1 6 3
3
1 2 17
2 17
```

## Sample Output 1

```
0
0
4
3
```

## Sample Input 2

```
6 20
1 5 7
1 6 9
2 7
2 9
1 2 9
2 9
```

## Sample Output 2

```
0
5
0
6
0
8
```

## Sample Input 3

```
6 20
1 5 4
3
1 6 10
3
1 2 17
1 2 30
```

## Sample Output 3

```
0
0
0
8
```
