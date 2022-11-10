/*
试题 基础练习 序列求和
资源限制
    内存限制：256.0MB   C/C++时间限制：1.0s   Java时间限制：3.0s   Python时间限制：5.0s
问题描述
    求1+2+3+...+n的值。
输入格式
    输入包括一个整数n。
输出格式
    输出一行，包括一个整数，表示1+2+3+...+n的值。
样例输入1   样例输出1
    4          10
样例输入2   样例输出2
    100       5050
数据规模与约定
1 <= n <= 1,000,000,000。
*   说明：请注意这里的数据规模。
    本题直接的想法是直接使用一个循环来累加，然而，当数据规模很大时，这种“暴力”的方法往往会导致超时。此时你需要想想其他方法。你可以试一试，如果使用1000000000作为你的程序的输入，你的程序是不是能在规定的上面规定的时限内运行出来。
    本题另一个要值得注意的地方是答案的大小不在你的语言默认的整型(int)范围内，如果使用整型来保存结果，会导致结果错误。
    如果你使用C++或C语言而且准备使用printf输出结果，则你的格式字符串应该写成%I64d以输出long long类型的整数。

*/
#include <cstdio>

using namespace std;

int main()
{
    unsigned long long destVal;
    scanf("%lld", &destVal);
    // 大伙儿最爱的1+2+...+n求和公式  ((首项+尾项)*项数)/2
    // 在数据规模很大的时候，不妨想想有什么数学公式可以用
    // 值得一提的是题目给了个格式字符串%I64d，这个是一个非标准的格式指示符(似乎是微软搞的)，所以我换用了标准中的%lld
    unsigned long long sum = ((1 + destVal) * destVal) / 2;
    printf("%lld", sum);
    return 0;
}