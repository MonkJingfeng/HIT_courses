#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define STOP system("pause")
//#define ADD(p,q,aa) q->num = aa->num;q->x = aa->x;aa = aa->next;p->next = q;p = q
using namespace std;

struct node {
    int x;          //底数
    int num;        //指数
    node* next;
};

typedef node* List;
typedef node* pos;

/**
* @brief    Create a list contain n nodes.
* @param    n    Size of the %list
* @return   Created %list
*
* This is always the first operation
* in that case.
*/
List creatList(int n) {
    List head,p,q;
    int x,num;
    head = (struct node*)malloc(sizeof(struct node));
    p = head;

    while (n--) {
        scanf("%d%d",&x,&num);
        q = (struct node*)malloc(sizeof(struct node));
        q->x = x;
        q->num = num;
        p->next = q;
        p = q;
    }
    p->next = NULL;
    return head;
}

/**
* @brief    Print a %list one by one
* @param    L    A %list
*/
void printList(List L) {
    List p;
    bool flag = false;

    p = L->next;

    if(p == NULL)
        printf("0 0");

    while(p != NULL) {
        if(flag)
            printf(" ");
        else
            flag = true;
        printf("%d %d",p->x,p->num);
        p = p->next;
    }
    printf("\n");
}

/**
* @brief    Add a number to a %list
* @param    p    A %list
* @param    q    A %list contains a node NULL
* @param    aa   A %list contains the add number
* @return   A %list equals @p + @aa's first number
*/
List Add(pos p, pos q, List aa) {
    q->num = aa->num;
    q->x = aa->x;
    p->next = q;
    p = q;
    return p;
}

/**
* @brief    Add %list to the other %list
* @param    a    A %list
* @param    b    A %list of the same type as @a
* @return   A %list equals @a + @b
*/
List add_List(List a, List b) {
    pos aa, bb;
    List c,p,q;
    int tmp;

    aa = a->next;
    bb = b->next;

    c = (struct node*)malloc(sizeof(struct node));
    p = c;

    //a和b都不为空，优先比较a和b的指数
    while ((aa != NULL) && (bb != NULL)) {
        q = (struct node*)malloc(sizeof(struct node));
        if (aa->num < bb->num) {
            //ADD(p, q, bb);
            p = Add(p, q, bb);
            bb = bb->next;
        } else if (aa->num > bb->num) {
            //ADD(p, q, aa);
            p = Add(p, q, aa);
            aa = aa->next;
        } else {
            tmp = aa->x + bb->x;
            if (tmp != 0) {
                q->num = aa->num;
                q->x = tmp;
                p->next = q;
                p = p->next;
            }
            bb = bb->next;
            aa = aa->next;
        }
    }

    //a为空，添加b
    if (aa == NULL) {
        while (bb != NULL) {
            q = (struct node*)malloc(sizeof(struct node));
            //ADD(p, q, bb);
            p = Add(p, q, bb);
            bb = bb->next;
        }
    }

    //b为空，添加a
    if(bb == NULL) {
        while(aa != NULL) {
            q = (struct node*)malloc(sizeof(struct node));
            //ADD(p, q, aa);
            p = Add(p, q, aa);
            aa = aa->next;
        }
    }

    p->next = NULL;
    return c;
}

/**
* @brief    Multiply %list to the other %list
* @param    a    A %list
* @param    b    A %list of the same type as @a
* @return   A %list equals @a * @b
*/
List mul_List(List a, List b) {
    pos aa, bb;
    List c,tmp,p,q;

    aa = a->next;
    bb = b->next;
    c = creatList(0);

    if (aa == NULL || bb == NULL) {
        return c;
    }

    while (aa != NULL) {
        tmp = (struct node*)malloc(sizeof(struct node));
        p = tmp;
        bb = b->next;

        while (bb != NULL) {
            q = (struct node*)malloc(sizeof(struct node));
            q->num = aa->num + bb->num;
            q->x = aa->x * bb->x;
            bb = bb->next;
            p->next = q;
            p = q;
        }

        p->next = NULL;
        c = add_List(c, tmp);

        aa = aa->next;
    }

    return c;
}


int main() {
    int n1,n2;
    List L1,L2,L3,L4;

    puts("请输入多项式1的项数及各项值、指数：");
    scanf("%d",&n1);
    L1 = creatList(n1);
    puts("请输入多项式2的项数及各项值、指数：");
    scanf("%d",&n2);
    L2 = creatList(n2);

    L3 = add_List(L1, L2);
    L4 = mul_List(L1, L2);
    puts("L1 * L2 :");
    printList(L4);
    puts("L1 + L2 :");
    printList(L3);

    return 0;
}
