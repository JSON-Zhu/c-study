#include <iostream>
#include <stdlib.h>

#define InitSize 10 //默认的最大长度

typedef struct {
    int *data;// 指示动态分配数组的指针
    int maxSize;//顺序表的最大容量
    int length;//顺序表的当前长度
} SeqList;

void initList(SeqList &list);

void increaseSize(SeqList &list, int len);

int mainTest() {
    SeqList list;
    initList(list);
    list.data[0] = 1;
    list.data[5] = 5;

    int b = list.data[5];
    std::cout << "sixth number is: " << b << std::endl;
    if (list.length >= 2) {
        increaseSize(list, InitSize);
    }

    return 0;
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
