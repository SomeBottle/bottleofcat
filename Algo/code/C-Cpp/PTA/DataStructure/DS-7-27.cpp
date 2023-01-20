#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <stack>
// 注: map头文件已经引入<utility>头文件，因此可以使用pair

using namespace std;

/*
    观察样例:
        parent和child相对应，表述父子关系
        ancestor和descendant(后代)相对应，包含父子关系
    注意不要把这里的ancestor理解成祖先，在这里的意思是前一代。
*/

typedef pair<int, int> IndPair; // 储存<父节点下标, 父节点缩进>的pair

int main()
{
    int serial = 0;            // 名字编号
    map<string, int> nameInds; // 将名字映射到一个整数
    vector<int> parents;       // 记录每个家庭成员的父节点和后代
    int nameNum, sentenceNum;  // 名字数量和陈述句数量
    // 注意这里顺带取走了行末的换行符
    scanf("%d %d%*[\n]", &nameNum, &sentenceNum);
    // 初始化父子关系数组
    parents.resize(nameNum);
    // ---------------------------------------------------------------------------读入家谱
    stack<IndPair> parentNodes;      // 储存父节点
    parentNodes.push(IndPair{0, 0}); // 最早祖先的下标为0，缩进为0
    int prevIndent = 0;              // 之前的缩进
    for (int i = 0; i < nameNum; i++)
    {
        string name;
        int indent = 0;
        char readChr;
        // 读入一行数据
        while (scanf("%c", &readChr) != EOF && readChr != '\n')
        {
            if (readChr == ' ') // 如果读入的是空格，缩进就增加
                indent++;
            else // 否则读入的就是名字
                name.push_back(readChr);
        }
        nameInds[name] = serial; // 给每个名字编个号(下标)
        if (indent > prevIndent)
        {
            // 如果缩进增加了
            // 先寻找有没有相同缩进的父节点，如果没有就把父亲节点的下标和缩进压入
            // 上一个节点就是父节点，编号为serial-1, 缩进为prevIndent
            parentNodes.push(IndPair{serial - 1, prevIndent});
        }
        else if (indent < prevIndent)
        {
            // 如果缩进减小了
            // 出栈，找到当前成员的父节点，父节点的缩进肯定【少于】当前节点
            // 最多出栈到缩进=0时就不再继续了
            while (parentNodes.top().second > 0 && parentNodes.top().second >= indent)
                parentNodes.pop();
        }
        if (serial == 0)
            parents[serial] = -1; // 💡 !!!!!!!!!!!最早祖先的父节点是-1，避免后面判断兄弟时出错!!!!!!!!!!!!!
        else
            parents[serial] = parentNodes.top().first; // 指定当前节点的父节点下标
        serial++;                                      // 名字序号递增
        prevIndent = indent;                           // 用作下一次迭代判断缩进量是否改变
    }
    // ---------------------------------------------------------------------------接下来读入陈述句
    string nameFront;  // 句子中首个名字
    string nameBack;   // 句子中最后一个名字
    char relation[11]; // 表示关系的名词
    char temp[11];     // 临时字符数组
    for (int i = 0; i < sentenceNum; i++)
    {
        scanf("%s", temp); // 读入句子中首个名字
        nameFront.assign(temp);
        scanf("%*s%*s"); // 吸收掉系动词和冠词
        scanf("%s", relation);
        scanf("%*s");      // 吸收掉介词of
        scanf("%s", temp); // 读入句子中最后一个名字
        nameBack.assign(temp);
        int nameFrontInd = nameInds[nameFront]; // 获得名字的编号(下标)
        int nameBackInd = nameInds[nameBack];
        bool found = false; // 是否符合家谱
        switch (relation[0])
        {
        case 'c': // childs
            // X is a child of Y, X的父节点是Y
            found = parents[nameFrontInd] == nameBackInd;
            break;
        case 'p': // parents
            // X is the parent of Y, Y的父节点是X
            found = parents[nameBackInd] == nameFrontInd;
            break;
        case 's': // siblings
            // X is a sibling of Y, X和Y的父节点的孩子中有X和Y
            // 如果X的父节点也是Y的父节点，二者就互为兄弟姐妹
            found = parents[nameBackInd] == parents[nameFrontInd];
            break;
        case 'd': // descendants
        {
            // X is a descendant of Y, 从X往上找父节点，有父节点Y
            int parentInd = nameFrontInd;
            while (parentInd != -1) // 下标为-1就遇到最早祖先了
            {
                parentInd = parents[parentInd]; // 向上找父节点
                // 这样写不会漏掉父亲是0号节点的情况
                if (parentInd == nameBackInd)
                {
                    found = true;
                    break;
                }
            }
        }
        break;
        case 'a': // ancestors
        {

            // X is an ancestor of Y, 从Y向上找父节点，有父节点X
            int parentInd = nameBackInd;
            while (parentInd != -1) // 下标为-1就遇到最早祖先了
            {
                parentInd = parents[parentInd]; // 同样是向上找父节点
                // 这样写不会漏掉父亲是0号节点的情况
                if (parentInd == nameFrontInd)
                {
                    found = true;
                    break;
                }
            }
        }
        break;
        }
        if (found)
            printf("True\n");
        else
            printf("False\n");
    }
    return 0;
}

/*
    这题我是真的非常佩服出题老师的挖坑能力，这个坑就坑在【测试点3】- 最大N和M，随机

    乍一看好像没什么特别的，但我刚开始死活过不了这个测试点。后来写了个家谱数据生成器加上bash脚本才找到了问题所在——

        最开始我是按并查集的parents数组去初始化本题中的parents数组的，也就是初始值parents[i]=i，这样一来，树根(最早祖先)的父节点就是【它自己】。

        然而后面我在判断【两节点是否为兄弟】时，判断条件写的是 parents[节点1]==parents[节点2] 。

        假如我有这样一组数据:

            3 1
            Simon
              Steve
              Alex
            Simon is a sibling of Steve

        那么程序就会判断 parents[Simon]==parents[Steve] 是否成立。很明显，这里parents[Simon]=Simon，而parents[Steve]=Simon，所以导致了判断失误，💡 这也是【测试点3】故意卡的一个地方。

        解决方法很简单，在初始化时将【最早祖先】(树根)的【父节点设为其他值】，详见本代码第63行。
    -------------------------------------------

    说说这道题的思路。

    家谱图是比较典型的树形结构，但并不是说看到树形结构我就一定要用树的构造模式。

    本题用空格缩进来【表示父子关系】
        * 因为题目中说了“如果家谱中一个名字前缩进k个空格，则下一行中名字至多缩进k+2个空格”

    而题目要我们判断几条陈述句的正确性，可以看出题目中涉及到的判断主要是几种:

        1. X是Y的孩子
            - X的父节点是Y
        2. X是Y的父/母
            - Y的父节点是X
        3. X是Y的兄弟/姐妹
            - X和Y的父节点相同
                (!!!💡注意树根结点的处理)
        4. X是Y的后裔 (包括X是Y的孩子的情况)
            - X的所有祖先节点中有Y
        5. X是Y的祖先 (💡注意，这里的祖先指的是Y的所有父节点的任意一个，包含X是Y的父母的情况)
            - Y的所有祖先节点中有X

    归纳之后发现，我只需要储存【每一个家庭成员的父/母】(每一个节点的父节点) 即可。
        * 可以发现这里和并查集的parents数组是很类似的，不同点是【要注意根结点的父节点的设置】，我的建议是【单独标记根结点的父节点】，以免混淆判断。
    --------------------------------------------

    再说说这道题的输入。

        - 因为是依赖于空格缩进来表示父子关系，因此在接受输入时我首先要【对空格进行计数】。
            空格的数量我将其记为【缩进量】indent

        - 每次扫描完一行文本，都会记录当前缩进量，以【和下一次迭代的缩进量进行比较】

        - 某次扫描的时候发现【缩进量变大】了，说明【出现了新儿子】，就把【上一个读入的节点】作为【一个父节点】压入【栈】
            然后用parents数组标记节点和其父节点的关系。

        - 某次扫描的时候发现【缩进量变小】了，说明【回到了前面的层】，此时【根据缩进量】找到【当前节点的父节点】(寻找过程中把不满足的父节点弹出栈)
            然后用parents数组标记节点和其父节点的关系。

    这样将数据全部读入后就建立了父子关系。

    💡值得一提的是，在【读入名字】时，我给【每个名字分配了一个序号】，这里的父节点和子节点都是用一个【序号】表示的，以节省一些逻辑比较上的开销。
    -----------------------------------------------

        - SomeBottle 2023.1.21
*/

/*
7-27 家谱处理
    人类学研究对于家族很感兴趣，于是研究人员搜集了一些家族的家谱进行研究。实验中，使用计算机处理家谱。为了实现这个目的，研究人员将家谱转换为文本文件。下面为家谱文本文件的实例：
        John
        Robert
            Frank
            Andrew
        Nancy
            David
    家谱文本文件中，每一行包含一个人的名字。第一行中的名字是这个家族最早的祖先。家谱仅包含最早祖先的后代，而他们的丈夫或妻子不出现在家谱中。每个人的子女比父母多缩进2个空格。以上述家谱文本文件为例，John这个家族最早的祖先，他有两个子女Robert和Nancy，Robert有两个子女Frank和Andrew，Nancy只有一个子女David。

    在实验中，研究人员还收集了家庭文件，并提取了家谱中有关两个人关系的陈述语句。下面为家谱中关系的陈述语句实例：
        John is the parent of Robert
        Robert is a sibling of Nancy
        David is a descendant of Robert
    研究人员需要判断每个陈述语句是真还是假，请编写程序帮助研究人员判断。

输入格式:
    输入首先给出2个正整数N（2≤N≤100）和M（≤100），其中N为家谱中名字的数量，M为家谱中陈述语句的数量，输入的每行不超过70个字符。

    名字的字符串由不超过10个英文字母组成。在家谱中的第一行给出的名字前没有缩进空格。家谱中的其他名字至少缩进2个空格，即他们是家谱中最早祖先（第一行给出的名字）的后代，且如果家谱中一个名字前缩进k个空格，则下一行中名字至多缩进k+2个空格。

    在一个家谱中同样的名字不会出现两次，且家谱中没有出现的名字不会出现在陈述语句中。每句陈述语句格式如下，其中X和Y为家谱中的不同名字：
        X is a child of Y
        X is the parent of Y
        X is a sibling of Y
        X is a descendant of Y
        X is an ancestor of Y
输出格式:
    对于测试用例中的每句陈述语句，在一行中输出True，如果陈述为真，或False，如果陈述为假。
输入样例:
    6 5
    John
    Robert
        Frank
        Andrew
    Nancy
        David
    Robert is a child of John
    Robert is an ancestor of Andrew
    Robert is a sibling of Nancy
    Nancy is the parent of Frank
    John is a descendant of Andrew
输出样例:
    True
    True
    True
    False
    False
代码长度限制
    16 KB
时间限制
    400 ms
内存限制
    64 MB
*/