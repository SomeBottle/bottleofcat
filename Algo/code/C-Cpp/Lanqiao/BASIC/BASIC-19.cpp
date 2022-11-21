#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int strLen; // 字符串长度
    scanf(" %d", &strLen);
    vector<char> myStr(strLen); // 根据长度初始化字符vector长度
    char temp;
    for (int i = 0; i < strLen; i++)
    { // 从标准输入读入字符, 忽略前面的空白符\n
        scanf(" %c", &temp);
        myStr[i] = temp;
    }
    // 字符串长度是否是奇数
    bool isOdd = strLen & 1;
    // 是否已经有【不成对】的字符了，对于【奇数长】的回文串中，有且仅能有一个不成对的字符，比如acbca中的b
    bool hasAloneChar = false;
    // 字符串中间一位的下标
    int middleInd = (strLen - 1) / 2;
    // 纪录交换次数
    int swapCount = 0;
    // 开始处理字符串
    // former最先选中一个字符
    /*
        former从第0个字符扫描到字符串中间的一位
        为什么只用到中间? 我经过多次实践才得出这个推论：
            💡在交换相邻字符的时候，
                - 如果右半侧【有两个相同的字符】，总会有【其中一个】被“挤”到左侧
                - 而如果右半侧有【一个落单的字符】，它则总会被“挤”到正中心
    */
    for (int former = 0; former <= middleInd; former++)
    {
        int destInd = strLen - 1 - former; // 算出和former对称的下标，也就是要将latter的字符一直交换到下标为destInd
        // 如果和former对称的下标destInd指向的字符也是一致的，已经配对了，就不用接着往下了
        if (myStr[former] == myStr[destInd])
            continue;

        int latter = -1;
        // 找到一个【和former对应的字符相同的字符】，i从former的下一位开始扫描到字符串尾部
        for (int i = former + 1; i < strLen; i++)
        {
            if (myStr[former] == myStr[i])
            {
                int symmetry = strLen - 1 - i; // 算出与i下标对称的下标
                /*
                    比如aabba, 如果former指向的是第二个a, i此时会等于最后一个a的下标，
                    但是这个a已经和第一个a对称了，这个时候就需要跳过了。
                */
                if (myStr[i] != myStr[symmetry])
                {
                    latter = i; // 找到了相同的字符
                    break;
                }
            }
        }
        // latter如果还是-1，说明没找到与former相同的字符, former指向的这个字符【落单了】
        if (latter == -1)
        {
            // 对于【落单字符】的处理
            // 在【回文串长度为奇数】时，有且仅能有【一个落单字符】
            if (isOdd && !hasAloneChar)
            {
                destInd = middleInd; // 唯一的落单字符【只能在回文串的最中间】, 所以将终点下标设为middleInd
                hasAloneChar = true; // 标记已经有落单字符了
            }
            else
            {
                // 其他情况，那就不可能形成回文串了，程序结束
                cout << "Impossible";
                return 0;
            }
        }
        // 接下来将
    }
    return 0;
}