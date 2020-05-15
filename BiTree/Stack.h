#pragma once
#include "tree_data_structure.h"
#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT  10  // 存储空间分配增量

typedef BiTree SElemType;

typedef struct {
    SElemType * base; //在栈构造之前和销毁之后, base的值为NULL
    SElemType * top;  // 栈顶的指针
    int       stackSize; //当前已分配的存储空间, 以元素为单位
}SqStack;

status initStack(SqStack & S);
status destroyStack(SqStack & S);
bool stackEmpty(const SqStack S);
status push(SqStack & S, const SElemType & e);
status pop(SqStack & S, SElemType & e);
status getTop(const SqStack & S, SElemType & e);