#include "bubbleSort.h"
#include <assert.h>
#include "Repo.h"

void BubbleSort(DynamicArray* lista, char* criteriu, char* ordine)
{
    ElemType temp;
    int i, j;
    for (i = 0; i < lista->size - 1; i++) {
        for (j = i + 1; j < lista->size; j++) {
            if (inRelatie(lista->elems[i], lista->elems[j], criteriu, ordine) < 0)
            {
                temp = lista->elems[i];
                lista->elems[i] = lista->elems[j];
                lista->elems[j] = temp;
            }
        }
    }
}


void testSortare() {
    DynamicArray lista = createEmpty();
    insert(&lista, creeazaParticipant("pop", "ana", 100));
    insert(&lista, creeazaParticipant("popan", "mihaela", 1234));
    insert(&lista, creeazaParticipant("mihaescu", "ingrid", 1010));
    insert(&lista, creeazaParticipant("albu", "ana", 30));
    insert(&lista, creeazaParticipant("aa", "irsd", 112345));
    BubbleSort(&lista, "scor", "crescatoare");
    assert(get(&lista, 0).scor == 30);
    assert(get(&lista, 1).scor == 100);
    assert(get(&lista, 2).scor == 1010);
    assert(get(&lista, 3).scor == 1234);
    assert(get(&lista, 4).scor == 112345);
    destroy(&lista);
}

