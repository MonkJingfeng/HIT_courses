//开放定址
/*------------------------------------------------------------------
*形成地址序列的公式是：Hi=（H（key）+di）% m，其中m是表长，di是增量。
*一种做法是di =1，2，…，m-1 称为线性探测再散列，
*其特点是逐个探测表空间，只要散列表中有空闲空间，就可解决碰撞，
*缺点是容易造成“聚集”，即不是同义词的关键字争夺同一散列地址。
-------------------------------------------------------------------*/
#include <bits/stdc++.h>
using namespace std;
unsigned int hash_BKDE(char *str)
{
    unsigned int seed = 17;
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7fffffff);
}
double k = (double)(rand() % 999) / 1000;//随机生成小数
unsigned int hash_rand(unsigned int value)
{
    double a = k * value;
    double n = (a - (int)a) * 64;//取小数部分与常数相乘
    unsigned int seed = (int)n;
    return seed;
}
unsigned int Hash(char *str)
{
    return hash_rand(hash_BKDE(str));
}
class HashTable
{
public:
    HashTable();
    ~HashTable();
    void insert(char*);
    bool find(char*);
private:
    char **Arr;//二维数组用于保存字符串
    int ArrSize;//散列表单元个数
};
HashTable::HashTable()
{
    ArrSize = 32768;
    Arr = new char*[64];
    for (int i=0; i<64; i++)
    {
        Arr[i] = new char[100];
        Arr[i] = NULL;
    }
}
HashTable::~HashTable()
{
    for (int i=0; i<64; i++)
        delete[] Arr[i];
    delete[] Arr;
}
void HashTable::insert(char* s)
{
    unsigned int pos = Hash(s);//计算散列地址位置
    //寻找空位，插入存储
    while (Arr[pos] != NULL)
    {
        pos = pos + 1;
    }
    Arr[pos] = s;
}
bool HashTable::find(char *s)
{
    unsigned int pos = Hash(s);//计算散列地址位置
    while (Arr[pos] != NULL)
    {
        if (Arr[pos] == s) return true;
        pos = pos + 1;
    }
    return false;
}
int main()
{
    bool a[20];
    int n, m;
    char *s = new char[100];
    HashTable H;
    cout << "输入字符串个数n和待查字符串个数m：";
    cin >> n >> m;
    cout << "输入n个字符串：";
    for (int i=1; i<=n; i++)
    {
        cin >> s;
        H.insert(s);
    }
    for (int i=1; i<=m; i++)
    {
        cout << "输入要查找的字符串：" ;
        cin >> s;
        if (H.find(s)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}
/*
4 9
a
ans
and
hellocpp
a
b
an
as
ans
and
hellocbb
hellocpp
ande
*/
