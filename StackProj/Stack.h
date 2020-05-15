#pragma once

#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT  10  // �洢�ռ��������

typedef char SElemType;
typedef int status;

#define SUCCESS 0
#define FAIL    -1;

#define CHECK_PTR(ptr) \
    if (ptr == NULL) { \
        cout << "Allocate memory failed!!!" <<__FILE__ << ":" << __LINE__ << endl; \
        return FAIL; \
    }

#define ARRAY_SIZE(array) \
    (sizeof(array)/sizeof((array)[0]))

char OP[] = { '+', '-', '*', '/', '(', ')', '#'};

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
/*
    check whether c is a operator
*/
bool In(char c);

/*
    check topVal and c's priority
*/
char precede(char topVal, char c);

/*
    return operandA op operandB
*/
char operate(char operandA, char op, char operandB);
