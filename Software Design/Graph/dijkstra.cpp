//Dijksta算法中，如果我们采用的是邻接矩阵来存的，第一点浪费的空间比较多，第二点我们知道算法的时间复杂度在O(2*|E|+|V|*|V|)
//首先我们可以优化存储结构，采用邻接表来存储，时间复杂度=O(2*|E|+|V|^2/2)
//其次我们可以用优先队列来排序大小，堆的性质决定取最小值操作用时由O(n)优化为O(logn)，总时间复杂度=O(2*|E|+|V|*log|V|)
//注意不能处理带负权的图，每条边加上一个常数后可能导致错误结果
#include <bits/stdc++.h>
#define maxn 1020
#define INF 0x7f7f7f7f
using namespace std;
typedef pair<int, int> PII;
struct Edge
{
	int u, v, l;//l 为边的长度
	Edge(){}
	Edge(int u,int v, int l):u(u),v(v),l(l){}
};
struct Node//priority_queue 的记录
{
	int v, l;//v顶点编号，l距起点距离
	Node(){}
	Node(int v, int l):v(v),l(l){}
	bool operator < (const Node &a) const//priority_queue 的优先级和 < 相反
	{
		return l > a.l;
	}
};
vector<Edge> G[maxn];
priority_queue<Node> pq;
int dist[maxn],vis[maxn],tot;
void add_edge(int u, int v, int l)
{
	G[u].push_back(Edge(u, v, l));
}
//start s
void dijstra(int s)
{
    //初始化
	memset(dist, INF, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	while(!pq.empty()) pq.pop();
	//起点进队
	pq.push(Node(s, 0));
	while(!pq.empty())
	{
		const Node nd = pq.top();//取出顶点
		pq.pop();
		if(vis[nd.v]) continue;//若访问过，直接操作下一个顶点。在没访问到前，同一个点可能进队多次
		vis[nd.v] = true;//若未访问，标记此点
		dist[nd.v] = nd.l;//更新此点的dist数组
		for(int i = 0, len = G[nd.v].size(); i < len; i++)//从邻接表出发扩展与其相连的顶点
		{
			Edge& e = G[nd.v][i];
			if(!vis[e.v])//如果该点未访问过，加上当前边的距离进队
			{
				pq.push(Node(e.v, nd.l + e.l));
			}
		}
	}
}


int main()
{
	int n, m;
	scanf("%d%d", &n,&m);

	int u, v, c;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		add_edge(u,v,c);
		add_edge(v,u,c);
	}

	dijstra(1);
	printf("以顶点1为起点距各点的最短路径：\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d%c", dist[i], i==n?'\n':' ');
	}

	return 0;
}
/*
3 3
1 2 5
2 3 5
3 1 2
*/
