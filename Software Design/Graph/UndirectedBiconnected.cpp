#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
typedef pair<int, int> PII;
//保存边的结构体 u，v分别为起点和终点
struct Edge
{
	int u,v;
	Edge(){}
	Edge(int u, int v):u(u),v(v){}
};
vector<Edge> G[MAXN];//保存图的结构 G[i]存储与编号为i的顶点相连的边
//往图中加边 一条无向边拆成两条有向边
void addedge(int u, int v)
{
	G[u].push_back(Edge(u, v));
	G[v].push_back(Edge(v, u));
}
int n, m, tot, vbs, ves;
//dfn(u)为u在深度优先搜索树中被遍历到的次序号 low(u)为u经过一条其后代组成的路径和回退边，所能到达的最小深度的顶点的编号
int dfn[MAXN], low[MAXN], vis[MAXN];
bool cut[MAXN];//记录一个点是否为割点
deque<PII> stak;
//记录点双连通分支的数据结构
set<int> belongs[MAXN];
void mark(int u, int id)
{
	if(belongs[u].find(id) == belongs[u].end())
	{
		belongs[u].insert(id);
		printf("%d ", u);
	}
}
//记录桥的数据结构
set< PII > bridge;
void addbrige(int u, int v)
{
	if(u > v) swap(u, v);
	bridge.insert(PII(u, v));
}
bool isbridge(int u, int v)
{
	if(u > v) swap(u, v);
	if(bridge.find(PII(u, v)) == bridge.end()) return false;
	return true;
}
void tarjan(int now, int pre)
{
	dfn[now] = low[now] = ++tot;
	int child = 0;
	for (int i = 0, len = G[now].size(); i < len; i++)
	if(G[now][i].v != pre && dfn[G[now][i].v] < dfn[now])//防止重复计算无向图中同一条边及回退边
                                                         //因为dfs过程中,遇到的顶点只有两种情况,dfn[w]=0 新点, dfn[w]<dfn[u] u,w 是回退边
                                                         //二者的共同点是 dfn[w] < dfn[u],这两种边包括了G的所有边,因此对其他边的访问是重复的
	{
		int to = G[now][i].v;
		stak.push_back(PII(now, to));//新边压栈
		if(dfn[to] == 0)//如果未访问过，是新节点
		{
			child++;
			tarjan(to, now);//递归计算
			low[now] = min(low[now], low[to]);//更新当前结点的low值
			//一个顶点now是割点，当且仅当满足以下两个条件之一1.now为树根，且有多于一个子树2.now不为树根且满足存在(now,to)使得dfn(now)<=low(to)
			if((pre == -1 && child > 1) || (pre != -1 && dfn[now] <= low[to]))
				cut[now] = true;
            //一条无向边(now,to)是桥，当且仅当now为to在搜索树中的父亲，且满足dfn(now)<low(to)
			if(low[to] > dfn[now])
				addbrige(now, to);
            //如果有环
			if(low[to] >= dfn[now])
			{
				PII tmp;
				printf("biconnectivity found %d:\n", ++vbs);
				//如果满足now为割点，把边从栈顶依次取出直至取到(now,to)，取出的这些边与其关联的点，组成一个点双连通分支
				//割点可以属于多个点双连通分支
				while(true)
				{
					tmp = stak.back();
					stak.pop_back();
					mark(tmp.first, vbs);
					mark(tmp.second, vbs);
					if(tmp == PII(now, to))
						break;
				}
				printf("\n");
			}
		}
		else if(to != pre)
			low[now] = min(low[now], dfn[to]);
	}
}
//深度遍历，求边双连通分支
void dfs_no_bridge(int now)
{
	vis[now] = true;
	printf("%d ", now);

	for (int i = 0, len = G[now].size(); i < len; i++)
		if(!isbridge(now, G[now][i].v) && !vis[G[now][i].v])//若此边不是桥且未访问过另一个点
		{
			dfs_no_bridge(G[now][i].v);//递归求解
		}
}

int main()
{
	scanf("%d%d", &n, &m);
	//初始化
	for (int i = 1; i <= n; i++)
		G[i].clear(),belongs[i].clear();
	bridge.clear();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(cut, 0, sizeof(cut));
	memset(vis, 0, sizeof(vis));
	stak.clear();
	vbs = ves = tot = 0;

	//建图
	int u, v;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		addedge(u, v);
	}

    //点连通性
	printf("Point biconnectivity:\n");
	for (int i = 1; i <= n; i++) if(dfn[i] == 0)
		tarjan(i, -1);

	printf("Briges:\n");
	for (set<PII>::iterator it = bridge.begin(); it != bridge.end(); it++)
	{
		printf("%d - %d\n", (*it).first, (*it).second);
	}

    //边连通性
	printf("Edge biconnectivity:\n");
	for (int i = 1; i <= n; i++) if(!vis[i])
	{
		printf("biconnectivity found %d:\n", ++ves);
		dfs_no_bridge(i);
		printf("\n");
	}

	return 0;
}


/*
sample 1:
8 9
1 2
2 3
3 4
1 4
4 5
5 6
6 7
7 8
5 8

sample 2:
5 4
1 2
2 3
3 4
4 5

*/
