#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "Queue.h"

using std::cout;
using std::endl;

status initQueue(LinkQueue & Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    CHECK_PTR(Q.front);
    Q.front->next = NULL;

    return SUCCESS;
}

status destroyQueue(LinkQueue & Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return SUCCESS;
}

status push(LinkQueue & Q, QElemType bNode)
{
    QueuePtr tempQNode = (QueuePtr)malloc(sizeof(QNode));
    CHECK_PTR(tempQNode);
    tempQNode->data = bNode;
    tempQNode->next = NULL;
    Q.rear->next = tempQNode;
    Q.rear = tempQNode;
    return SUCCESS;
}

QElemType pop(LinkQueue & Q)
{
    if (queueEmpty(Q)) {
        cout << "The queue is empty..." << endl;
        return SUCCESS;
    }
    
    QueuePtr tempQNode = Q.front->next;
    Q.front->next = tempQNode->next;
    if (Q.rear == tempQNode) {
        Q.rear = Q.front;
    }
    QElemType tempData = tempQNode->data;
    free(tempQNode);

    return tempData;
}

bool queueEmpty(const LinkQueue & Q) {
    return Q.front == Q.rear;
}

status getTail(const LinkQueue & Q, QElemType & e) {
    if (!queueEmpty(Q)) {
        e = Q.rear->data;
    }
    return SUCCESS;
}
