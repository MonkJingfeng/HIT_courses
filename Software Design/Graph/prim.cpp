#include <cstdio>
#include <cstring>
#define MaxInt 0x3f3f3f3f
#define N 110
//创建map二维数组储存图表，low数组记录每2个点间最小权值，visited数组标记某点是否已访问
int map[N][N],low[N],visited[N];
int n, m;

int prim()
{
    int i,j,pos,min,result=0;
    int tmp[N];//tmp保存low[i]取到当前值时所对应的另一边端点编号
    memset(visited,0,sizeof(visited));

    visited[1]=1;//选择起始点，标记和记录该点
    pos=1;
    for(i=1; i<=n; i++) tmp[i]=1;

    for(i=1; i<=n; i++)//第一次给low数组赋值
        if(i!=pos)
            low[i]=map[pos][i];

    for(i=1; i<n; i++)//再运行n-1次
    {
        min=MaxInt;//找出最小权值并记录位置
        for(j=1; j<=n; j++)
            if(visited[j]==0&&min>low[j])
            {
                min=low[j];
                pos=j;
            }

        result+=min;//最小权值累加
        printf("%d->%d: %d\n",tmp[pos],pos,min);

        visited[pos]=1;//标记该点

        for(j=1; j<=n; j++)//在延伸的点中更新low数组值
            if(visited[j]==0&&low[j]>map[pos][j])
            {
                low[j]=map[pos][j];
                tmp[j]=pos;
            }
    }
    return result;
}

int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {

        memset(map,MaxInt,sizeof(map));//所有权值初始化为最大
        int u,v,w;
        for (int i=0; i<m; i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            map[u][v]=map[v][u]=w;
        }
        printf("%d\n",prim());
    }
    return 0;
}
/*
6 10
1 2 10
1 5 19
1 6 21
2 3 5
2 4 6
2 6 11
3 4 6
4 5 18
4 6 14
5 6 33
*/
