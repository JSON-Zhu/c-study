#pragma once

#include <iostream>
#include <stdlib.h>
#include "../20221120/1.dynamic_array_list.cpp"

using namespace std;
#define InitSize 10 //默认的最大长度


/**
 * 综合应用题 01. 删除最小元素,并返回,并用最后一个元素填充
 * @param list
 */
bool removeSmallestElement(SeqList &list, int &value);

void traverseList(SeqList &list);

/**
 * 综合应用题 02. 逆置顺序表
 * @param list
 */
bool reverseList(SeqList &list);

/**
 * 综合应用题 03. 删除数组中值为x的元素
 * @param list
 */
bool deleteSpecificValueFromList(SeqList &list, int value);

/**
 * 综合应用题 04. 从有序表中删除区间元素
 * 有序表必然删除的是相连的整体.
 * @param list
 */
bool deleteIntervalValueFromList(SeqList &list, int small, int big);

/**
 * 综合应用题 06. 从有序表中删除元素重复的值
 * 有序表必然删除的是相连的整体.
 * @param list
 */
bool deleteDuplicateValueFromList(SeqList &list);

/**
 * 综合应用题 07. 合并两个有序顺序表,并返回结果顺序表
 *
 * @param list
 */
bool mergeTwoOrderedList(SeqList &a, SeqList &b, SeqList &resultList);

/**
 * 综合应用题 08. 一维数组中的两个顺序表互换顺序
 *
 * @param list
 */
bool changeOrderOfArray(int arr[], int left, int right);


bool reverseByLeftAndRight(int arr[], int left, int right);

/**
 * 综合应用题 09. 折半查找和插入
 * @param arr
 * @param x
 * @return
 */
bool binarySearch(int arr[], int len, int x);

/**
 * 综合应用题 10. 向左移动p个位置
 * 相当于 0-p p-n,进行逆置
 * @param arr
 * @param x
 * @return
 */
bool move_p_index(int arr[], int p, int len);

/**
 * 综合应用题 11. 求两个升序序列的中位数
 *
 * 使用合并两个数组的方法,时间复杂度和空间复杂度n,
 * b站有个(https://www.bilibili.com/video/BV1mh411Y75c/?p=10&vd_source=97dc0105e885114c73dbddc197b448c2),
 * 说是使用归并,暂时没看懂,后续学完在回头看 todo
 * @param arr
 * @param x
 * @return
 */
bool calcMiddleNumber(int arr[], int arr1[]);

bool calcMiddleNumber(int arr[], int arr1[]) {
    // 暂时使用合并有序数组的方式
}

bool move_p_index(int arr[], int p, int len) {
    int arr1[len];
    for (int i = 0; i < len; ++i) {
        if (i + p > len - 1)
            arr1[i + p - len] = arr[i];
        if (i + p <= len - 1)
            arr1[i + p] = arr[i];
    }
    for (int i = 0; i < len; ++i) {
        cout << arr1[i] << endl;
    }
}

bool binarySearch(int arr[], int len, int x) {
    int low = 0;
    int high = len - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == x) {
            break;
        }
        if (arr[mid] < x)
            low = mid + 1;
        if (arr[mid] > x)
            high = mid - 1;
    }
    // 找到x,并且不是最后一个元素,此种条件下交换
    if (arr[mid] == x && mid != high) {
        int temp = arr[mid];
        arr[mid] = arr[mid + 1];
        arr[mid + 1] = temp;
    }
    int index = len - 1;
    // 未找到, 插入 并仍使其有序
    if (low > high) {
        int i;
        // 这个一直没想明白,又涨知识了加油. 2022年12月4日21:51:40.-^^-
        for (i = index; i > high; i--) {
            arr[i + 1] = arr[i];
        }
        arr[i + 1] = x;
    }
}

bool changeOrderOfArray(int arr[], int left, int right) {
    reverseByLeftAndRight(arr, 0, left + right);
    reverseByLeftAndRight(arr, 0, right);
    reverseByLeftAndRight(arr, right, right + left);
}

bool reverseByLeftAndRight(int arr[], int left, int right) {
    if (left > right) {
        return false;
    }
    for (int i = left; i < (left + right) / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[left + right - 1 - i];
        arr[left + right - 1 - i] = temp;
    }
}

bool mergeTwoOrderedList(SeqList &a, SeqList &b, SeqList &resultList) {
    // 有一个表为空,直接返回
    if (a.length == 0 || b.length == 0) {
        return false;
    }
    int i = 0, j = 0, k = 0;
    // 两个表一起遍历,任意一个表遍历完成即结束.
    while (i < a.length && j < b.length) {
        // a的值小,加入结果表,并且下标都+1,反之亦然
        if (a.data[i] <= b.data[j]) {
            resultList.data[k++] = a.data[i++];
        }
        if (a.data[i] > b.data[j]) {
            resultList.data[k++] = b.data[j++];
        }
    }
    // 是否有表还有元素,如果有继续加入到结果表中
    while (i < a.length) {
        resultList.data[k++] = a.data[i++];
    }
    while (j < b.length) {
        resultList.data[k++] = b.data[j++];
    }
    resultList.length = k;
}

bool deleteDuplicateValueFromList(SeqList &list) {
    int i = 0, j = 1;
    for (; j < list.length; j++) {
        // 默认第一个元素为不重复的值
        if (list.data[i] != list.data[j]) {
            list.data[++i] = list.data[j];
        }
    }
    list.length = i + 1;
}

bool deleteIntervalValueFromList(SeqList &list, int small, int big) {
    if (small >= big || list.length == 0) {
        cout << "list is empty or illegal input!" << endl;
    }
    int valueIndexCount = 0;
    for (int i = 0; i < list.length; ++i) {
        if (!(small < list.data[i] && list.data[i] < big)) {
            // 统计个数,并把不同的value移动
            list.data[valueIndexCount] = list.data[i];
            valueIndexCount++;
        }
    }
    list.length = valueIndexCount;
}

bool deleteSpecificValueFromList(SeqList &list, int value) {
    int valueIndexCount = 0;
    for (int i = 0; i < list.length; ++i) {
        if (value != list.data[i]) {
            // 统计个数,并把不同的value移动
            list.data[valueIndexCount] = list.data[i];
            valueIndexCount++;
        }
    }
    list.length = valueIndexCount;
    return true;
}

int listTest() {
    SeqList list;
    initList(list);
    addList(list, 1, 11);
    addList(list, 2, 13);
    addList(list, 3, 15);
    addList(list, 4, 17);
    addList(list, 5, 19);
    SeqList list2;
    SeqList resultList;
    initList(list2);
    initList(resultList);
    addList(list2, 1, 2);
    addList(list2, 2, 4);
    addList(list2, 3, 6);
    addList(list2, 4, 8);
    addList(list2, 5, 20);
    // 删除最小值
//    int smallestValue;
//    removeSmallestElement(list, smallestValue);
//    cout << "deletedValue is:" << smallestValue << endl;
    // 逆置顺序表
    // reverseList(list);
    // 删除值为x元素
    // deleteSpecificValueFromList(list, 2);
    // 删除区间元素
    // deleteIntervalValueFromList(list, 3, 3);
    // 删除所有重复元素
    // deleteDuplicateValueFromList(list);
    // 合并两个有序顺序表
    mergeTwoOrderedList(list, list2, resultList);

    traverseList(resultList);
    // int arr[10] = {1, 2, 3, 12, 14, 15, 16, 17};
    // int arr[] = {1, 2, 3, 12, 14, 15, 16, 17};
    // changeOrderOfArray(arr, 3, 5);
    // 二分查找并插入相关数据
    // binarySearch(arr, 8, 18);
    // 平移位置
    // move_p_index(arr,6,8);

    // 使用逆置实现平移
//    changeOrderOfArray(arr,2,6);
//    for (int i = 0; i < 8; ++i) {
//        cout<<arr[i]<<endl;
//    }
    return 0;
}

bool reverseList(SeqList &list) {
    // 空表,直接返回
    if (list.length == 0) {
        return false;
    }
    int circleTimes = list.length / 2;
    for (int i = 0; i < circleTimes; ++i) {
        int temp = list.data[i];
        list.data[i] = list.data[list.length - 1 - i];
        list.data[list.length - 1 - i] = temp;
    }
    traverseList(list);
}

void traverseList(SeqList &list) {
    for (int i = 0; i < list.length; ++i) {
        cout << "data is:" << list.data[i] << endl;
    }
}

bool removeSmallestElement(SeqList &list, int &value) {
    // 空表,直接返回
    if (list.length == 0) {
        return false;
    }
    // 假设第一个最小
    value = list.data[0];
    int pos = 0;
    for (int i = 1; i < list.length; ++i) {
        if (value > list.data[i]) {
            // 找出最小值,并记录下标
            value = list.data[i];
            pos = i;
        }
    }
    list.data[pos] = list.data[list.length - 1];
    list.length--;
    return true;
}
