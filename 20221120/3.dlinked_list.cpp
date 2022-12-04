#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 * 双向链表结点定义
 */
typedef struct DNode {
    int data;// 指示动态分配数组的指针
    struct DNode *prior;
    struct DNode *next;
} DNode, *DLinkedList;
