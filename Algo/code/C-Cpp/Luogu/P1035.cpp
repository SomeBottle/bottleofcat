#include <iostream>

using namespace std;

int main()
{
    double k;
    cin >> k;
    double sum = 0;
    int n = 0;
    while (sum <= k)
    {
        n++;
        sum += (double)1 / n;
    }
    cout << n;
    return 0;
}

/*
    本题已经给出公式，求和+判断即可。
        - SomeBottle 2023.2.15
*/

/*
# [NOIP2002 普及组] 级数求和

## 题目描述

已知：$S_n= 1+\frac{1}{2}+\frac{1}{3}+…+\frac{1}{n}$。显然对于任意一个整数 $k$，当 $n$ 足够大的时候，$S_n>k$。

现给出一个整数 $k$，要求计算出一个最小的 $n$，使得 $S_n>k$。

## 输入格式

一个正整数 $k$。

## 输出格式

一个正整数 $n$。

## 样例 #1

### 样例输入 #1

```
1
```

### 样例输出 #1

```
2
```

## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1\le k \le 15$。

**【题目来源】**

NOIP 2002 普及组第一题
*/