/* Předmět: Algoritmy (IAL) - FIT VUT v Brně
 * Hlavičkový soubor pro c201.c (Jednosměrně vázaný lineární seznam)
 * Vytvořil: Martin Tuček, září 2005
 * Upravil: Kamil Jeřábek, září 2020
 *          Daniel Dolejška, září 2021
 *
 * Tento soubor, prosíme, neupravujte!
 * Please, do not modify this file!
 */

#ifndef C201_H
#define C201_H

#include <stdbool.h>

/** Globální proměnná - indikuje, zda operace volala chybu. */
extern bool error_flag;
/** Globální proměnná - indikuje, zda byla operace řešena. */
extern bool solved;

/** Prvek jednosměrně vázaného seznamu. */
typedef struct ListElement {
	/** Užitečná data. */
    int data;
	/** Ukazatel na následující prvek seznamu. */
    struct ListElement *nextElement;
} *ListElementPtr;

/** Jednosměrně vázaný seznam. */
typedef struct {
	/** Ukazatel na první prvek seznamu. */
	ListElementPtr firstElement;
	/** Ukazatel na aktuální prvek seznamu. */
    ListElementPtr activeElement;
	/** Aktuální délka seznamu. */
	int currentLength;
} List;

void List_Init( List * );

void List_Dispose( List * );

void List_InsertFirst( List *, int );

void List_First( List * );

void List_GetFirst( List *, int * );

void List_DeleteFirst( List * );

void List_DeleteAfter( List * );

void List_InsertAfter( List *, int  );

void List_Next( List * );

void List_GetValue( List *, int * );

void List_SetValue( List *, int );

int List_IsActive( List * );

/* Konec hlavičkového souboru c201.h */
#endif
