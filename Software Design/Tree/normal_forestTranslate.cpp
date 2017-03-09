#include <bits/stdc++.h>
using namespace std;

//二叉树的结点结构
struct BTnode {
    int data;
    BTnode *lchild, *rchild;//左儿子右儿子
    BTnode() {}
    BTnode(int data):data(data) {lchild = rchild = NULL;}
} ;
typedef BTnode* BT;

void create_tree(BT& now) {
    int data;
    scanf("%d", &data);
    if (!data) {
        now = NULL;
    } else {
        now = new BTnode(data);
        create_tree(now->lchild);
        create_tree(now->rchild);
    }
}

//普通树的结点结构
struct node {
    int data;
    vector<node*> tree;//儿子们
    node() {}
    node(int data):data(data) {tree.clear();}
};
typedef node* Tree;

void pre_order_binary_tree(BT& now) {
    if (now) {
        printf("%d ", now->data);
        pre_order_binary_tree(now->lchild);
        pre_order_binary_tree(now->rchild);
    }
}
//二叉树转换为普通树
void transform_into_normal_tree(BT& rt, Tree& normal_tree) {
    if (!rt->lchild)//没有左儿子则返回
        return;
    Tree ptr_normal_tree = normal_tree;
    BT ptr_binary_tree = rt->lchild;
    ptr_normal_tree->tree.push_back(new node(rt->lchild->data));
    transform_into_normal_tree(rt->lchild, normal_tree->tree[0]);
    while (ptr_binary_tree->rchild) {//转化左儿子的所有的右儿子为当前结点的儿子
        ptr_binary_tree = ptr_binary_tree->rchild;
        ptr_normal_tree->tree.push_back(new node(ptr_binary_tree->data));
        transform_into_normal_tree(ptr_binary_tree, ptr_normal_tree);//递归转化以当前结点左儿子的右儿子为顶点的子树
    }
}
//二叉树转换为森林
void transform_into_forest(BT& rt, vector<Tree>& forest) {
    if (!rt)
        return;
    transform_into_forest(rt->rchild, forest);//递归转化以右儿子为顶点的子树
    Tree normal_tree = new node(rt->data);
    transform_into_normal_tree(rt, normal_tree);
    forest.push_back(normal_tree);
}
//先序遍历普通树
void pre_order_normal_tree(Tree& normal_tree) {
    if (normal_tree) {
        printf("%d ", normal_tree->data);
        for (int i=0; i<normal_tree->tree.size(); i++) {
            pre_order_normal_tree(normal_tree->tree[i]);
        }
    }
}

//森林转换成二叉树                                           目前的序号                   儿子的数量
void transform_into_b_tree(BT& b_tree, Tree normal_tree, int number_now, int number_all, int son_number, vector<Tree> forest) {
    if (!normal_tree)//如果空节点则返回
        return;
    BT& ptr_b_tree = b_tree;
    int jud = 0;
    if (son_number == 0) {//如果当前节点不是遍历到第二或更多个子节点则为当前节点
        ptr_b_tree = new BTnode(normal_tree->data);
    } else {//否则为其儿子节点
        ptr_b_tree = new BTnode(normal_tree->tree[son_number]->data);
    }
    if (ptr_b_tree->data == forest[number_now]->data && number_now < number_all) { //如果当前节点代表一棵树顶端
        transform_into_b_tree(ptr_b_tree->rchild, forest[number_now+1], number_now + 1, number_all, son_number, forest);
        jud = 1;//二叉树为其下一棵树的根
    }
    if (son_number == 0 && normal_tree->tree.size()) {//如果当前不是二或更多节点且有儿子
        transform_into_b_tree(ptr_b_tree->lchild, normal_tree->tree[son_number], number_now, number_all, 0, forest);//其左儿子为普通树第一节点
    } else if(normal_tree->tree.size() > son_number && normal_tree->tree[son_number]->tree.size()) {//如果没遍历到最后一个儿子
        transform_into_b_tree(ptr_b_tree->lchild, normal_tree->tree[son_number], number_now, number_all, 0, forest);//则遍历下一儿子
    }
    if (normal_tree->tree.size() > 1 && son_number < normal_tree->tree.size() - 1 &&  ptr_b_tree->data != forest[number_now]->data ) { //如果当前节点右节点不是树
        transform_into_b_tree(ptr_b_tree->rchild, normal_tree, number_now, number_all, son_number + 1, forest);     //右儿子为其普通树下一节点
    }
    if (normal_tree->tree.size() > 1 && son_number < normal_tree->tree.size() - 1 &&  ptr_b_tree->data == forest[number_now]->data ) {
        transform_into_b_tree(ptr_b_tree->lchild->rchild, normal_tree, number_now, number_all, son_number + 1, forest);     //否则其左儿子的右儿子更新
    }
}


int main() {
    BT rt; rt = NULL;

    puts("建立二叉树开始。");
    puts("请前序输入您想插入的节点编号。0表示空。");
    create_tree(rt);

    puts("二叉树前序遍历：");
    pre_order_binary_tree(rt);
    puts("");

    puts("二叉树转化为森林。");
    Tree top = new node(-1);
    vector<Tree> forest;
    forest.clear();
    transform_into_forest(rt, forest);
    printf("树的总数：%d\n", forest.size());
    for (int i=0; i<forest.size(); i++) {
        printf("第%d棵树的前序遍历序列：", i + 1);
        pre_order_normal_tree(forest[i]);
        puts("");
    }

    puts("森林转化为二叉树。");
    BT b_tree = NULL;
    transform_into_b_tree(b_tree, forest[0], 0, forest.size() - 1, 0, forest);
    puts("最终二叉树前序遍历序列：");
    if (b_tree == NULL)
        puts("KKK");
    pre_order_binary_tree(b_tree);
    puts("");
    return 0;
}

//1 2 0 3 4 0 0 5 0 0 6 7 9 0 0 10 0 0 8 0 0
//1 2 0 3 0 4 0 0 5 6 0 0 7 8 10 0 0 9 0 0 0
