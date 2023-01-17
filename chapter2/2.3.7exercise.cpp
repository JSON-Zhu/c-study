#pragma once

#define MAXINT 0x7fffffff

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "../20221120/2.linked_list.cpp"

using namespace std;
#define InitSize 10 //默认的最大长度

/**
 * 综合应用题 01. 递归删除链表元素
 * @param list
 */
void deleteRecursively(LinkedList &list, int x);

/**
 * 综合应用题 02. 删除链表元素
 * @param list
 */
// 算法1, 引入三个指针, pre,cur,target,分别指向前驱,当前,目标结点. 遍历链表,删除目标结点
void deleteAllX(LinkedList &list, int x);

/**
 * 综合应用题 03. 反向输出链表的所有元素
 * @param list
 */
// 解法1 原地逆置链表,两个指针pre,cur,最后头结点指向pre
void printListReverse(LinkedList &list);

/**
 * 综合应用题 04. 带头结点的链表删除最小的元素
 * @param list
 */
void removeSmallest(LinkedList &list);

/**
 * 综合应用题 05. 03的第二种解法
 * @param list
 */


/**
 * 综合应用题 06. 排序链表
 * @param list
 */
void sortingList(LinkedList &list);

/**
 * 综合应用题 07 删除指定区间的值
 * @param list
 */
void removeSpecifiedInterval(LinkedList &list, int begin, int end);

/**
 * 综合应用题 08 找出两个单链表的公共结点
 * 有相同的结点表明后续结点必然全部都是相同的,因为单链表的结点只能存储一个next指针
 * @param list1
 * @param list2
 */
LNode * findCommonElement(LinkedList &list1, LinkedList &list2);

LNode * findCommonElement(LinkedList &list1, LinkedList &list2) {
    LinkedList longList, shortList;
    int length1 = getListLength(list1);
    int length2 = getListLength(list2);
    // 长链表需要先遍历的元素个数
    int dist = 0;
    if (length1 > length2) {
        longList = list1->next;
        shortList = list2->next;
        // 相减后并且长链表在遍历dist个元素,然后通知遍历长短链表,如果还有相同的元素,则必然他们在长短链表中的index是一致的.
        dist = length1 - length2;
    } else {
        longList = list2->next;
        shortList = list1->next;
        dist = length2 - length1;
    }
    // 长链表遍历dist个,是两个链表长度一致,以一起遍历
    while (dist > 0) {
        longList = longList->next;
        dist--;
    }
    // 开始同时遍历长短两个链表
    while (longList != nullptr) {
        // 找到即返回
        if (shortList == longList) {
            return longList;
        } else {
            shortList = shortList->next;
            longList = longList->next;
        }
    }
    // 没有找到相同的
    return nullptr;
}

void removeSpecifiedInterval(LinkedList &list, int begin, int end) {
    LNode *p = list->next, *pre, *next;
    pre = list;
    while (p != nullptr) {
        // 先保存下个节点 ,确保不断链
        next = p->next;
        if (p->data >= begin && p->data <= end) {
            // 临时节点,用于释放内存
            LNode *temp;
            temp = p;
            // 移动p,pre指针
            p = next;
            pre->next = p;
            free(temp);
        } else {
            pre = p;
            p = next;
        }
    }
}

/**
 * 这方法太妙了, 我很难想到 2022年12月17日23:40:43
 * 我可能真是个正常人啊 笑哭ing........
 * @param list
 */
void sortingList(LinkedList &list) {
    // p第一个节点
    LNode *p = list->next, *pre;
    LNode *r = p->next;
    // 构造只包含一个元素的有序表
    p->next = NULL;
    // p指向原链表的第二个元素
    p = r;
    while (p != nullptr) {
        // 保存p的后继指针
        r = p->next;
        // 每次都要从从头开始遍历比较
        pre = list;
        while (pre->next != nullptr && pre->next->data < p->data) {
            pre = pre->next;
        }
        // 找到位置,在pre,pre->next之间插入p,
        p->next = pre->next;
        pre->next = p;
        // 移动指针,继续扫描原链表
        p = r;
    }
}

void removeSmallest(LinkedList &list) {
    int index = 1;
    int smallerIndex = 1;
    int base = list->next->data;
    LNode *p = list->next;
    while (p != nullptr) {
        if (p->data < base) {
            base = p->data;
            smallerIndex = index;
        }
        p = p->next;
        index++;
    }
    removeElement(list, smallerIndex);
}

// 解法2 使用递归
LNode *printListReverseV2(LinkedList &list);

LNode *printListReverseV2(LinkedList &list) {
    // 递归出口
    if (list == nullptr || list->next == nullptr) {
        return list;
    }
    LNode *newHead = printListReverseV2(list->next);
    // 反转指向 ps: 想出此种想法的人简直太聪明了,我这种凡人理解都成问题.2022年12月17日18:54:37
    list->next->next = list;
    // 原指针指向置空
    list->next = nullptr;
    // 返回新的第一个元素的节点
    return newHead;
}

void printListReverse(LinkedList &list) {
    LNode *pre = nullptr, *cur = list->next;
    while (cur != nullptr) {
        // 先取出下个节点,如下顺序不要改变,否则可能无法预料结果
        LNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    list->next = pre;
}

void deleteAllXV2(LinkedList &list, int x);

// 算法2 不等于的结点插入头结点后面.
void deleteAllXV2(LinkedList &list, int x) {
    LNode *p = list->next, *r = list, *q;
    while (p != nullptr) {
        // 找到不等于x的节点,连接到l尾部,并继续扫描
        if (p->data != x) {
            r->next = p;
            r = p;
            p = p->next;
        } else {
            // 知道等于x的节点,释放空间并继续扫描.
            q = p;
            p = p->next;
            free(q);
        }
        // 最后设置后置节点尾指针null
        r->next = nullptr;
    }
}

void deleteAllX(LinkedList &list, int x) {
    if (list == nullptr || list->next == nullptr) {
        return;
    }
    // 设置p和pre的初始值
    LNode *p = list->next, *pre = list, *q;
    p = list->next;
    while (p != nullptr) {
        if (p->data == x) {
            // q指向该结点
            q = p;
            p = p->next;
            pre->next = p;
            free(q);
        } else {
            pre = p;
            p = p->next;
        }
    }

}

void deleteRecursively(LinkedList &list, int x) {
    LNode *p;
    // 递归出口
    if (list == nullptr) {
        return;
    }
    if (list->data == x) {
        p = list;
        list = list->next;
        free(p);
        deleteRecursively(list, x);
    } else {
        deleteRecursively(list->next, x);
    }
}

void test2() {
    LinkedList list;
    initList(list);
    insertElement(list, 1, 5);
    insertElement(list, 2, 2);
    insertElement(list, 3, 4);
    insertElement(list, 4, 3);
    insertElement(list, 5, 1);
    //deleteRecursively(list, 2);
    // deleteAllX(list, 4);
    // printListReverse(list);
    //LNode *pNode = printListReverseV2(list->next);
    // list->next = pNode;
    // removeSmallest(list);
    // sortingList(list);
    // removeSpecifiedInterval(list, 1, 4);

    LinkedList list1;
    initList(list1);
    LNode *pLNode2 = getElement(list, 2);
    insertNode(list1,pLNode2);
    
    LinkedList list2;
    initList(list2);
    LNode *pLNode3 = getElement(list, 2);
    insertNode(list2,pLNode3);

    LNode *pLNode = findCommonElement(list1, list2);
    traverseListNoHead(pLNode);

    //traverseList(list);
}