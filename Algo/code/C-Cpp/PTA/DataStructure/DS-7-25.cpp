#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> FriendSet;

// 简单并查集
class UnionFind
{
private:
    int size;
    vector<int> parents; // 各节点的父节点
    vector<int> counts;  // 各节点对应子树的节点数
public:
    UnionFind(int size)
    {
        this->size = size;
        // 初始化并查集
        parents.resize(size);
        counts.resize(size, 1); // 初始所有节点计数为1
        // 初始: 所有节点的父节点就是自己
        for (int i = 0; i < size; i++)
            parents[i] = i;
    }
    // 查找一个元素所在的树的根结点
    int find(int elem)
    {
        // 访问的就是树的根结点，返回
        // 根结点的父节点就是自己
        if (parents[elem] == elem)
        {
            return elem;
        }
        else
        {
            // 路径压缩, 如果当前不是根结点的孩子，就将其转换为其孩子
            return parents[elem] = find(parents[elem]);
        }
    }
    // 将两个元素对应的集合(树)合并
    void merge(int first, int second)
    {
        int root1 = find(first);  // 找到元素1所在树的根结点
        int root2 = find(second); // 找到元素2所在树的根结点
        if (root1 == root2)       // 两元素所在树相同时不要操作!!!!!!!!!!!!!-------------容易漏掉!💡
            return;
        // 将元素较少的树并入元素较多的
        if (counts[root1] > counts[root2])
        {
            parents[root2] = root1;
            counts[root1] += counts[root2]; // 元素1对应的子树结点计数增加
        }
        else
        {
            parents[root1] = root2;
            counts[root2] += counts[root1];
        }
    }
    // 找到最大元素数的集合
    int maxCount()
    {
        int max = 0;
        for (int i = 0; i < size; i++)
        {
            // 扫描所有根节点即可
            if (parents[i] == i && counts[i] > max)
                max = counts[i];
        }
        return max;
    }
};

int main()
{
    int stuNum, clubNum; // 学生总数和俱乐部数
    cin >> stuNum >> clubNum;
    UnionFind uf(stuNum); // 初始化并查集
    for (int i = 0; i < clubNum; i++)
    {
        int clubStu, firstStu;
        // 读入俱乐部人数和俱乐部中第一个学生
        // 这里不选第一个学生也是可以的，选第一个只是因为操作方便
        cin >> clubStu >> firstStu;
        // 读入俱乐部的其他学生
        for (int j = 1; j < clubStu; j++)
        {
            int anotherStu;
            cin >> anotherStu;
            // 注意，并查集里编号是0~N-1
            // 这里利用并操作把所有有关系的朋友都集合起来，成为一个朋友圈集合
            uf.merge(firstStu - 1, anotherStu - 1);
        }
    }
    cout << uf.maxCount();
    return 0;
}

/*
    观察题目: “不同的俱乐部”，“如果A和B是朋友，且B和C是朋友，则A和C也是朋友”，“朋友圈”，可以发现，题目在试图描述一种集合的构造方法——
        —— 没错，这里要求的集合就是“朋友圈”，不同的朋友圈之间也是互不相交的。
    题目要求找到“最大”的朋友圈，其实就是要找到【元素最多的集合(朋友圈)】。

    怎么构造这些朋友圈集合呢？

        1. 学生和学生原本是【独立的元素】，如果把他们撒入【森林】中，他们【自身就是一棵树(也是一个集合)】，这些树之间【没有相同的节点】，从集合的角度来看【他们互不相交】。

        2. 题目用“俱乐部”描述了学生和学生之间的关系，同一个俱乐部的学生互为朋友，也就是他们【在一个朋友圈中】。
            从集合角度来看，他们【应处于一个集合中】; 从树的角度看，他们处于同一棵树。

        3. 因此程序要做的，就是【按照俱乐部】将【互不相交的学生集合并起来】，形成【朋友圈集合】。
            从树的角度来看，就是把有关联的树都连接起来。

    看到这里，程序需要的数据结构就很明了了—— 【并查集】 ！
    ---------------------------------
    具体思路看代码的注释即可，这里简单写一下并查集的基础:

        - 并查集中【所有元素都是不相同】的，因此可以直接用【数组来储存】，通过计算哈希作为下标来访问元素(本题中是用元素值【学生编号】直接定址)。

        - 并查集需要维护一个【父亲数组】，第i号下标对应的值代表i号元素的父节点编号。

        - 本题的并查集还维护了一个【计数数组】，用于【记录集合(树)中的元素数量】，借此才能求出【最大的朋友圈】。

        0. 初始化(Initialization)

            初始化时，所有节点的父节点【就是自己】，这代表所有节点都是根节点。在本题中的意思是: 【每个学生都是一个集合, 他们互不相交】。

        1. 查询(Find) - 找到元素属于哪个集合(找到元素所在树的【根节点】)

            通过元素值val首先可以直接访问到元素的父节点parents[val]，如果parents[val]!=val就说明没到根节点，要继续递归直至【找到根节点】。

            这个过程中其实还可以顺带进行【路径压缩】操作，也就是说，如果【该元素的父亲不是根节点】，就调整其直到【该元素与根节点相连】。

                * 在递归中，只需要【将递归函数返回的节点下标赋给parents[val]即可】。

        2. 合并(Union) - 合并两个【互不相交】的集合

            本质上的操作就是【把一棵树的根节点作为另一棵树的孩子】。

            这里为了尽量不增加复杂度，就尽量将【节点数更小的树】(元素更少的集合)合并到【节点数更多的树】(元素更多的集合)之中。

    总的来说，并查集不算很难，但是从题目中【找到合并和查询的要求】是一大考点。

        - SomeBottle 2023.1.18

*/