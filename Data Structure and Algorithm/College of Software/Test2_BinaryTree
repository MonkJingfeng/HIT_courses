#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stdlib.h>
using namespace std;
//二叉树的结点结构体
struct BinTree {
    int data;
    BinTree* lson;
    BinTree* rson;
    BinTree(){lson = rson = NULL;}
};

//找到以x为值的结点，返回以其为根的子树
BinTree* get_father(BinTree* root,int x) {
    if(root == NULL) return NULL;
    if(root->data == x) return root;
    BinTree* lson = get_father(root->lson, x);
    BinTree* rson = get_father(root->rson, x);
    if(lson != NULL) return lson;
    if(rson != NULL) return rson;
}

//先序遍历
void pre_order(BinTree* root) {
    if (root == NULL) return;
    printf("%d ",root->data);
    pre_order(root->lson);
    pre_order(root->rson);
}

//中序遍历
void in_order(BinTree* root) {
    if (root == NULL) return;
    in_order(root->lson);
    printf("%d ",root->data);
    in_order(root->rson);
}

//后序遍历
void post_order(BinTree* root) {
    if (root == NULL) return;
    post_order(root->lson);
    post_order(root->rson);
    printf("%d ",root->data);
}

//层序遍历
void level_order(BinTree* root) {
    if (root == NULL) return;
    queue<BinTree*> q;
    q.push(root);
    while (!q.empty()) {
        BinTree* tmp = q.front();
        q.pop();
        printf("%d ",tmp->data);
        if (tmp->lson != NULL) q.push(tmp->lson);
        if (tmp->rson != NULL) q.push(tmp->rson);
    }
}

int main() {
    //freopen("in.txt","r",stdin);
    int n,x,y;
    char c;
    puts("请输入层次数：");
    scanf("%d",&n);
    puts("请输入根节点：");
    scanf("%d",&x);
    BinTree* root = new BinTree();
    root->data = x;
    root->lson = NULL;
    root->rson = NULL;
    for (int i=1;i<n;i++) {
        printf("请输入第%d层：（均以空格隔开，回车表示结束）\n",i+1);
        while (1) {
            scanf("%d%d %c",&x,&y,&c);
            BinTree* father = get_father(root, y);
            if (father == NULL)
            {
                puts("输入错误！");
                exit(-1);
            }
            if (c == 'L') {
                father->lson = new BinTree();
                father->lson->data = x;
                father->lson->rson = NULL;
                father->lson->lson = NULL;
            } else {
                father->rson = new BinTree();
                father->rson->data = x;
                father->rson->rson = NULL;
                father->rson->lson = NULL;
            }
            if (getchar() == '\n') break;
        }
    }
    puts("==========================================");
    puts("先序遍历是： ");
    pre_order(root);
    putchar('\n');
    puts("中序遍历是： ");
    in_order(root);
    putchar('\n');
    puts("后序遍历是： ");
    post_order(root);
    putchar('\n');
    puts("层序遍历是： ");
    level_order(root);
    putchar('\n');
    return 0;
}
