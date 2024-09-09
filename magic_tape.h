/* Antonescu Albert - 314CD */
#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef char T;
typedef struct node {
    T value;
    struct node* prev;
    struct node* next;
} Node, *TList;

typedef struct banda {
    TList santinela;
    TList deget;
} Banda;

TList createList(T value) {
    TList result = (TList) malloc(sizeof(Node));
    result->value = value;
    result->prev = NULL;
    result->next = NULL;
    return result;
}

void insertFront(TList head, T value) {
    TList new = createList(value);
    new->prev = head;
    new->next = head->next;
    if (head->next != NULL)
        head->next->prev = new;
    head->next = new;
}

TList deleteList(TList head) {
    TList tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

void show(Banda banda, FILE* fisier) {
    TList iter = banda.santinela->next;
    while (iter != NULL) {
        if (iter != banda.deget)
            fprintf(fisier, "%c", iter->value);
        else
            fprintf(fisier, "|%c|", iter->value);
        iter = iter->next;
    }
    fprintf(fisier, "\n");
}

void show_current(Banda banda, FILE* fisier) {
    fprintf(fisier, "%c\n", banda.deget->value);
}

int move_left(Banda *banda) {
    if (banda->deget->prev != banda->santinela) {
        banda->deget = banda->deget->prev;
        return 1;
    }
    return 0;
}

void move_right(Banda *banda) {
    if (banda->deget->next == NULL)
        insertFront(banda->deget, '#');
    banda->deget = banda->deget->next;
}

void write(Banda *banda, T value) {
    banda->deget->value = value;
}

void move_left_char(Banda *banda, T value, FILE* fisier) {
    TList iter = banda->deget;
    while (iter->value != value) {
        if (iter == banda->santinela) {
            fprintf(fisier, "ERROR\n");
            return;
        }
        iter = iter->prev;
    }

    banda->deget = iter;
}

void move_right_char(Banda *banda, T value) {
    TList iter = banda->deget;
    while (iter->value != value) {
        if (iter->next == NULL) {
            insertFront(iter, '#');
            banda->deget = iter->next;
            return;
        }
        iter = iter->next;
    }
    banda->deget = iter;
}

void insert_left(Banda *banda, T value, FILE* fisier) {
    if (banda->deget->prev == banda->santinela) {
        fprintf(fisier, "ERROR\n");
        return;
    }
    TList new = createList(value);
    new->prev = banda->deget->prev;
    new->next = banda->deget;
    banda->deget->prev->next = new;
    banda->deget->prev = new;
    banda->deget = new;
}

void insert_right(Banda *banda, T value) {
    insertFront(banda->deget, value);
    banda->deget = banda->deget->next;
}
