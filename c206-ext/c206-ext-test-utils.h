/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Metody pro testy pro rozšíření příkladu c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Daniel Dolejška, září 2024
 */

#ifndef C206_TEST_H
#define C206_TEST_H

#include "c206-ext.h"

#define TEST(NAME, DESCRIPTION)                                                \
void NAME(void) {                                                              \
	printf("\n[%s] %s\n", #NAME, DESCRIPTION);                                 \
    DLList _queue_list;                                                        \
	DLList *test_queue_list = &_queue_list;                                    \
	DLList _output_list;                                                       \
	DLList *test_output_list = &_output_list;

#define ENDTEST                                                                \
	test_dispose_queue_list(test_queue_list);                                  \
	test_dispose_list(test_output_list);                                       \
}

#define FAIL(REASON) printf("[FAILED] %s", REASON)

void test_print_list(DLList *);
void test_dispose_list(DLList *);
void test_dispose_queue_list(DLList *);

void test_print_current_packet_count(DLList *list);
void test_print_current_queue_count(DLList *list);
void test_print_list_of_packets(DLList *);
void test_print_list_of_qosLists(DLList *);

#endif
