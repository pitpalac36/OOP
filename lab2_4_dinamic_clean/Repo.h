#pragma once
#include "Participant.h"

typedef Participant ElemType;

typedef struct {
	ElemType* elems;
	int size;
	int capacity;
} DynamicArray;


DynamicArray createEmpty();


ElemType get(DynamicArray* array, int poz);


void insert(DynamicArray* array, Participant p);


void deleteAll(DynamicArray* array);


int length(DynamicArray array);


void reallocate(DynamicArray* array);


int getScor(DynamicArray* array, int poz);


ElemType* getBy(DynamicArray* lista, char* nume, char* prenume);


void actualizeazaRepo(DynamicArray* array, char* nume, char* prenume, int scorNou);


void destroy(DynamicArray* array);


void testCreateDestroy();


void testInsertDelete();