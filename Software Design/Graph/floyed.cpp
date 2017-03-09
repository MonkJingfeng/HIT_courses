#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=110;
const int INF=100000000;
int  dist[maxn][maxn];
int  n, m, num, minc;
void floyd()
{
    for(int k=1; k<=n; k++)//枚举中间点
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                if(dist[i][j]>dist[i][k]+dist[k][j])
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
}
bool check()
{
    for(int i=1; i<=n; i++)
        if (dist[i][i] < 0)//如果i到i的最短路径长小于0，必定存在负圈使得自身更新
        {
            printf("存在负权回路！\n");
            return false;
        }
    return true;
}

int main()
{
    scanf("%d%d", &n, &m);
    int x, y, c;
    //初始化
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            dist[i][j] = INF;
        dist[i][i] = 0;
    }
    //建图
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &x,&y,&c);
        dist[x][y] = dist[y][x] = c;
    }

    floyd();

    if (check())//如果无负圈，输出整张图中两两顶点间最短路径长
        for (int i = 1; i <= n;i++)
            for (int j = 1; j <= n; j++)
                printf("%d%c", dist[i][j]==INF? -1: dist[i][j], j == n? '\n':' ');

    return 0;
}
/*
4 4
1 2 10
2 3 10
3 4 -10
1 4 10

*/
