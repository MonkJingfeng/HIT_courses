#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn = 233;
const int inf = 0x3f3f3f3f; //极大值，inf+inf不会爆int
int way[maxn][maxn],dis[maxn],pre[maxn];
bool vis[maxn];
int n,m;
void dijkstra(int s) {
    //初始化dis及pre数组，不与源点相邻的点均特殊赋值
    for (int i=0; i<n; i++) {
        dis[i] = way[s][i];
        if (i == s || dis[i] == inf) pre[i] = -1;
        else pre[i] = s;
        vis[i] = false;
    }

    //标记源点
    vis[s] = true;

    int k,tmp;
    for (int i=0; i<n; i++) {
        //找出未标记（即不在集合中）中离源点最近的点
        tmp = inf;
        for (int j=0; j<n; j++)
            if (!vis[j] && tmp > dis[j]) {
                k = j;
                tmp = dis[j];
            }

        //若所有可到达的点都在集合中，跳出循环
        if (tmp == inf)
            break;

        //标记这个最近的点，以其为路径中转点，更新不在集合中的点到源点的最短路径长
        vis[k] = true;
        for (int j=0; j<n; j++)
            if (!vis[j] && dis[j] > dis[k] + way[k][j]) {
                //如果s->k及k->j的长度小于现有的s->j，更新数据
                dis[j] = dis[k] + way[k][j];
                //记录更新后的中转点
                pre[j] = k;
            }
    }
}

//pre[i]记录i点之前的结点，递归输出路径
void printPath(int t) {
    if (pre[t] != -1)
        printPath(pre[t]);
    //输出当前点
    printf(" %d",t);
}

int main() {
    //freopen("in.txt","r",stdin);
    int a,b,s,t,x;
    printf("请输入图的结点数和边数：");
    scanf("%d%d",&n,&m);

    //初始化邻接矩阵，编号从0开始建图
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            if(i == j) way[i][j] = 0;
            else way[i][j] = inf;
        }

    printf("请依次输入出发地编号，目标地编号以及两地间距离（编号从0到n-1,边权不可为负）：\n");
    for (int i=0; i<m; i++) {
        scanf("%d%d%d",&a,&b,&x);
        //避免重边等不规则输入对程序造成的影响
        if (way[a][b] > x)
            way[a][b] = x;
        if (x < 0) {
            puts("出现负边权！");
            return 0;
        }
    }

    puts("邻接矩阵建立完成如下（没有对应路径则表示为0x3f3f3f3f）：");
    //输出建立成功的邻接矩阵
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            printf("%d%c",way[i][j],j==n-1?'\n':' ');

    printf("请输入源点编号：");
    scanf("%d",&s);

    dijkstra(s);
    //从0到n-1遍历，分别打印当前点为汇点时的最短路径长和最短路径。
    for (int i=0; i<n; i++) {
        printf("\n当终点为%d: \n",i);
        if (i == s) {
            printf("最短路径长为0。\n");
            printf("最短路径为：%d。\n",i);
            continue;
        }
        t = i;
        //判断s->t的距离是否是有效值
        if(dis[t] == inf)
            printf("不连通。\n");
        else {
            printf("最短路径长为%d。\n",dis[t]);
            printf("最短路径为:");
            printPath(t);
            puts("。");
        }
    }
    return 0;
}
