#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct LNode {
    int data;// 指示动态分配数组的指针
    struct LNode *next;
} LNode, *LinkedList;

/**
 * 初始化带头结点的链表
 * @param list
 * @return
 */

bool initList(LinkedList &list);

/**
 * 头插法 常用于逆置链表
 * @param list
 * @return
 */
LinkedList list_headInsert(LinkedList &list);

/**
 * 尾插法
 * @param list
 * @return
 */
LinkedList list_tailInsert(LinkedList &list);

/**
 * 按序号查找节点
 * @param i
 * @return
 */
LNode *getElement(LinkedList list, int i);

/**
 * 插入到对应位置
 * @param i
 * @return
 */
void insertElement(LinkedList list, int index, int value);

/**
 * 删除元素
 * @param i
 * @return
 */
void removeElement(LinkedList list, int index);

/**
 * 删除指定元素
 * 原理是和后一个元素做交换,交换data和next,并释放后一个元素.
 * @return
 */
bool removeSpecificElement(LNode *p);

bool removeSpecificElement(LNode *p) {
    if (p == NULL) {
        return false;
    }
    LNode *pNode = p->next;
    p->data = pNode->data;
    p->next = pNode->next;
    free(pNode);
    return true;
}

void removeElement(LinkedList list, int index) {
    LNode *pNode = getElement(list, index - 1);
    LNode *pLNode = pNode->next;
    pNode->next = pNode->next->next;
    free(pLNode);
}


void insertElement(LinkedList list, int index, int value) {
    LNode *pNode = getElement(list, index - 1);
    if (pNode == nullptr) {
        cout << "位序号输入错误" << endl;
        return;
    }
    LNode *s = (LNode *) malloc(sizeof(LNode));
    s->data = value;
    s->next = pNode->next;
    pNode->next = s;
    /**
     * 可以交换s和p的数据域,以实现前插操作
     * int tempInt = s->data
     * s->data = p->data
     * p->data = tempInt;
     * 好一招偷天换日,移花接木啊!!!! 2022年12月3日21:41:50 出租屋学习王道数据结构第二章 线性表
     */
}

/**
 * 按值查找表结点
 * @param i
 * @return
 */
LNode *getElementByValue(LinkedList list, int value) {
    LNode *pNode = list->next;
    while (pNode && pNode->data != value) {
        pNode = pNode->next;
    }
    return pNode;
}


LNode *getElement(LinkedList list, int i) {
    // 计数,初始化为1
    int count = 1;
    LNode *p = list->next;
    if (i == 0) {
        return list;
    }
    if (i < 1) {
        return NULL;
    }
    while (p && count < i) {
        p = p->next;
        count++;
    }
    return p;
}

/**
 * 遍历链表
 * @param list
 */
void traverseList(LinkedList &list);

LinkedList list_tailInsert(LinkedList &list) {
    LNode *s;
    int intData;
    // 创建头结点
    list = (LinkedList) malloc(sizeof(LNode));
    // 初始化为空链表
    list->next = NULL;
    LNode *r = list;
    scanf("%d", &intData);
    while (intData != 9999) {
        s = (LNode *) malloc(sizeof(LNode));
        s->data = intData;
        r->next = s;
        // r指向新的表尾结点
        r = s;
        // 继续输入
        scanf("%d", &intData);
    }
    // 输入结束,表尾结点指向null
    r->next = NULL;
    return list;
}

void traverseList(LinkedList &list) {
    if (list == NULL)
        return;
    LNode *p = list->next;
    while (p != NULL) {
        cout << "data is: " << p->data << endl;
        p = p->next;
    }
}


LinkedList list_headInsert(LinkedList &list) {
    LNode *s;
    int intData;
    // 创建头结点
    list = (LinkedList) malloc(sizeof(LNode));
    // 初始化为空链表
    list->next = NULL;
    scanf("%d", &intData);
    while (intData != 9999) {
        s = (LNode *) malloc(sizeof(LNode));
        s->data = intData;
        s->next = list->next;
        list->next = s;
        // 继续输入
        scanf("%d", &intData);
    }
    return list;
}


bool initList(LinkedList &list) {
    list = (LNode *) malloc(sizeof(LNode));
    if (list == NULL) {
        return false;
    }
    list->next = NULL;
    return true;
}

