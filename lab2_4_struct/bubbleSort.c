#include "bubbleSort.h"
#include <assert.h>

void BubbleSort(List* lista, char* criteriu, char* ordine)
{
    ElemType temp;
    int i, j;
    for (i = 0; i < dimensiune(lista) - 1; i++) {
        for (j = i + 1; j < dimensiune(lista); j++) {
            if (!inRelatie(lista->elems[i], lista->elems[j], criteriu, ordine)) {
                temp = lista->elems[i];
                lista->elems[i] = lista->elems[j];
                lista->elems[j] = temp;
            }
        }
    }
}
