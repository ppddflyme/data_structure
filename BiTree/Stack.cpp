#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "Stack.h"

using std::cout;
using std::endl;

status initStack(SqStack & S)
{
    S.top = S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    CHECK_PTR(S.base);
    S.stackSize = STACK_INIT_SIZE;
    return SUCCESS;
}

status destroyStack(SqStack & S)
{
    if (S.base)
        free(S.base);
    S.stackSize = 0;
    return SUCCESS;
}

bool stackEmpty(const SqStack S)
{
    return S.base == S.top;
}

status push(SqStack & S, const SElemType & e)
{
    if (S.top - S.base >= S.stackSize) {
        S.base = (SElemType *)realloc(S.base, (S.stackSize + STACKINCREMENT) * sizeof(SElemType));
        CHECK_PTR(S.base);
        S.top = S.base + S.stackSize;
        S.stackSize += STACKINCREMENT;
    }
    *S.top++ = e;
    return SUCCESS;
}

status pop(SqStack & S, SElemType & e)
{
    if (S.base == S.top)
        return FAIL;
    e = *--S.top;
    return SUCCESS;
}

status getTop(const SqStack & S, SElemType & e)
{
    if (stackEmpty(S))
        return FAIL;
    e = *(S.top - 1);
    return SUCCESS;
}
