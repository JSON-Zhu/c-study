
// hello.h
#ifndef HELLO_H_
#define HELLO_H_

#endif  // HELLO_H_

#include <iostream>
#include <stdlib.h>
#include "../chapter2/2.2.3exercise.cpp"

using namespace std;
#define InitSize 10 //默认的最大长度

typedef struct {
    int *data;// 指示动态分配数组的指针
    int maxSize;//顺序表的最大容量
    int length;//顺序表的当前长度
} SeqList;

void initList(SeqList &list);

void increaseSize(SeqList &list, int len);

// 指定位序(起始为1)插入数据
bool addList(SeqList &list, int i, int e);

// 删除指定位置的元素,并返回被删除的元素
bool removeElementFromList(SeqList &list, int i, int &deletedValue);

int mainTest() {
    SeqList list;
    initList(list);
    bool addStatusFlag = addList(list, 1, 2);
    if (addStatusFlag) {
        printf("%s", "添加成功\n");
    } else {
        printf("%s", "添加失败.\n");
    }
    for (int i = 0; i < list.length; ++i) {
        printf("%d element is: %d", i + 1, list.data[i]);
    }
    // 删除后
    int deletedNumber = -1;
    bool deletedStatusFlag = removeElementFromList(list, 1, deletedNumber);
    if (deletedStatusFlag) {
        printf("删除成功%d\n", deletedNumber);
    } else {
        printf("%s", "添加失败.\n");
    }
    for (int i = 0; i < list.length; ++i) {
        printf("%d element is: %d", i + 1, list.data[i]);
    }
    return 0;
}

bool removeElementFromList(SeqList &list, int i, int &deletedValue) {
    if (i < 1 || i > list.length) {
        return false;
    }
    deletedValue = list.data[i - 1];
    for (int j = i; j < list.length; ++j) {
        list.data[j - 1] = list.data[j];
    }
    list.length--;
    return true;
}

bool addList(SeqList &list, int i, int e) {
    // 判断index合法性
    if (i < 1 || i > list.length + 1) {
        return false;
    }
    if (list.length >= list.maxSize) {
        return false;
    }
    // 往后移动
    for (int j = list.length; j >= i; j--) {
        list.data[j] = list.data[j - 1];
    }
    list.data[i - 1] = e;
    list.length++;
    return true;
}

// 初始化列表
void initList(SeqList &list) {
    // malloc申请一片连续的存储空间
    list.data = (int *) malloc(InitSize * sizeof(int));
    list.length = 0;
    list.maxSize = InitSize;
}

// 增加动态数组的长度
void increaseSize(SeqList &list, int len) {
    int *p = list.data;
    // malloc申请一片连续的存储空间
    list.data = (int *) malloc(InitSize * sizeof(int));
    for (int i = 0; i < list.length; ++i) {
        list.data[i] = p[i];
    }
    list.maxSize = list.maxSize + len;
    free(p);
}
