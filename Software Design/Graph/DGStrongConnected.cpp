#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000;
//保存边的结构体 u，v分别为起点和终点
struct Edge
{
	int u, v;
	Edge(){}
	Edge(int u, int v):u(u),v(v){}
};
vector<Edge> G[MAXN];//保存图的结构 G[i]存储与编号为i的顶点相连的各顶点编号
vector<int> sc[MAXN];//保存强连通分量的结构 sc[i]存储第i个强连通分量的各顶点编号
deque<int> stak;//顺序保存遍历的边
bool instak[MAXN];
int n, m, dfn[MAXN], low[MAXN],tot,sccnt;
//往图中加边
void addedge(int u, int v)
{
	G[u].push_back(Edge(u,v));
}


void tarjan(int u)
{
	dfn[u] = low[u] = ++tot;
	stak.push_back(u);
	instak[u] = true;
	int v;
	for (int i = 0, len = G[u].size(); i < len; i++)//枚举每一条边
	{
		int v = G[u][i].v;
		if (dfn[v] == 0)//如果未访问过，是新节点
		{
			tarjan(v);//递归计算
			if(low[u] > low[v])//更新当前结点的low值
				low[u] = low[v];
		}
		else if(instak[v] && dfn[v] < low[u])//如果v还在栈内，更新当前结点的low值
			low[u] = dfn[v];
	}
	if(dfn[u] == low[u])//找到一个完整的环，以u为根的搜索子树上所有节点是一个强连通分量
	{
		sccnt++;
		while(true)
		{
			v = stak.back();
			stak.pop_back();
			sc[sccnt].push_back(v);
			instak[v] = false;
			if(v == u) break;
		}
	}
}




int main()
{
    //初始化
	for (int i = 1; i <= n; i++)
		G[i].clear(),sc[i].clear();
	memset(instak, 0, sizeof(instak));
	stak.clear();
	sccnt = 0;
	tot = 0;

	//建图
	scanf("%d%d",&n,&m);
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		addedge(u,v);
	}

	for (int i = 1; i <= n; i++) if(dfn[i] == 0) //防止输入不连通
		tarjan(i);

	for (int i = 1; i <= sccnt; i++) {
	    printf("强连通分量%d: ", i);
		for (int j = 0, len = sc[i].size(); j < len; j++)
			printf("%d%c", sc[i][j], j == len-1? '\n':' ');
	}
	return 0;
}

/*
sample 1:
6 8
1 2
1 3
2 4
3 4
3 5
4 1
4 6
5 6

*/
