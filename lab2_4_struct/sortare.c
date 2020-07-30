#include "sortare.h"
#include <assert.h>
#include <compare>



bool inRelatie(ElemType e1, ElemType e2, char* atribut, char* ordine)
{
    if (strcmp(ordine, "crescatoare") == 0) {
        if (strcmp(atribut, "nume") == 0)
            return (strcmp(e1.nume, e2.nume) <= 0);
        else
            return e1.scor <= e2.scor;
    }
    else {
        if (strcmp(atribut, "nume") == 0)
            return (strcmp(e1.nume, e2.nume) >= 0);
        else
            return e1.scor >= e2.scor;
    }
}
