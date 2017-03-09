#include <iostream>
#include <stdio.h>
#include <stack>
#include <stdlib.h>
#define STOP system("pause")
#define BUG puts("===")
using namespace std;
const int inf = 0x3f3f3f3f * 2;

struct node
{
    int x;
    node* next;
};

typedef node* List;
typedef node* pos;

int len;        //链表长度


/**
* @brief    Print a %list one by one
* @param    L    A %list
*/
void printList(List L)
{
    List p;
    bool flag = false;

    p = L->next;

    if(p == NULL)
        printf("NULL");

    while(p != NULL)
    {
        if(flag)
            printf(" ");
        else
            flag = true;
        printf("%d",p->x);
        p = p->next;
    }
    printf(" 共 %d个元素\n",len);
}

/**
* @brief    Insert a number into a %list
* @param    head    A %list
* @param    x       An integer
* @param    flag    True if the %list is reversed
* @return   A %list
*/
List insert(pos head, int x, bool flag)
{
    pos p = head;
    pos q = (struct node*)malloc(sizeof(struct node));
    q->x = x, q->next = NULL;

    //插入表头
    if ((p->x >= x && !flag) || (p->x <= x && flag))
    {
        List tmp = p;
        p = q;
        q = tmp;
        p->next = q;
    }
    //插入表中
    else
    {
        while (p->next != NULL)
        {
            if ((p->x <= x && p->next->x >= x && !flag) || (p->x >= x && p->next->x <= x && flag))
                break;
            p = p->next;
        }

        //插入表尾
        if (p->next == NULL && ((p->x <= x && !flag) || (p->x >= x && flag)))
            p->next = q;
        else
        {
            q->next = p->next;
            p->next = q;
        }
    }

    return head;
}

/**
* @brief    Create a list
* @return   Created %list
*
* Read the file name from the keyboard and open it.
* If it doesn't exist, return NULL.
*/
List creatList()
{
    char s[233];        //文件名称
    FILE *fp;           //文件指针
    List head,p,q;
    int n,x;            //链表长度，当前元素

    //初始化表头
    head = (struct node*)malloc(sizeof(struct node));
    head->x = 0;
    head->next = NULL;

    puts("建立链表。请输入文件名称：");
    scanf("%s",s);
    if ((fp=fopen(s,"r")) == NULL)
    {
        puts("打开文件失败。请输入正确的文件名称。");
        return NULL;
    }

    fscanf(fp,"%d",&n);
    len = n;
    while (n--)
    {
        fscanf(fp,"%d",&x);
        p = head;

//#define DEBUG
#ifdef DEBUG
        printList(p);
        printf("%d: %d\n",x, p->x);
#endif

        insert(p, x, false);
    }

    fclose(fp);
    return head;
}

int main()
{
    List L1, p;
    char op[2];
    int x, cnt;
    bool flag = false;      //是否逆序
    bool find;              //是否找到

    L1 = creatList();
    while (L1 == NULL)
    {
        L1 = creatList();
    }
    puts("链表成功建立如下：");
    printList(L1);

    while (1)
    {
        puts("请输入操作：F 查找指定元素, I 插入指定元素, D 删除指定元素, O 输出线性链表, R 逆序重建。");
        scanf("%s",op);
        p = L1;
        stack<int> stk;

        switch(op[0])
        {
        case 'F':
            puts("请输入要查找的元素：");
            scanf("%d",&x);
            find = false;
            cnt = 0;

            while (p->next != NULL)
            {
                if (x == p->x)
                {
                    printf("元素 %d位于第 %d位。\n",x,cnt);
                    find = true;
                    break;
                }
                p = p->next;
                cnt++;
            }
            if (!find && p->x == x) printf("元素 %d位于第 %d位。\n",x,len);
            if (p->next == NULL && p->x != x) puts("查无此数！");

            break;
        case 'I':
            puts("请输入要插入的元素：");
            scanf("%d",&x);

            p = insert(p, x, flag);
            len++;

            break;
        case 'D':
            puts("请输入要删除的元素：");
            scanf("%d",&x);

            //位于表头
            while (p->next->x == x)
            {
                L1 = L1->next;
                L1->x = -inf;
                p = p->next;
                len--;
            }

            //位于表中
            while (p->next)
            {
                if (p->next->x == x)
                {
                    if (p->next->next) p->next = p->next->next;
                    else p->next = NULL;
                    len--;
                }
                if (p->next)
                {
                    p = p->next;
                }
            }

            break;
        case 'O':
            printList(L1);

            break;
        case 'R':
            flag = !flag;

            while (p->next)
            {
                stk.push(p->next->x);
                p = p->next;
            }

            L1->next = NULL;
            L1->x = flag ? inf : -inf;
            p = L1;

            while (!stk.empty())
            {
                x = stk.top();
                p = insert(p, x, flag);
                stk.pop();
            }

            break;
        default:
            puts("请输入正确的命令！");

            break;
        }
    }
    return 0;
}
