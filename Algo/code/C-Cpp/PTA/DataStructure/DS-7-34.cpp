#include <cstdio>
#include <vector>

using namespace std;

/*
    本题考察对【有向图是否有环】的判断，适合采用拓扑排序
*/

// 邻接表节点
typedef struct ListNode
{
    int data; // 记录入度数或邻接点下标
    ListNode *next;
} *List;

// 邻接表
class AdjList
{
private:
    int vertexNum;
    vector<List> listArr;

public:
    AdjList(int vertexNum)
    {
        this->vertexNum = vertexNum;
        // 初始化邻接表
        listArr.resize(vertexNum);
        for (int i = 0; i < vertexNum; i++)
        {
            List node = new ListNode();
            node->data = 0; // 初始入度数为0
            node->next = NULL;
            listArr[i] = node;
        }
    }
    ~AdjList()
    {
        // 析构时释放内存
        for (int i = 0; i < vertexNum; i++)
        {
            List curr = listArr[i]->next;
            while (curr)
            {
                List next = curr->next;
                delete curr;
                curr = next;
            }
            delete listArr[i];
        }
    }
    // 往有向图中添加一条v1指向v2的边
    void addEdge(int v1, int v2)
    {
        List node = new ListNode();
        node->data = v2; // 指向v2
        node->next = listArr[v1]->next;
        listArr[v1]->next = node; // 头插法
        listArr[v2]->data++;      // v2顶点的入度增加
    }
    // 拓扑排序判断是否无环
    bool noCycle()
    {
        // 复制各顶点的入度，用于拓扑排序，💡【不影响原邻接表】
        // i顶点被访问后，indegree[i]会被标为-1，代表顶点被取出
        vector<int> indegree(vertexNum);
        for (int i = 0; i < vertexNum; i++)
            indegree[i] = listArr[i]->data; // 备份入度，因为后面要拆边
        while (true)
        {
            bool noZero = true; // 是否没有零入度顶点
            for (int i = 0; i < vertexNum; i++)
            {
                // 找未被访问的零度顶点
                if (indegree[i] == 0)
                {
                    noZero = false;   // 有0入度的顶点
                    indegree[i] = -1; // 标记已访问
                    List curr = listArr[i]->next;
                    while (curr)
                    {
                        // “拆掉”入边，更新邻接点入度
                        indegree[curr->data]--;
                        curr = curr->next;
                    }
                }
            }
            if (noZero) // 没有0入度顶点就迭代结束
                break;
        }
        // 检查是否有顶点未被取出
        for (int i = 0; i < vertexNum; i++)
        {
            if (indegree[i] != -1) // 有顶点未被取出就说明有环
                return false;
        }
        return true;
    }
};

int main()
{
    int vertexNum; // 顶点数
    scanf("%d", &vertexNum);
    // 初始化邻接表
    AdjList graph(vertexNum);
    // 读入各点的依赖
    for (int i = 0; i < vertexNum; i++)
    {
        int depend; // 依赖数
        scanf("%d", &depend);
        // 某个顶点的依赖顶点就是其前驱顶点。
        for (int j = 0; j < depend; j++)
        {
            int vertex;
            scanf("%d", &vertex);
            vertex--; // 题目顶点编号是1~N，这里转换为0~N-1
            graph.addEdge(vertex, i);
        }
    }
    // 拓扑排序判断是否有环
    printf(graph.noCycle() ? "1" : "0");
    return 0;
}

/*
    本题给出的是AOV网，要使得任务调度可行，整张图必须是【有向无环图】。

    要判断有向图是否有环，咱第一个想到的算法就是拓扑排序了。这里采用的是【卡恩拓扑排序算法】:

        1. 不断拆掉入度为0的顶点及其出边，直至图中没有入度为0的顶点为止
        2. 如果此时还有顶点没有被访问，说明图中有环

    算法思路是很简单的，看代码就能理解的很清晰。
    -----------------------
    ⭐ 再思考一下能发现，拓扑排序还可以借助【栈】来进行辅助。

    💡 可以发现，拓扑排序每次迭代中，我都要【扫描邻接表的顶点数组】来寻找0入度的顶点，在顶点数很多的情况下这样会有很大的额外开销。
    如果【用栈储存所有0度顶点】，那么每次迭代【只需要弹栈操作即可】。

    栈辅助的题解我也写了: DS-7-34-withStack.cpp

        - SomeBottle 2023.1.25

*/

/*
7-34 任务调度的合理性
    假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

    比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

    但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。你现在的工作是写程序判定任何一个给定的任务调度是否可行。

输入格式:
    输入说明：输入第一行给出子任务数N（≤100），子任务按1~N编号。随后N行，每行给出一个子任务的依赖集合：首先给出依赖集合中的子任务数K，随后给出K个子任务编号，整数之间都用空格分隔。
输出格式:
    如果方案可行，则输出1，否则输出0。
输入样例1:
    12
    0
    0
    2 1 2
    0
    1 4
    1 5
    2 3 6
    1 3
    2 7 8
    1 7
    1 10
    1 7
输出样例1:
    1
输入样例2:
    5
    1 4
    2 1 4
    2 2 5
    1 3
    0
输出样例2:
    0
代码长度限制
    16 KB
时间限制
    400 ms
内存限制
    64 MB
*/