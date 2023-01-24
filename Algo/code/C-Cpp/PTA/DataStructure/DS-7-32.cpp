#include <cstdio>
#include <vector>

using namespace std;

// 这题直接让人想起了QQ的“一笔画”红包，其实就是欧拉图问题
// 不过一笔画红包构成的是欧拉通路，整体来说是半欧拉图(并没有回到起点)
// 本题需要能一笔回到起点，因此要判断是否有【欧拉回路】

// 并查集，用于判断连通性
class UnionFind
{
private:
    int size; // 节点数量
    vector<int> parents;
    vector<int> counts; // 记录树中节点数量
public:
    UnionFind(int size)
    {
        this->size = size;
        parents.resize(size);
        counts.resize(size, 1); // 初始每个节点自身构成一个集合
        for (int i = 0; i < size; i++)
            parents[i] = i; // 并查集中各节点父节点初始为自己
    }
    // 寻找节点所在树的根结点, 顺带路径压缩
    int find(int index)
    {
        return parents[index] == index ? index : parents[index] = find(parents[index]);
    }
    // 并操作，将小树并入大树
    void merge(int node1, int node2)
    {
        int root1 = find(node1); // 寻找节点1所在的树的根
        int root2 = find(node2); // 寻找节点2所在的树的根
        if (root1 == root2)      // 树根相同不进行合并操作-----------💡容易写掉
            return;
        // 小树并入大树
        if (counts[root1] > counts[root2])
        {
            parents[root2] = root1;
            counts[root1] += parents[root2];
        }
        else
        {
            parents[root1] = root2;
            counts[root2] += parents[root1];
        }
    }
};

int main()
{
    int nodeNum, edgeNum; // 节点数和边数
    scanf("%d %d", &nodeNum, &edgeNum);
    UnionFind uf(nodeNum);           // 初始化并查集
    vector<int> degrees(nodeNum, 0); // 储存每个节点的度数
    // 读入所有边
    for (int i = 0; i < edgeNum; i++)
    {
        int node1, node2;
        scanf("%d %d", &node1, &node2);
        node1--; // 题目中是1~N编号，这里处理用0~N-1编号
        node2--;
        uf.merge(node1, node2); // 进行并操作
        degrees[node1]++;       // 度增加
        degrees[node2]++;
    }
    int output = 1; // 输出是否是欧拉图
    for (int i = 0; i < nodeNum; i++)
    {
        // 欧拉图判定条件1: 所有顶点皆连通
        // 欧拉图判定条件2: 所有顶点的度数为偶数
        // 如果不是所有顶点都在同一集合中，就是不连通的
        // 如果有奇数度数出现，也是不满足欧拉图的
        if (uf.find(0) != uf.find(i) || (degrees[i] & 1))
        {
            output = 0;
            break;
        }
    }
    printf("%d", output);
    return 0;
}

/*
    这题主要考察了对于【一个图是否是欧拉图】的判断。

    欧拉图是具有【欧拉回路】的图，而欧拉回路指的是【从任一个顶点出发，能有且仅有经过图中每条边一次，最后回到这个点】的回路。

    寻找欧拉回路的算法一眼看上去发现: 我超！好难！
    然而本题只需要判断【无向图中有没有欧拉回路】，因此把握以下两个判断指标就行:

        1. 无向图中【所有】顶点【是连通的】。
            - 采用【并查集】可以高效判断。

        2. 无向图中每个顶点的【度数】是【偶数】。

    满足上面两点的话，无向图中就有欧拉回路。

        - SomeBottle 2023.1.24
*/
/*
7-32 哥尼斯堡的“七桥问题”
哥尼斯堡是位于普累格河上的一座城市，它包含两个岛屿及连接它们的七座桥，如下图所示。
https://images.ptausercontent.com/51

可否走过这样的七座桥，而且每桥只走过一次？瑞士数学家欧拉(Leonhard Euler，1707—1783)最终解决了这个问题，并由此创立了拓扑学。

这个问题如今可以描述为判断欧拉回路是否存在的问题。欧拉回路是指不令笔离开纸面，可画过图中每条边仅一次，且可以回到起点的一条回路。现给定一个无向图，问是否存在欧拉回路？

输入格式:
    输入第一行给出两个正整数，分别是节点数N (1≤N≤1000)和边数M；随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个节点的编号（节点从1到N编号）。
输出格式:
    若欧拉回路存在则输出1，否则输出0。
输入样例1:
    6 10
    1 2
    2 3
    3 1
    4 5
    5 6
    6 4
    1 4
    1 6
    3 4
    3 6
输出样例1:
    1
输入样例2:
    5 8
    1 2
    1 3
    2 3
    2 4
    2 5
    5 3
    5 4
    3 4
输出样例2:
    0
代码长度限制
    16 KB
时间限制
    400 ms
内存限制
    64 MB
*/