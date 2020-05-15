#pragma once

#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT  10  // 存储空间分配增量

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
