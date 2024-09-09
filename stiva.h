/* Antonescu Albert - 314CD */

#pragma once
#include "tema1.h"

typedef struct stack {
    TList data;
    struct stack *next;
}   *TStack;

TStack initStack(TList data) {
    TStack s = (TStack) malloc(sizeof(struct stack));
    s->data = data;
    s->next = NULL;
    return s;
}

int isEmptyS(TStack s) {
    return s == NULL;
}

TStack push(TStack s, TList data) {
    TStack top;
    if (isEmptyS(s))
        return initStack(data);
    top = initStack(data);
    top->next = s;
    return top;
}
TStack pop(TStack s) {
    TStack tmp;
    if (isEmptyS(s))
        return s;
    tmp = s;
    s = s->next;
    free(tmp);
    return s;
}

TList top(TStack s) {
    if (isEmptyS(s))
        exit(1);
    return s->data;
}
TStack freeStack(TStack s) {
    while (!isEmptyS(s))
        s = pop(s);
    return NULL;
}
