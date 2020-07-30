#include "Participant.h"
#include "Repo.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

DynamicArray createEmpty()
{
	DynamicArray array;
	array.size = 0;
	array.capacity = 10;
	array.elems = malloc(sizeof(ElemType) * array.capacity);
	return array;
}

ElemType get(DynamicArray* array, int poz)
{
	return array->elems[poz];
}


void insert(DynamicArray* array, Participant p)
{
	if (array->capacity == array->size) {
		reallocate(array);
	}
	array->elems[array->size] = p;
	(array->size)++;
}


void deleteAll(DynamicArray* array)
{
	for (int i = 0; i < array->size; i++)
		distrugeParticipant(&array->elems[i]);
	array->size = 0;
}

int length(DynamicArray array)
{
	return array.size;
}

void reallocate(DynamicArray* array)
{
	int newCapacity = array->capacity + 5;
	ElemType* aux = malloc(sizeof(ElemType) * newCapacity);
	for (int i = 0; i < array->size; i++)
		if(aux) 
			aux[i] = array->elems[i];
	free(array->elems);
	array->elems = aux;
	array->capacity = newCapacity;
}

int getScor(DynamicArray* array, int poz)
{
	return array->elems[poz].scor;
}

ElemType* getBy(DynamicArray* lista, char* nume, char* prenume)
{
	for (int i = 0; i < lista->size; i++) {
		if (strcmp(lista->elems[i].nume, nume) == 0)
			if (strcmp(lista->elems[i].prenume, prenume) == 0)
				return &(lista->elems[i]);
	}
	return NULL;
}

void actualizeazaRepo(DynamicArray* array, char* nume, char* prenume, int scorNou)
{
	Participant* p = getBy(array, nume, prenume);
	if (p != NULL) {
		setScor(p, scorNou);
	}
}

void destroy(DynamicArray* array)
{
	for (int i = 0; i < array->size; i++)
		distrugeParticipant(&array->elems[i]);
	free(array->elems);
	array->elems = NULL;
	array->size = 0;
	array->capacity = 0;
}

void testCreateDestroy()
{
	DynamicArray array = createEmpty();
	assert(length(array) == 0);
	assert(array.capacity == 10);
	destroy(&array);
	assert(array.size == 0);
	assert(array.capacity == 0);
}

void testInsertDelete()
{
	DynamicArray array = createEmpty();
	insert(&array, creeazaParticipant("nume", "prenume", 4));
	insert(&array, creeazaParticipant("nume", "prenume", 10));
	insert(&array, creeazaParticipant("nume", "prenume", 20));
	assert(length(array) == 3);
	deleteAll(&array);
	assert(length(array) == 0);
	assert(array.capacity == 10);
	for (int i = 0; i < 15; i++)
		insert(&array, creeazaParticipant("nume", "prenume", i + 50));
	assert(length(array) == 15);
	assert(array.capacity == 15);
	destroy(&array);
}
