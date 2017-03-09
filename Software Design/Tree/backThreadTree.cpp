#include <bits/stdc++.h>
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
//后序线索化二叉树
void backThreading(Treep &p) {
    if (p) {
        backThreading(p->left);
        backThreading(p->right);
        if (!p->left) {//前驱线索
            p->Ltag = Thread;
            p->left = pre;
        }
        if (!pre->right) {//后继线索
            pre->Rtag = Thread;
            pre->right = p;
        }
        pre = p;
    }
}
Treep backorderThreading(Treep &rt) {
    Treep thrt;
    if (!(thrt=(Treep)malloc(sizeof(Treenode)))) {
        puts("内存溢出！");
        exit(0);
    }
    thrt->Ltag = Link;
    thrt->Rtag = Thread;    //建头结点
    thrt->right = thrt;    //右指针回指
    if (!rt) {
        thrt->left = thrt;    //若二叉树空，则左指针回指
    } else {
        thrt->left = rt;
        pre = thrt;

        backThreading(rt);        //前序遍历进行线索化

        //thrt->right = pre;        //最后一个节点处理
    }
    return thrt;
}

Treep parent(Treep &thrt,Treep &p) {
    Treep tmp;
    tmp = thrt;
    if (tmp->left == p) {
        return tmp;    //父节点是头结点
    } else {
        tmp = tmp->left;
        while (tmp->left!=p && tmp->right!=p) {
            if (Link == tmp->Rtag)
                tmp = tmp->right;    //如果节点有右节点，那么往右
            else
                tmp = tmp->left;    //如果节点没有右孩子，那么去左孩子，没有左孩子，去前驱，也是走往左
        }
        return tmp;
    }
}
//后序遍历线索二叉树
void backorderTraver(Treep &thrt) {
    Treep p;
    Treep par;
    p = thrt->left;
    while (1) {
        while (Link == p->Ltag)
            p = p->left;
        if (Link == p->Rtag)
            p = p->right;
        else
            break;        //p指向第一个被访问的节点
    }
    while (p != thrt) {
        printf("%d ", p->data);
        par = parent(thrt,p);    //parent是p的双亲:

        if (thrt == par)        //1.若parent是thrt，即p是根节点，则无后继
            p = thrt;
        else if(p==par->right || Thread==par->Rtag)    //2.若p是双亲的右孩子，或者双亲只有左孩子，则后继为双亲
            p = par;
        else {
            while(par->Rtag==Link) {        //3.若p是有兄弟的左孩子，则后继为双亲的右子树上按照后续遍历访问的第一个节点
                par = par->right;
                while (par->Ltag == Link) {
                    par = par->left;
                }
            }
            p = par;
        }
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
    thrt = backorderThreading(rt);//建立后序线索二叉树
    backorderTraver(thrt);//后序遍历二叉树
    puts("");
    return 0;
}

//1 2 0 3 4 0 0 5 0 0 6 7 9 0 0 10 0 0 8 0 0
//1 2 0 3 0 4 0 0 5 6 0 0 7 8 10 0 0 9 0 0 0
