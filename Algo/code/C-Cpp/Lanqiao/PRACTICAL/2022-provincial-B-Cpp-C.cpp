#include <iostream>

using namespace std;

int main()
{
    long long a, b;
    long long n;
    cin >> a >> b >> n;
    long long nums[] = {a, a, a, a, a, b, b}; // 直接把一周中每天刷的题量列出来
    long long solved = 0;                     // 做题量
    long long days = 0;                       // 做了几天
    for (int i = 0; solved < n; i = (i + 1) % 7)
    {
        solved += nums[i];
        days++;
    }
    cout << days;
    return 0;
}

/*
    这题可以看作一个模拟题。
    直接把七天做的题量列出来，不断【循环】扫描来模拟做题过程即可（直至做题数量>=n）
    这样的写法很保险，肯定不会出错。

        * 注意: 题目要拿满分的话，要考虑极大的数据规模(10^8)，需要采用long long数据类型。

    - SomeBottle 2023.2.10
*/

/*
# [蓝桥杯 2022 省 B] 刷题统计

## 题目描述

小明决定从下周一开始努力刷题准备蓝桥杯竞赛。他计划周一至周五每天做 $a$ 道题目，周六和周日每天做 $b$ 道题目。请你帮小明计算，按照计划他将在第几天实现做题数大于等于 $n$ 题?

## 输入格式

输入一行包含三个整数 $a, b$ 和 $n$.

## 输出格式

输出一个整数代表天数。

## 样例 #1

### 样例输入 #1

```
10 20 99
```

### 样例输出 #1

```
8
```

## 提示

对于 $50 \%$ 的评测用例，$1 \leq a, b, n \leq 10^{6}$.

对于 $100 \%$ 的评测用例，$1 \leq a, b, n \leq 10^{18}$.

蓝桥杯 2022 省赛 B 组 C 题。
*/