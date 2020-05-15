#pragma once
#include "tree_data_structure.h"
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT  10  // �洢�ռ��������

typedef BiTree SElemType;

typedef struct {
    SElemType * base; //��ջ����֮ǰ������֮��, base��ֵΪNULL
    SElemType * top;  // ջ����ָ��
    int       stackSize; //��ǰ�ѷ���Ĵ洢�ռ�, ��Ԫ��Ϊ��λ
}SqStack;

status initStack(SqStack & S);
status destroyStack(SqStack & S);
bool stackEmpty(const SqStack S);
status push(SqStack & S, const SElemType & e);
status pop(SqStack & S, SElemType & e);
status getTop(const SqStack & S, SElemType & e);