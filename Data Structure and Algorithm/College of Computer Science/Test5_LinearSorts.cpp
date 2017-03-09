#include <bits/stdc++.h>
using namespace std;
int t = 4, n, a[105], b[105], A[105][5], B[105][5]={0}, Start, End;
double c[105];
void Counting_Sort(int (*A)[5],int (*B)[5],int l,int d)   //计数排序，注意指针的用法（指向一维数组的指针） l代表当前比较的是第l位数字
{
    int C[10]= {0},i,j; //C[i]代表了不大于i的元素个数
    for(i=0; i<=9; i++) //置0
        C[i]=0;
    for(j=1; j<=n; j++)
        C[A[j][l]]++;   //A[j][l]属于0...9 ,分别记录每个数字出现的次数
    for(i=1; i<=9; i++)
        C[i]+=C[i-1];  //c[i]代表的是不大于i的元素个数
    for(j=n; j>=1; j--) //从最后一个元素的第l位开始
    {
        for(i=1; i<=d; i++)                //整体存入
            B[C[A[j][l]]][i]=A[j][i];  //找到位置
        C[A[j][l]]--;  //保证相同大小的数字的排序稳定性  后来的在前面
    }
}
void Get_num(int a,int *A)  //获取一个数字的各位数然后倒序存入A中
{
    int i=1;
    while(a)
    {
        A[i++]=a%10;      //从A[1]开始存，存入最低位
        a/=10;
    }
    return ;
}
void Radix_Sort(int (*A)[5],int (*B)[5],int d)  //基数排序
{
    int i;  //表示当前比较第i位，从低位开始，所以从1开始
    for(i=1; i<=d; i++) //一直比较到最后一位
    {
        Counting_Sort(A,B,i,d);
        memcpy(A,B,400*sizeof(int));  //把比较完第i位后的排序结果赋给数组A，从而在原来的基础上继续比较第i+1位
    }
}
void insert_sort(double *A,int l)
{
    int i,j;
    double key;
    for(i=1; i<l; i++)
    {
        key=A[i];
        j=i-1;
        while(j>-1&&A[j]>key)
        {
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=key;

    }
}
void bucket_sort(double *A)//桶排序
{
    int i,j,C[101]= {0};
    double B[101][101]= {0};
    for(i=1; i<=n; i++)
    {
        C[(int)(n*A[i])]++;
        B[(int)(n*A[i])][C[(int)(n*A[i])]-1]=A[i];
    }
    for(i=0; i<n; i++)
        insert_sort(B[i],C[i]);
}
void Counting_Sort(int *A,int *B,int k)//计数排序
{
    int C[1005],i,j;
    for(i=0; i<=k; i++)
        C[i]=0;
    for(j=1; j<=n; j++)
        C[A[j]]++;
    for(i=1; i<=k; i++)
        C[i]=C[i]+C[i-1];
    for(j=n; j>=1; j--)
    {
        B[C[A[j]]]=A[j];
        C[A[j]]--;
    }
}

int main()
{
    freopen("in.txt","r",stdin);
    while (t--) {
        switch (t) {
        case 3:puts("100 随机数据");break;
        case 2:puts("100 正序数据");break;
        case 1:puts("100 逆序数据");break;
        case 0:puts("100 重复数据");break;
        }
        if (t) {
            scanf("%d", &n);
            for (int i=0; i<n; i++) scanf("%d", &a[i]);
            for (int i=0; i<n; i++) {
                c[i] = a[i] / 1000;
                Get_num(a[i], A[i]);
            }
        } else {
            for (int i=0; i<100; i++) a[i] = 10, c[i] = 0.01, Get_num(10, A[i]);
        }
        Start = clock();
        bucket_sort(c);
        End = clock();
        printf("桶排序： %dms\n",End - Start);
        Start = clock();
        Counting_Sort(a, b, 1000);
        End = clock();
        printf("计数排序： %dms\n",End - Start);
        Start = clock();
        Radix_Sort(A, B, 4);
        End = clock();
        printf("基数排序： %dms\n",End - Start);
    }
    return 0;
}
