#include<bits/stdc++.h>
using namespace std;

typedef enum PointerTag {Link,Thread};    //Link==0,Thread==1;线索
typedef struct treenode
{
    struct treenode *left;
    int data;
    struct treenode *right;
    PointerTag Ltag,Rtag;    //左右标志
}Treenode,* Treep;
Treep pre;
//初始化二叉树
void init_tree(Treep &rt) {
    rt = NULL;
}
//创建二叉树
void create_tree(Treep &rt) {
    int data;
    scanf("%d", &data);
    if (!data) {
        rt = NULL;
    } else {
        rt = (Treep)malloc(sizeof(Treenode));
        rt->data = data;
        rt->Ltag = rt->Rtag = Link;
        create_tree(rt->left);
        create_tree(rt->right);
    }
}
//先序遍历二叉树
void pre_order(Treep &rt) {
    if (rt) {
        printf("%d ", rt->data);
        pre_order(rt->left);
        pre_order(rt->right);
    }
}
//先序线索化二叉树
void preThreading(Treep &p) {
    if (p) {
        if (!p->left) {//前驱线索
            p->Ltag = Thread;
            p->left = pre;
        }
        if (!pre->right) {//后继线索
            pre->Rtag = Thread;
            pre->right = p;
        }
        pre = p;
        if (Link == p->Ltag)
            preThreading(p->left);
        if (Link == p->Rtag)
            preThreading(p->right);
    }
}

Treep preorderThreading(Treep &rt) {
    Treep thrt;
    if (!(thrt = (Treep)malloc(sizeof(Treenode)))) {
        puts("内存溢出！");
        exit(0);
    }
    //建头结点 右指针回指
    thrt->Ltag = Link, thrt->Rtag = Thread, thrt->right = thrt;
    if (!rt) {//若二叉树空，则左指针回指
        thrt->left = thrt;
    } else {
        thrt->left = rt;
        pre = thrt;

        preThreading(rt);   //先序遍历进行线索化

        pre->right = thrt;        //最后一个节点处理
        pre->Rtag = Thread;
        //thrt->right = pre;
    }
    return thrt;
}

//先序遍历线索二叉树
void preorderTraver(Treep &thrt) {
    Treep p;
    p = thrt->left;
    while (p != thrt) {
        printf("%d ", p->data);
        if (Link == p->Ltag)
            p = p->left;
        else
            p = p->right;
    }
}

int main()
{
    Treep rt;
    init_tree(rt);
    puts("先序输入二叉树，0表示空：");
    create_tree(rt);

    //先序遍历二叉树
    puts("先序遍历序列是:");
    pre_order(rt);
    puts("");

    Treep thrt;
    thrt = preorderThreading(rt);//建立先序线索二叉树
    preorderTraver(thrt);//先序遍历二叉树
    puts("");
    return 0;
}

//1 2 0 3 4 0 0 5 0 0 6 7 9 0 0 10 0 0 8 0 0
//1 2 0 3 0 4 0 0 5 6 0 0 7 8 10 0 0 9 0 0 0
