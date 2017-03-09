#include <bits/stdc++.h>
const int maxSize = 6666;
#define elementType int
struct triple {
    int i, j;
    elementType e;
} ;
struct matrix {
    triple data[maxSize];
    int mu, nu, tu; //分别表示矩阵的行数、列数、非零元素个数
} ;
int num[maxSize];   //表示矩阵M中第col列非零元素的个数
int cpot[maxSize];  //表示矩阵M中第col列第一个非零元素在T中的恰当位置
void printMatrix(matrix T) {
    puts("    i     j     v");
    for (int i=1; i<=T.tu; i++) {
        printf("%5d %5d %5d\n", T.data[i].i, T.data[i].j, T.data[i].e);
    }
}
void transposMatrix(matrix M, matrix &T) {  //O(nu*tu)
    T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
    if (T.tu) {
        int q = 1;
        for (int col=1; col<=M.nu; ++col)
            for (int p=1; p<=M.tu; ++p) {
                if (M.data[p].j == col) {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    ++q;
                }
            }
    }
}
void fastTransposMatrix(matrix M, matrix &T) {  //O(nu+tu)
    T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
    if  (T.tu) {
        for (int col = 1; col<=M.nu; ++col)
            num[col] = 0;
        for (int t=1; t<=M.tu; ++t)
            ++num[M.data[t].j];
        cpot[1] = 1;
        for (int col=2; col<M.nu; ++col)
            cpot[col] = cpot[col-1] + num[col-1];
        for (int p=1; p<=M.tu; ++p) {
            int col = M.data[p].j;
            int q = cpot[col];
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
}
int main()
{
    matrix M, T;
    printf("请分别输入给定矩阵行数、列数、非零元素个数：");
    scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
    printf("请依次输入三元组：\n");
    for (int i=1; i<=M.tu; i++) {
        scanf("%d %d %d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
    }
    puts("初始矩阵如下：");
    printMatrix(M);
    puts("朴素转置：");
    transposMatrix(M, T);
    printMatrix(T);
    puts("优化转置：");
    transposMatrix(M, T);
    printMatrix(T);
    return 0;
}
