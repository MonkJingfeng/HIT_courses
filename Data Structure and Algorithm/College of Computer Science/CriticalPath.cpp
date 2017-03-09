#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn = 2333;
int head[maxn], cnt, n, m, ind[maxn], ve[maxn], vl[maxn], e[maxn*maxn*2], l[maxn*maxn*2], st[maxn*maxn*2];
stack<int> T;
struct Edge
{
	int v,next;
	int w;
} edge[maxn*maxn*2];
void add(int u,int v,int w)      //邻接表形式存储
{
	edge[cnt].v=v;
	edge[cnt].w=w;
	edge[cnt].next=head[u];
	head[u]=cnt++;
}
void init()                      //变量初始化

{
	memset(head,-1,sizeof head);
	cnt = 0;
	while (!T.empty())
        T.pop();
	memset(vl,0x3f,sizeof vl);
	memset(l,0x3f,sizeof l);
}
void output()
{
    puts("活动   起点  终点   e[i]   l[i]   l[i]-e[i] 是否为关键路径");
    puts("-----------------------------------------------------------");
    for (int i=0; i<cnt; i++) {
        printf("%4d   %4d  %4d  %4d   %4d       %4d        ",i+1,st[i]+1,edge[i].v+1,e[i],l[i],l[i]-e[i]);
        if (l[i] == e[i])
            puts("√");
        else puts("×");
        puts("-----------------------------------------------------------");
    }
}
int topo()	                    //拓扑排序求ve
{
	stack<int> s;
	int cnt = 1;
	for (int i=0; i<n; i++)
        if (ind[i] == 0) {
            s.push(i);
            break;
        }
    while (!s.empty()) {
        int j = s.top(); s.pop();
        T.push(j);
        for (int p=head[j]; ~p; p=edge[p].next) {
            int v = edge[p].v;
            if (--ind[v] == 0) { //如果入度为0，入栈
                s.push(v);
                cnt++;
            }
            ve[v] = max(ve[v], edge[p].w+ve[j]);
        }
    }
	return cnt;
}
void getCriticalPath()	        //求最晚开始时间
{
	if (topo() < n) {           //存在环路
	    puts("Circle!");
        return;
	}
	int j = T.top(); T.pop();   //确定最后一个结点的vl
    vl[j] = ve[j];
    while (!T.empty()) {        //逆拓扑序求vl
        j = T.top(); T.pop();
        for (int p=head[j]; ~p; p=edge[p].next) {
            int k = edge[p].v;
            vl[j] = min(vl[j], vl[k]-edge[p].w);
        }
    }
	for (int i=0; i<n; i++)     //根据vl,ve求e,l
        for (int p=head[i]; ~p; p=edge[p].next) {
            e[p] = ve[st[p]=i];
            int k = edge[p].v;
            l[p] = vl[k] - edge[p].w;
        }
        output();
}
int main() 
{
	  //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    init();
    int x, y, z;
    while (m--) {
        scanf("%d%d%d",&x,&y,&z);
        x--, y--;
        ind[y]++;
        add(x, y, z);
    }
    getCriticalPath();
	  return 0;
}
