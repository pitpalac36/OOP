#include "sortare.h"
#include <assert.h>

int inRelatie(ElemType e1, ElemType e2, char* atribut, char* ordine)
{
    if (strcmp(ordine, "crescatoare") == 0)
        if (strcmp(atribut, "nume") == 0)
            return (strcmp(e2.nume, e1.nume));
        else
            return e2.scor - e1.scor;
    else
        if (strcmp(atribut, "nume") == 0)
            return (strcmp(e1.nume, e2.nume));
        else
            return e1.scor - e2.scor;
}


void testRelatie() {
    Participant p1 = creeazaParticipant("pop", "ana", 100);
    Participant p2 = creeazaParticipant("popan", "irina", 1050);
    assert(inRelatie(p1, p2, "nume", "crescatoare") > 0);
    assert(inRelatie(p1, p2, "nume", "descrescatoare") < 0);
    assert(inRelatie(p1, p2, "scor", "crescatoare") > 0);
    assert(inRelatie(p1, p2, "scor", "descrescatoare") < 0);
    distrugeParticipant(&p1);
    distrugeParticipant(&p2);
}