#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);
    int steps[N + 1]; // steps[i]代表跳到第i级台阶有多少种方式
    memset(steps, 0, sizeof(steps));
    steps[0] = 1;                // 从最底部跳到第1-K级台阶至少有1种方式
    for (int i = 1; i <= N; i++) // 递推
    {
        int bound = i - K; // 最多能借助到第i-K级台阶
        for (int j = i - 1; j >= 0 && j >= bound; j--)
            steps[i] = (steps[i] + steps[j]) % 100003;
    }
    printf("%d", steps[N]);
    return 0;
}

/*

    本题的递推规律还是很好找的，比如K>=3的情况:

    - 跳上第1级台阶只有1种途径

    - 跳上第2级台阶的时候我可以【从最底端一步跳上第2级】，也可以【先到第1级，借助第1级台阶跳到第2级】。

    - 跳上第3级台阶则既可以:
        1. 从最底端一步跨上来 (方法数:1)
        2. 借助第1级台阶 (方法数:1)
        3. 借助第2级台阶 (方法数:2)

    跳上第3级台阶时可以借助第1级和第2级台阶，那么跨上第3级台阶的方法数为:

    1 + 1 + 2 = 4

    因为一步最多能迈K级台阶，因此要迈上第n级台阶，最多只能借助到第n-K个台阶，因此到第n级台阶的方法数 M[n] (n>=1) 是:

    M[n] = M[n-1] + M[n-2] + ... + M[n-k]

    如果n-k<0则为:

    M[n] = M[n-1] + M[n-2] + ... + M[0]

    于是咱就用两层循环解决了这道题。

    PS: 可以发现，K=2时求出的序列形似斐波拉契数列。

        - SomeBottle 2023.3.3
*/

/*
# 台阶问题

## 题目描述

有 $N$ 级台阶，你一开始在底部，每次可以向上迈 $1\sim K$ 级台阶，问到达第 $N$ 级台阶有多少种不同方式。

## 输入格式

两个正整数 $N,K$。

## 输出格式

一个正整数 $ans\pmod{100003}$，为到达第 $N$ 级台阶的不同方式数。

## 样例 #1

### 样例输入 #1

```
5 2
```

### 样例输出 #1

```
8
```

## 提示

- 对于 $20\%$ 的数据，$1\leq N\leq10$，$1\leq K\leq3$；
- 对于 $40\%$ 的数据，$1\leq N\leq1000$；
- 对于 $100\%$ 的数据，$1\leq N\leq100000$，$1\leq K\leq100$。
*/