#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "Queue.h"
using std::cout;
using std::endl;

status initQueue(LinkQueue & Q) {
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    
    if (!Q.front) {
        cout << "allocate memory error!!!" << endl;
        return -1;
    }
    Q.front->next = NULL;
    return 0;
}

status destroyQueue(LinkQueue & Q)
{
    while (Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return 0;
}

status enQueue(LinkQueue & Q, QElemType e)
{
    QNode * tmpNode = (QNode *)malloc(sizeof(QNode));

    if (!tmpNode) {
        cout << "allocate memory failed!!!" << endl;
        return -1;
    }
    tmpNode->data = e;
    tmpNode->next = NULL;
    Q.rear->next = tmpNode;
    Q.rear = tmpNode;
    return 0;
}

status deQueue(LinkQueue & Q, QElemType * e)
{
    if (Q.front == Q.rear)
        return 0;
    * e = Q.front->data;
    QNode * tmpData = Q.front->next;
    Q.front->next = tmpData->next;
    if (Q.rear == tmpData)
        Q.rear = Q.front;
    free(tmpData);
    return 0;
}

bool queueEmpty(const LinkQueue & Q)
{
    if (Q.front == Q.rear)
        return true;
    return false;
}
