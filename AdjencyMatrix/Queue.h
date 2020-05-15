#pragma once

typedef int QElemType;
typedef int status;

typedef struct QNode {
    QElemType data;
    struct QNode * next;
}QNode, * QueuePtr;

typedef struct {
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
} LinkQueue;

//construct a empty queue Q
status initQueue(LinkQueue & Q);

//destroy queue Q
status destroyQueue(LinkQueue & Q);

//insert element e to queue Q from tail
status enQueue(LinkQueue & Q, QElemType e);

//delete front element and store the deleted element into e
status deQueue(LinkQueue & Q, QElemType * e);

//check whether the queue is empty
bool queueEmpty(const LinkQueue & Q);

//get tail element
status getTail(const LinkQueue & Q, QElemType & e);

