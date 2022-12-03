#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct LNode {
    int data;// 指示动态分配数组的指针
    struct LNode *next;
} LNode, *LinkedList;

bool initList(LinkedList &list);

LinkedList list_headInsert(LinkedList &list);

/**
 * 头插法
 * @param list
 * @return
 */
LinkedList list_headInsert(LinkedList &list) {

};

/**
 * 初始化带头结点的链表
 * @param list
 * @return
 */
bool initList(LinkedList &list) {
    list = (LNode *) malloc(sizeof(LNode));
    if (list == NULL) {
        return false;
    }
    list->next = NULL;
    return true;
}

