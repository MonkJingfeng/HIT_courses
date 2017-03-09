#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1005;
int nodenum, edgenum, original; //�㣬�ߣ����

struct Edge { //��
	int u, v;
	int cost;
} ;

Edge edge[maxn];
int dis[maxn], pre[maxn];

bool Bellman_Ford() {
	for(int i = 1; i <= nodenum; ++i) //��ʼ��
		dis[i] = (i == original ? 0 : inf);
	for(int i = 1; i <= nodenum - 1; ++i)
		for(int j = 1; j <= edgenum; ++j)
			if(dis[edge[j].v] > dis[edge[j].u] + edge[j].cost) { //�ɳڣ�˳��һ�����ܷ�~��
				dis[edge[j].v] = dis[edge[j].u] + edge[j].cost;
				pre[edge[j].v] = edge[j].u;
			}
			bool flag = 1; //�ж��Ƿ��и�Ȩ��·
			for(int i = 1; i <= edgenum; ++i)
				if(dis[edge[i].v] > dis[edge[i].u] + edge[i].cost) {
					flag = 0;
					break;
				}
				return flag;
}

void print_path(int root) { //��ӡ���·��·��
    stack<int> stk;
	while (root != pre[root]) { //ǰ��
		stk.push(root);
		root = pre[root];
	}
	if (root == pre[root])
		printf("%d-->", root);
    while (stk.size() > 1) {
        printf("%d-->", stk.top());
        stk.pop();
    }
    printf("%d\n", stk.top());
}

int main()
{
	scanf("%d%d%d", &nodenum, &edgenum, &original);
	pre[original] = original;
	for(int i = 1; i <= edgenum; ++i) {
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
	}
	if(Bellman_Ford())
		for(int i = 1; i <= nodenum; ++i) { //ÿ�������·
			printf("%d\n", dis[i]);
			printf("Path:");
			print_path(i);
		}
	else
		printf("have negative circle\n");
	return 0;
}
