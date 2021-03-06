#include <cstdio>
#include <cstring>
#include <algorithm>
int fa[205];
using namespace std;
struct edge
{
    int u,v,w;
}e[205*205];
bool cmp(edge a,edge b)
{
    if (a.w>b.w) return false;
    return true;
}
int find(int x)//并查集维护点集合
{
    if (fa[x]==x) return x;
    fa[x]=find(fa[x]);//路径压缩，使每个树只有两层
    return fa[x];
}
int main()
{
    int i,j,m,n,k,u,v,w,cnt,ans;
    scanf("%d%d",&n,&m);
    cnt=0;
    for (i=1;i<=n;i++)  fa[i]=i;
        for (i=1;i<=m;i++)
        {

            scanf("%d%d%d",&u,&v,&w);
            e[cnt].u=u;
            e[cnt].v=v;
            e[cnt].w=w;
            cnt++;
        }
    sort(e,e+cnt,cmp);//按边权升序排序
    k=0;i=0;ans=0;
    while (k<n-1)//找n-1条边
    {
        if (i==cnt) break;
        if (find(e[i].u)!=find(e[i].v))
        {
            k++;
            ans+=e[i].w;
            printf("%d->%d: %d\n",e[i].u,e[i].v,e[i].w);
            fa[find(e[i].u)]=find(e[i].v);
        }
        i++;
    }
    printf("%d\n",ans);
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
