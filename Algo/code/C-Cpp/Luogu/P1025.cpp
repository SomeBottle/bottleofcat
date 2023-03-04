#include <cstdio>

using namespace std;

int solve(int num, int start = 1, int part = 1); // DFS解决问题

int N, K;

int main()
{
    scanf("%d %d", &N, &K);
    printf("%d", solve(N));
    return 0;
}

// (当前剩余的整数大小，这一份从start开始枚举，第几份)
int solve(int num, int start, int part)
{
    if (part == K) // 找到了可行的分法，分成了K份
        return 1;
    int res = 0; // 总的可行方案
    // 除了当前这一份外还有K-part份，假设后面每份只分一份，bound就是当前能分到的最大数值
    // 比如把7分成3份，那么第一份的数值最大为7-(3-1)=5.
    int bound = num - (K - part);
    for (int i = start; i <= bound; i++) // 从start开始，也算是剪枝
    {
        int numLeft = num - i; // 计算留给后面分的还有多少
        if (i > numLeft)       // 当前这一份比剩余的值要大，就不用继续了，剪枝
            break;
        res += solve(numLeft, i, part + 1);
    }
    return res;
}

/*
    这题主要考察的是搜索+剪枝操作

    首先先上DFS，我的做法是每份分到的数值【从小到大】进行枚举，【从第1份开始】向后深入。

    DFS搜索本身就是骗分法宝，但往往时间复杂度过高。而它时间复杂度高的原因就是把【递归树中所有分支全部枚举了一遍】。

    实际上有很多分支是完全没必要深入去枚举的，也就是可以被【剪掉】。
    ----------------------
    这题的规律一眼还真不太看得出来，但不用怕，咱可以手动打表嘛！

    通过打表可以发现剪枝规律（仅限我这个题解的做法）:

    1. 后一份只需要【从前一份的数值】开始枚举即可
    2. 假设当前【剩余数值大小为num】，是第part份，而总共要分成K份。

        要保证后面每份都不为空（也就是后面每份都为1）的话，当前这第part份【最多】只能分到 num - (K-part) 。

        * 比如num=7,part=1,K=3，那么第1份最多只能分到 7-(3-1)=5 份

    3. 【后面一份】的数值不能比【前一份】的大。

        * 可以排除掉 1 4 2，1 5 1 这样的情况

    这样一来可以把时间复杂度降低 70% 左右，剪枝效果可以说是非常显著了！

        - SomeBottle 2023.3.4
*/