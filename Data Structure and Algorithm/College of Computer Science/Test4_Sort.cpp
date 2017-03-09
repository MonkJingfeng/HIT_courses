#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int a[maxn], n;
time_t now, t;
char hlp[11][55] = {"","直接插入排序","折半插入排序","冒泡排序","快速排序","选择排序","堆排序","基数排序"};
void insert_sort()
{
    for (int i=2,j; i<=n; i++) {
        int key = a[i];
        for (j=i; j>0&&a[j-1]>key; j--)
            a[j] = a[j-1];
        a[j] = key;
    }
}
void binary_insert_sort()
{
    for (int i=2; i<=n; i++) {
        a[0] = a[i];
        int l = 1, r = i-1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (a[0] < a[m]) r = m - 1;
            else l = m + 1;
        }
        for (int j=i-1; j>=r+1; j--)
            a[j+1] = a[j];
        a[r+1] = a[0];
    }
}
void bubble_sort()
{
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n-i; j++)
            if (a[j] > a[j+1])
                swap(a[j], a[j+1]);
}
void quick_sort(int l, int r)
{
    int i = l, j = r, mid = a[l+rand()%(r-l+1)];
    while (i <= j) {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++, j--;
        }
    }
    if (l < j) quick_sort(l, j);
    if (i < r) quick_sort(i, r);
}
void select_sort()
{
    for (int i=1; i<=n; i++) {
        int l = i;
        for (int j=i+1; j<=n; j++)
            if (a[j] < a[l])
                l = j;
        swap(a[i], a[l]);
    }
}
void build_heap(int i, int n)                   //建立最大堆
{
    int tmp = a[i], j = 2 * i;
    while (j <= n) {
        if (j < n && a[j+1] > a[j])             //在左右孩子中找最大的
            j++;
        if (a[j] <= tmp) break;
        a[i] = a[j];                            //把较大的孩子向上移动，替换父节点
        i = j;
        j = 2 * i;
    }
    a[i] = tmp;
}
void heap_sort()
{
    for (int i=n/2; i>=1; i--)
        build_heap(i, n);
    for (int i=n; i>=2; i--) {
        swap(a[1], a[i]);                       //每次将最大元素调后
        build_heap(1, i-1);
    }
}
int max_bit()                                   //辅助函数，求数据最大位数
{
    int d = 1, p = 10;
    for (int i=1; i<=n; i++) {
        while (a[i] >= p) {
            p *= 10;
            d++;
        }
    }
    return d;
}
void radix_sort()
{
    int d = max_bit();
    int *tmp = new int[n+1];
    int *cnt = new int[10];
    int radix = 1;
    for (int i=1; i<=d; i++) {
        for (int j=0; j<10; j++)                //每次分配前，清空计数器
            cnt[j] = 0;
        for (int j=1; j<=n; j++) {
            int k = (a[j] / radix) % 10;        //统计每个桶中的记录数
            cnt[k]++;
        }
        for (int j=1; j<10; j++)
            cnt[j] += cnt[j-1];
        for (int j=n; j>=1; j--) {
            int k = (a[j] / radix) % 10;
            tmp[cnt[k]] = a[j];
            cnt[k]--;
        }
        for (int j=1; j<=n; j++)
            a[j] = tmp[j];
        radix *= 10;
    }
    delete[] tmp;
    delete[] cnt;
}
void show()             //输出数组
{
    for (int i=1; i<=n; i++)
        printf("%5d%c",a[i],i==n?'\n':' ');
}
void calc()             //计算时间
{
    t = clock();
    printf("\t\tTime used = %.2f\n", (double)(t - now) / CLOCKS_PER_SEC);
    now = t;
}
int main()
{
    puts("请输入测试数目n:");
    srand(time(NULL));
    char ch[55];
    while (~scanf("%d",&n)) {
        if (n < 1) break;
        now = clock();
        for (int i=1; i<=n; i++)
            a[i] = rand()%999 + 1;
        puts("初始数组如下：");
        show();
        puts("请选择排序方式：");
        scanf("%s",ch);
        bool flag = true;
        while (flag) {
            if (ch[0] < '1' || ch[0] > '7')
                puts("请输入合法选择！");
            else {
                printf("%s",hlp[ch[0]-'0']);
                switch(ch[0]) {
                    case '1':insert_sort();break;
                    case '2':binary_insert_sort();break;
                    case '3':bubble_sort();break;
                    case '4':quick_sort(1, n);break;
                    case '5':select_sort();break;
                    case '6':heap_sort();break;
                    case '7':radix_sort();break;
                }
                flag = false;
                calc();
                puts("排序后数组如下：");
                show();
            }
        }
        puts("请输入待测试数目n:");
    }
    return 0;
}
