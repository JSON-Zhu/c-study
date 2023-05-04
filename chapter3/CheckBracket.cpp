//
// Created by XQ.Zhu on 2023/5/2.
//
#define MAXSIZE2 100
#define MAXSIZE 10
#define ElemType char
typedef struct {
    ElemType data[MAXSIZE];// 指示动态分配数组的指针
    int top;
} SeqStackChar;

typedef struct Queue {
    ElemType data;
    struct Queue *next;
} Queue;

typedef struct {
    Queue *front, *rear;
} LinkQueue;

void initQueue(LinkQueue &queue) {
    // 建立头结点
    queue.front = queue.rear = (Queue *) malloc(sizeof(Queue));
    // 初始化为空
    queue.front->next = nullptr;
}

bool isEmpty2(LinkQueue &queue) {
    if (queue.front == queue.rear) return true;
    return false;
}

bool enQueue(LinkQueue &queue, ElemType x) {
    Queue *pQueue = (Queue *) malloc(sizeof(Queue));
    pQueue->data = x;
    pQueue->next = nullptr;
    queue.rear->next = pQueue;
    queue.rear = pQueue;
}

bool deQueue(LinkQueue &queue, ElemType &x) {
    if (queue.front == queue.rear) return false;
    Queue *pQueue = queue.front->next;
    x = pQueue->data;
    // 更新头指针指向
    queue.front->next = pQueue->next;
    if (queue.rear == pQueue)
        queue.rear = queue.front;
    free(pQueue);
    return true;
}

void initStackChar(SeqStackChar &stack) {
    // 初始化top为-1
    stack.top = -1;
}

bool pushIntoStackChar(SeqStackChar &stack, ElemType data) {
    if (stack.top == MAXSIZE - 1) {
        return false;
    }
    stack.data[++stack.top] = data;
    return true;
}

bool popChar(SeqStackChar &s, ElemType &data) {
    // 判空
    if (s.top == -1) {
        return false;
    }
    data = s.data[s.top--];
    return true;
}

bool isEmpty(SeqStackChar stackChar) {
    return stackChar.top == -1;
}

/**
 * 检查括号是否前后配对
 * @param str
 * @return
 */
bool CheckBracket(char *str) {
    SeqStackChar stackChar;
    initStackChar(stackChar);
    int i = 0;
    while (str[i] != '\0') {
        char temp = NULL;
        switch (str[i]) {
            case '(':
            case '{':
            case '[':
                pushIntoStackChar(stackChar, str[i]);
                break;
            case ')':
                popChar(stackChar, temp);
                if (temp != '(') {
                    return false;
                }
                break;
            case '}':
                popChar(stackChar, temp);
                if (temp != '{') {
                    return false;
                }
                break;
            case ']':
                popChar(stackChar, temp);
                if (temp != '[') {
                    return false;
                }
                break;
            default:
                break;
        }
        i++;
    }
    if (isEmpty(stackChar)) {
        printf("匹配结果合法");
    } else {
        printf("匹配结果不合法");
    }
}

/**
 * 车厢调度
 * @param train
 */
void match(char *train) {
    SeqStackChar s;
    initStackChar(s);
    char *p = train, *q = train, c;
    int i = 0, j = 0;
    char x[4];
    while (*p && i < 4) {
        if (*p == 'H') {
            pushIntoStackChar(s, *p);
        } else {
            *(q++) = *p;
        }
        i++;
        p++;
    }
    while (!isEmpty(s)) {
        popChar(s, c);
        *(q++) = c;
    }
}

/**
 * 递归的非递归计算
 * @param n
 * @param x
 * @return
 */
double p(int n, double x) {
    struct stack {
        // 保存n
        int no;
        // 保存pn(x)值
        double val;
    } st[MAXSIZE2];
    int top = -1, i;
    double fv1 = 1, fv2 = 2 * x;
    for (i = n; i >= 2; i--) {
        top++;
        st[top].no = i;
    }
    while (top >= 0) {
        st[top].val = 2 * x * fv2 - 2 * (st[top].no - 1) * fv1;
        fv1 = fv2;
        fv2 = st[top].val;
        top--; // 出栈
    }
    if (n == 0)
        return fv1;
    return fv2;
}

LinkQueue q;//总车辆队列
LinkQueue q1;//客车队列
LinkQueue q2;//货车队列

void manager() {
    // j表示总的车辆数
    int i = 0, j = 0;
    while (j < 10) {
        char x;
        // 从客车队列中取出4个
        if (!isEmpty2(q1) && i < 4) {
            deQueue(q1, x);
            enQueue(q, x);
            // 总数量和客车数量+1
            i++;
            j++;
        } else if (i == 4 && !isEmpty2(q2)) {
            deQueue(q2, x);
            enQueue(q, x);
            // 总数量增加,客车数量重置
            j++;
            i = 0;
        } else {
            // 客车或火车队列为空
            while (j < 10 && i < 4 && !isEmpty2(q2)) {
                deQueue(q2, x);
                enQueue(q, x);
                i++; // 货车当客车处理
                j++;
            }
            // 货车为空 客车计数置空,继续添加
            i = 0;
        }
        if (isEmpty2(q1) && isEmpty2(q2)) {
            break;
            //j = 11;
        }
    }
}

int test33() {
    //char x[] = {'[', '{', ']', '{'};

    //if (!CheckBracket(x)) {
    //    printf("不合法的表达式\n");
//    //}
//    char train[4] = {'H', 'H', 'S', 'S'};
//    //char train[1] = {'H'};
//    //printf("%s",train);
//    match(train);
//    printf("%s", train);
//    double p1 = p(3, 2);
//    printf("输出值是:%f", p1);
    initQueue(q);
    initQueue(q1);
    initQueue(q2);
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q1, '1');
    enQueue(q2, '2');
    enQueue(q2, '2');
    enQueue(q2, '2');
    enQueue(q2, '2');
    manager();

    Queue *pQueue = q.front->next;
    while (pQueue != nullptr) {
        printf("%c", pQueue->data);
        pQueue = pQueue->next;
    }
    return 0;
}



