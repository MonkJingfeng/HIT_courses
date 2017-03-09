#include <bits/stdc++.h>
#define Thread 1
#define Link 0
using namespace std;
struct BinaryTreeNode {
    int data;
    BinaryTreeNode *lson, *rson;
    bool lTag, rTag;
    BinaryTreeNode(){lson=rson=NULL;}
} ;
typedef BinaryTreeNode BT;
BT* pre;
BT* Setup()                                 //先序建立二叉树
{
    BT *bt;
    char ch;
    scanf("%c",&ch);
    if (ch == '#') bt = NULL;
    else {
        bt = new BT();
        if (!bt) exit(OVERFLOW);            //若内存满，则报错内存溢出
        bt->data = ch;
        bt->lTag = bt->rTag = Link;         //初始化标志位
        bt->lson = Setup();                 //递归建立二叉树
        bt->rson = Setup();
    }
    return bt;
}
void visit(char ch)                         //打印结点数据
{
	printf("%c",ch);
}
void QAQ(BT *rt)                            //递归中序遍历二叉树
{
    if (rt) {
        QAQ(rt->lson);
        visit(rt->data);
        QAQ(rt->rson);
    }
}
//按中序遍历线索化
void InThreading(BT* p)
{
	if (p) {
		InThreading(p->lson);               //左子树线索化
		if (!p->lson) {
            p->lTag = Thread;
            p->lson = pre;
		}
		if (!pre->rson) {
            pre->rTag = Thread;
            pre->rson = p;
		}
		pre = p;                            //pre指向p的前驱
		InThreading(p->rson);               //右子树线索化
	}
}
//此函数用于建立线索，中序遍历线索化二叉树，Thrt是表头，t是待线索化的二叉树根节点
void InOrderThreading(BT* &Thrt, BT *t)
{
    if (!(Thrt = new BT()))                 //若内存满，则报错内存溢出
        exit(OVERFLOW);
    Thrt->lTag = Link, Thrt->rTag = Link;   //建头结点,右指针回指
    Thrt->rson = Thrt;
    if (!t) {
        Thrt->lson = Thrt;                  //若二叉树空，则左指针回指
        Thrt->lTag = Thread;
    } else {
        Thrt->lson = t;
        pre = Thrt;
        InThreading(t);                     //中序遍历进行中序线索化
        pre->rson = Thrt;
        pre->rTag = Thread;                 //最后一个结点线索化
    }
}
BT* InNext(BT *p)                           //求中序后继
{
    if (p->rTag == Thread)
        return p->rson;
    BT *q = p->rson;
    while (q->lTag == Link)
        q = q->lson;
    return q;
}
BT* InPre(BT *p)                            //求中序前驱
{
    if (p->lTag == Thread)
        return p->lson;
    BT *q = p->lson;
    while (q->rTag == Link)
        q = q->rson;
    return q;
}
void InOrder(BT *head)                      //线索化后中序遍历,head为表头
{
	BT *p;
	p = head;
	do {
	   p = InNext(p);
       if (p != head)
           visit(p->data);
    } while (p != head);
}
void printTree(BT *t)                       //未利用后继结点的非递归先序遍历函数
{
    static int fb = 1;
    if (fb)
        puts("此二叉树的广义表表示为：");
    fb = 0;
	if (t) {
		visit(t->data);
		if (t->lson != NULL || t->rson != NULL) {
			printf("<");
			printTree(t->lson);
			if (t->rson != NULL)
				printf(",");
			printTree(t->rson);
			printf(">");
		}
	}
}
void QWQ(BT *t)                             //先序打印每个结点的前驱和后继
{
    if (t) {
        printf("%c: ",t->data);
        BT *pt = InPre(t), *nt = InNext(t);
        if (pt->data <='z' && pt->data >= 'a') {
            printf("%c  ",pt->data);
        } else printf("无 ");
        if (nt->data <= 'z' && nt->data >= 'a') {
            printf("%c\n",nt->data);
        } else puts("无");
        if (Link == t->lTag)
            QWQ(t->lson);
        if (Link == t->rTag)
            QWQ(t->rson);
    }
}
int main()
{
	BT *rt = new BT, *InThrt, *PreThrt, *PostThrt;
	puts("请按先序输入二叉树，空值以'#'代替：");
	rt = Setup();
	printTree(rt);
    puts("\n递归算法中序遍历结果：");
	QAQ(rt);
	puts("\n线索化后非递归中序遍历结果：");
	InOrderThreading(InThrt, rt);
	InOrder(InThrt);
    puts("\n每个结点的前驱和后继：");
    QWQ(rt);
	return 0;
}
