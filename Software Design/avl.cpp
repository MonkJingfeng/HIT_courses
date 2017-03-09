//文件名：AVL.CPP
//数据文件：ALL.TXT，任意个结点值，整型
//功能：平衡二叉树的建立，平衡二叉树的判断
//2015年5月11日

#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include "malloc.h"

#define TRUE 1
#define FALSE 0

typedef int ElementType;
typedef struct  CellType
{
    ElementType  data;
    int  bf;
    struct CellType  *lchild,*rchild;
} AVLT;

AVLT *Setup(char *filename); //创建平衡二叉树
void LeftRotation(AVLT *&T); //左向右旋转LL,LR
void RightRotation(AVLT *&T);//右向左旋转RR,RL
void AVLInsert( AVLT *&T,ElementType R); //在平衡二叉树中插入节点，
void LayerOrder(AVLT *T);    //层序遍历
void InOrder(AVLT *T);       //中序遍历
void PreOrder(AVLT *T);      //先序编历
int  IsBST(AVLT *bt);        //判断任意二叉树是否是二叉排序树
int  Depth(AVLT *bt);        //求二叉树的深度
int  IsAVL(AVLT *T);         //判断平衡二叉树

int  unbalanced=FALSE;	     //平衡标志

int Depth(AVLT *bt)                 //求二叉树的深度
{
    int ldepth,rdepth;
    if(bt==NULL)
        return(0);
    else
    {
        ldepth=Depth(bt->lchild);
        rdepth=Depth(bt->rchild);
        if(ldepth>rdepth)
            return(ldepth+1);
        else
            return(rdepth+1);
    }
}

int IsAVL(AVLT *T)   //判断平衡二叉树
{
    int hl,hr;
    if(T==NULL)
        return(1);
    else
    {
        hl=Depth(T->lchild);
        hr=Depth(T->rchild);
        if(abs(hl-hr)<=1)
        {
            if(IsAVL(T->lchild))
                return(IsAVL(T->rchild));
        }
        else
            return(0);
    }
}

void AVLInsert( AVLT *&T,ElementType R) //在平衡二叉树中插入节点，
{
    if(T==NULL)                         //插入在空二叉树上
    {
        unbalanced=TRUE ;
        T=new CellType ;
        T->data=R ;
        T->lchild=T->rchild=NULL ;
        T->bf=0;
    }
    else if(R<T->data)                //在左子树上插入
    {
        AVLInsert(T->lchild,R) ;
        if(unbalanced)
            switch(T->bf)
            {
            case -1:
                T->bf=0 ;
                unbalanced=FALSE ;
                break ;
            case  0:
                T->bf=1 ;
                break ;
            case  1:
                LeftRotation(T) ;
            }
    }
    else if(R>=T->data)                //在右子树上插入
    {
        AVLInsert(T->rchild,R) ;
        if(unbalanced)
            switch(T->bf)
            {
            case  1:
                T->bf=0 ;
                unbalanced=FALSE ;
                break ;
            case  0:
                T->bf= -1 ;
                break ;
            case -1:
                RightRotation(T) ;
            }
    }
    else
        unbalanced=FALSE  ;
}   //AVLInsert

void  LeftRotation(AVLT *&T )           //左向右旋转LL,LR
{
    AVLT *gc,*lc ;
    lc=T->lchild ;
    if(lc->bf==1)                //LL
    {
        printf("失衡结点T=%d,做LL旋转: \n",T->data);
        T->lchild=lc->rchild ;
        lc->rchild=T ;
        T->bf=0 ;
        T=lc;
    }
    else                                //LR
    {
        printf("失衡结点T=%d,做LR旋转: \n",T->data);
        gc=lc->rchild ;
        lc->rchild=gc->lchild ;
        gc->lchild=lc ;
        T->lchild =gc->rchild ;
        gc->rchild =T ;
        switch( gc->bf)
        {
        case  1:
            T->bf=-1 ;
            lc->bf=0 ;
            break ;
        case  0:
            T->bf=lc->bf=0 ;
            break ;
        case -1:
            T->bf =0 ;
            lc->bf=1 ;
        }
        T=gc ;
    }
    T->bf=0 ;
    unbalanced=FALSE ;
}

void RightRotation(AVLT *&T)          //右向左旋转RR,RL
{
    AVLT *gc,*rc ;
    rc=T->rchild ;
    if(rc->bf==-1)
    {
        printf("失衡结点T=%d,做RR旋转: \n",T->data);
        T->rchild=rc->lchild ;
        rc->lchild=T ;
        T->bf=0;
        T=rc;
    }
    else                              //RL
    {
        printf("失衡结点T=%d,做RL旋转: \n",T->data);
        gc=rc->lchild ;
        rc->lchild=gc->rchild ;
        gc->rchild=rc ;
        T->rchild=gc->lchild ;
        gc->lchild=T;
        switch(gc->bf)
        {
        case -1:
            T->bf=-1;
            rc->bf=0 ;
            break ;
        case  0:
            T->bf=rc->bf=0 ;
            break ;
        case  1:
            T->bf =0;
            rc->bf=-1;
        }
        T=gc ;
    }
    T->bf=0 ;
    unbalanced=FALSE ;
}

void LayerOrder(AVLT *T)             //层序遍历
{
    struct node
    {
        AVLT *vec[200];
        int f,r;
    } q;

    q.f=0;
    q.r=0;
    q.vec[0]=T;
    q.r++;

    while (q.f<q.r)
    {
        T=q.vec[q.f++];
        printf("(%d,%d) ",T->data,T->bf);
        if (T->lchild)
            q.vec[q.r++]=T->lchild;
        if(T->rchild)
            q.vec[q.r++]=T->rchild;
    }
    puts("");
}

void InOrder(AVLT *T)           //中序遍历
{
    if(T!=NULL)
    {
        InOrder(T->lchild);
        printf("%d  ",T->data);
        InOrder(T->rchild);
    }
}

void PreOrder(AVLT *T)         //先序遍历
{
    if(T!=NULL)
    {
        printf("%d  ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

int IsBST(AVLT *bt)            //判断任意二叉树是否是二叉排序树
{
    AVLT *s[100],*p=bt;
    int top=0,preval=-1;
    do
    {
        while(p)
        {
            s[top++]=p;
            p=p->lchild;
        }
        if(top>0)
        {
            p=s[--top];
            if(p->data<preval)
                return 0;   //不是二叉排序树
            preval=p->data;
            p=p->rchild;
        }
    }
    while (p||top>0);
    return(1);              //是二叉排序树
}

AVLT *Setup(char *filename)   //创建平衡二叉树
{
    FILE *fp;
    AVLT *T=NULL;
    ElementType x;
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("***数据文件不存在或打不开，请检查数据文件.\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d",&x);
        unbalanced=FALSE;	//每次调用AVLInsert前，将unbanlanced 设为 FALSE
        AVLInsert(T,x);
        printf("层序：");
        LayerOrder(T);
//	  printf("\n");
    };
    return(T);
}

int main()
{
    AVLT *BT=NULL;
    BT=Setup("avl.txt");
    if(BT!=NULL) printf("\n先序序列如下:\n");
    PreOrder(BT);
    printf("\n层序序列如下:\n");
    LayerOrder(BT);
    printf("\n");
    if(IsBST(BT)) printf("\n经IsBST判断，确定是二叉排序树!\n");
    if(IsAVL(BT)) printf("经IsAVL判断，确定是平衡二叉树!\n");
}

/*
25 27 30 12 11 18 14 20 15 22
*/
