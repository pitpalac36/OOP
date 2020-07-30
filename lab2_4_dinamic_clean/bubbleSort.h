#pragma once
#include "sortare.h"

/*
 quick-sort nu merge dintr-un oarecare motiv, asa ca ordonez folosind bubble sort;
 ma folosesc de relatia definita in sortare.c
 */
void BubbleSort(DynamicArray* l, char* criteriu, char* ordine);

void testSortare();