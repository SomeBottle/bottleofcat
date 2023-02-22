#include <cstdio>

using namespace std;

int main()
{
    char readChr;
    int chrNum = 0;
    while (scanf("%c", &readChr) != EOF && readChr != '\n')
        if (readChr != ' ')
            chrNum++;
    printf("%d", chrNum);
    return 0;
}

/*
    这题直接逐字符读取即可，如果字符不是空格或换行符就统计在内。

        - SomeBottle 2023.2.22
*/

/*
# [NOIP2018 普及组] 标题统计

## 题目描述

凯凯刚写了一篇美妙的作文，请问这篇作文的标题中有多少个字符？   注意：标题中可能包含大、小写英文字母、数字字符、空格和换行符。统计标题字 符数时，空格和换行符不计算在内。

## 输入格式

输入文件只有一行，一个字符串 $s$。

## 输出格式

输出文件只有一行，包含一个整数，即作文标题的字符数（不含空格和换行符）。

## 样例 #1

### 样例输入 #1

```
234
```

### 样例输出 #1

```
3
```

## 样例 #2

### 样例输入 #2

```
Ca 45
```

### 样例输出 #2

```
4
```

## 提示

【输入输出样例 1 说明】
标题中共有 3 个字符，这 3 个字符都是数字字符。

【输入输出样例 2 说明】 标题中共有$ 5$ 个字符，包括 $1$ 个大写英文字母， $1$ 个小写英文字母和 $2$ 个数字字符， 还有 $1$ 个空格。由于空格不计入结果中，故标题的有效字符数为 $4$ 个。

【数据规模与约定】
规定 $|s|$ 表示字符串 $s$ 的长度（即字符串中的字符和空格数）。
对于 $40\%$ 的数据，$1 ≤ |s| ≤ 5$，保证输入为数字字符及行末换行符。
对于 $80\%$ 的数据，$1 ≤ |s| ≤ 5$，输入只可能包含大、小写英文字母、数字字符及行末换行符。
对于 $100\%$ 的数据，$1 ≤ |s| ≤ 5$，输入可能包含大、小写英文字母、数字字符、空格和行末换行符。
*/