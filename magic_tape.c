/* Antonescu Albert - 314CD */

#include "tema1.h"
#include "coada.h"
#include "stiva.h"

int main() {
    TList santinela = createList(0);
    insertFront(santinela, '#');

    // se creeaza banda
    Banda banda;
    // se initializeaza santinela si degetul catre primul element
    banda.santinela = santinela;
    banda.deget = santinela->next;

    // coada pt execute
    TQueue execute = NULL;

    // stivele pt undo si redo
    TStack undo = NULL;
    TStack redo = NULL;

    // se deschid fisierele pentru input si output
    FILE *in = fopen("tema1.in", "r");
    FILE *out = fopen("tema1.out", "w");

    // se citete nr de operatii
    int n;
    fscanf(in, "%d\n", &n);
    
    // se citesc n operatii
    for (int i = 0; i < n; ++i) {
        char operatie[32];
        fgets(operatie, 32, in); // se citeste o operatie

        // se elimina newline \n din operatie daca exista
        while (operatie[strlen(operatie) - 1] == '\n'
            || operatie[strlen(operatie) - 1] == ' ')
            operatie[strlen(operatie) - 1] = '\0';

        // daca e operatie de update se adauga in coada
        if (strstr(operatie, "MOVE_LEFT_CHAR")
            || (strstr(operatie, "MOVE_RIGHT_CHAR"))
            || (strstr(operatie, "MOVE_LEFT"))
            || (strstr(operatie, "MOVE_RIGHT"))
            || (strstr(operatie, "WRITE"))
            || (strstr(operatie, "INSERT_LEFT"))
            || (strstr(operatie, "INSERT_RIGHT"))) {
                execute = enqueue(execute, operatie);
        }
        else if (strstr(operatie, "SHOW_CURRENT"))
            show_current(banda, out);
        else if (strstr(operatie, "SHOW"))
            show(banda, out);
        else if (strstr(operatie, "UNDO")) {
            redo = push(redo, banda.deget);
            banda.deget = top(undo);
            undo = pop(undo);
        }
        else if (strstr(operatie, "REDO")) {
            undo = push(undo, banda.deget);
            banda.deget = top(redo);
            redo = pop(redo);
        }
        else if (strstr(operatie, "EXECUTE")) {
            char op[32];
            strcpy(op, front(execute));
            if (strstr(op, "MOVE_LEFT_CHAR")) {
                undo = push(undo, banda.deget);
                move_left_char (&banda, op[strlen(op) - 1], out);
            }
            else if (strstr(op, "MOVE_RIGHT_CHAR")) {
                move_right_char (&banda, op[strlen(op) - 1]);
            }
            else if (strstr(op, "MOVE_LEFT")) {
                if (banda.deget->prev != banda.santinela)
                    undo = push(undo, banda.deget);
        
                move_left(&banda);
            }
            else if (strstr(op, "MOVE_RIGHT")) {
                undo = push(undo, banda.deget);
                move_right(&banda);
            }
            else if (strstr(op, "WRITE")) {
                write(&banda, op[strlen(op) - 1]);
                undo = freeStack(undo);
                redo = freeStack(redo);
            }
            else if (strstr(op, "INSERT_LEFT")) {
                insert_left(&banda, op[strlen(op) - 1], out);
                undo = freeStack(undo);
                redo = freeStack(redo);
            }
            else if (strstr(op, "INSERT_RIGHT")) {
                insert_right(&banda, op[strlen(op) - 1]);
                undo = freeStack(undo);
                redo = freeStack(redo);
            }
            execute = dequeue(execute);
        }
    }

    // se elibereaza toata memoria
    banda.santinela = deleteList(banda.santinela);
    execute = freeQueue(execute);
    undo = freeStack(undo);
    redo = freeStack(redo);
    fclose(in);
    fclose(out);
    return 0;
}
