//
// Created by XQ.Zhu on 2023/4/30.
//
#pragma once

#include <stdio.h>
#include <iostream>


#define MAXSIZE2 100
#define MAXSIZE 10
#define ElemType int
typedef struct {
    ElemType data[MAXSIZE];// 指示动态分配数组的指针
    int top;
} SeqStack;

typedef struct {
    ElemType stack[MAXSIZE2];// 栈空间
    int top[2]; // 两个栈顶指针
} stk;
stk s;

/**
 * 入栈
 * @param stack
 * @param data
 * @return
 */
bool pushIntoStack(SeqStack &stack, ElemType data);

void initStack(SeqStack &stack);

bool isEmpty(SeqStack s);

bool isFull(SeqStack s);

bool pop(SeqStack &s, ElemType &data);

bool GetTopElem(SeqStack s, ElemType &x);

void printStack(SeqStack s);

void initShareStack(stk s);

bool pop(SeqStack &s, ElemType &data) {
    // 判空
    if (s.top == -1) {
        return false;
    }
    data = s.data[s.top--];
    return true;
}

bool pushIntoStack(SeqStack &stack, ElemType data) {
    if (stack.top == MAXSIZE - 1) {
        return false;
    }
    stack.data[++stack.top] = data;
    return true;
}

void initStack(SeqStack &stack) {
    // 初始化top为-1
    stack.top = -1;
}

//判空
bool isEmpty(SeqStack s) {
    return s.top == -1;
}


//判满
bool isFull(SeqStack s) {
    return s.top == MAXSIZE - 1;
}

//获取栈顶元素
bool GetTopElem(SeqStack s, ElemType &x) {
    //判空
    if (s.top == -1) {
        return false;
    }
    x = s.data[s.top];
    return true;
}

//栈的打印操作
void printStack(SeqStack s) {
    while (s.top != -1) {
        ElemType x;
        pop(s, x);
        printf("%d\n", x);
    }
}

bool judgeIllegal(char a[]) {
    int i = 0;
    int j, k = 0;
    while (a[i] != '\0') {
        switch (a[i]) {
            case 'I':
                j++;
                break;
            case 'O':
                k++;
                // 弹出的次数不能大于push的次数
                if (k > j) {
                    printf("序列非法\n");
                    exit(0);
                }
        }
        i++;
    }
    // 栈中需要为空
    if (j != k) {
        printf("循环执行完,序列非法\n");
        return false;
    } else {
        printf("循环执行完,序列合法\n");
        return true;
    }
}

void initShareStack() {
    s.top[0] = -1;
    s.top[1] = MAXSIZE2;
}

/**
 * 04. 判断链表是否对称
 *
 * @param linkedList 链表
 * @param n 链表长度
 * @return
 */
bool isSymmetric(LinkedList linkedList, int n) {
    int i;
    int a[n / 2];
    // 工作指针
    LNode *pNode = linkedList->next;
    // 前半部分放入栈
    for (i = 0; i < n / 2; i++) {
        a[i] = pNode->data;
        pNode = pNode->next;
    }
    // 如果n为奇数,跳过中间结点
    if (n % 2 == 1) {
        pNode = pNode->next;
    }
    // 数组下标-1
    i--;
    while (pNode != nullptr && a[i] == pNode->data) {
        pNode = pNode->next;
        i--;
    }
    // 没有比对到最后一位就退出了
    if (i != -1) {
        return false;
    }
    return true;
}

int shareStackPush(int i, ElemType x) {
    // 入栈 i=0入左边栈,i=1入右边栈
    if (i < 0 || i > 1) {
        printf("栈号输入错误\n");
        exit(0);
    }
    // 栈是否满了
    if (s.top[1] - s.top[0] == 1) {
        printf("栈已满\n");
        return 0;
    }
    // 入栈
    switch (i) {
        case 0:
            s.top[0] = s.top[0] + 1;
            s.stack[s.top[0]] = x;
            //s.stack[++s.top[0]] = x;
            return 1;
        case 1:
            s.stack[--s.top[1]] = x;
            return 1;
        default:
            break;
    }
}

/**
 * 出栈
 * @param i 栈号
 * @return
 */
ElemType shareStackPop(int i) {
    // 入栈 i=0入左边栈,i=1入右边栈
    if (i < 0 || i > 1) {
        printf("栈号输入错误\n");
        //exit(0);
    }
    // 出栈 如果栈为空,返回-1
    switch (i) {
        case 0:
            if (s.top[0] == -1) {
                printf("0号栈为空\n");
                return -1;
            }
            return s.stack[s.top[0]--];
        case 1:
            if (s.top[1] == MAXSIZE2) {
                printf("1号栈为空\n");
                return -1;
            }
            return s.stack[s.top[1]++];
        default:
            break;
    }
}

int test3() {
//    SeqStack s;
//    //初始化栈元素
//    initStack(s);
//    //往栈里面添加元素
//    pushIntoStack(s, 1);
//    pushIntoStack(s, 2);
//    pushIntoStack(s, 3);
//    pushIntoStack(s, 4);
//    pushIntoStack(s, 5);
//    printStack(s);
//    char a[] = {'I', 'O', 'I', 'O'};
//    judgeIllegal(a);
//    LinkedList linkedList;
//    initList(linkedList);
//    insertElement(linkedList, 1, 2);
//    insertElement(linkedList, 2, 1);
//    insertElement(linkedList, 3, 1);
//    insertElement(linkedList, 4, 2);
//    //insertElement(linkedList, 5, 2);
//    bool b = isSymmetric(linkedList, 4);
//    if (b) {
//        printf("element is symmetrical!");
//    } else {
//        printf("element is NOT symmetrical!");
//    }
    initShareStack();
    shareStackPush(0, 1);
    shareStackPush(0, 2);
    shareStackPush(0, 3);
    shareStackPush(0, 4);
    shareStackPush(0, 5);
    for (int i = 0; i < 3; ++i) {
        int stackPop = shareStackPop(0);
        printf("返回结果: %d\n", stackPop);
    }
    return 0;
}


