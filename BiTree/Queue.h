#pragma once
#include "tree_data_structure.h"

typedef BiTree QElemType;

typedef struct QNode {
    QElemType    data;
    struct QNode * next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr  front;
    QueuePtr  rear;
} LinkQueue;

/*
create queue
*/
status initQueue(LinkQueue & Q);

/*
    destroy queue
*/
status destroyQueue(LinkQueue & Q);

/*
    insert data
*/

status push(LinkQueue & Q, QElemType bNode);
QElemType pop(LinkQueue & Q);
bool queueEmpty(const LinkQueue & Q);

//get tail element
status getTail(const LinkQueue & Q, QElemType & e);


