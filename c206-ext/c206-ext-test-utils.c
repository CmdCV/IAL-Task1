/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Metody pro testy pro rozšíření příkladu c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Daniel Dolejška, září 2024
 */

#include <stdio.h>
#include <string.h>
#include "c206-ext-test-utils.h"

const int MaxListLength = 10;

void test_print_current_packet_count(DLList *list) {
	printf("%-15s: %d\n", "Packet count", list->currentLength);
}

void test_print_current_queue_count(DLList *list) {
	printf("%-15s: %d\n", "Queue count", list->currentLength);
}

void print_packet(PacketPtr packet) {
	printf("Packet { .id = %2d, .priority = %3d }", packet->id, packet->priority);
}

void test_print_list_of_packets(DLList *list)
{
	if (list == NULL)
	{
		printf("The list is not initialized!\n");
		return;
	}

	test_print_current_packet_count(list);
	printf("%-15s:", "Queued packets");
	DLLElementPtr currentElement = list->firstElement;
	if (currentElement == NULL)
	{
		printf(" none (list is empty)");
	}

	int itemCount = 0;
	while (currentElement != NULL)
	{
		PacketPtr packet = (PacketPtr) currentElement->data;
		printf("\n  - ");
		print_packet(packet);
		currentElement = currentElement->nextElement;
		if (++itemCount > MaxListLength)
		{
			printf("*ERROR* Wrong element linking detected!\n");
			break;
		}
	}
	printf("\n");
}

void test_dispose_list(DLList *list)
{
	if (list == NULL)
	{
		printf("List was not initialised yet!\n");
		return;
	}

	DLLElementPtr temporaryElement;
	while (list->firstElement != NULL)
	{
		temporaryElement = list->firstElement->nextElement;
		free(list->firstElement);
		list->firstElement = temporaryElement;
	}
}

void test_dispose_queue_list(DLList *list)
{
	if (list == NULL)
	{
		printf("List was not initialised yet!\n");
		return;
	}

	DLLElementPtr temporaryElement;
	while (list->firstElement != NULL)
	{
		temporaryElement = list->firstElement->nextElement;
		QosPacketListPtr subList = (QosPacketListPtr) list->firstElement->data;
		test_dispose_list(subList->list);
		free(subList->list);
		free(subList);
		free(list->firstElement);
		list->firstElement = temporaryElement;
	}
}

void test_print_current_length(DLList *list)
{
	printf("%-15s: %d\n", "List length", list->currentLength);
}

void test_print_first_element(DLList *list)
{
	if (list->firstElement == NULL)
	{
		printf("%-15s: %s\n", "First element", "not initialised (list is empty)");
	}
	else
	{
		printf("%-15s: %ld\n", "First element", list->firstElement->data);
	}
}

void test_print_last_element(DLList *list)
{
	if (list->lastElement == NULL)
	{
		printf("%-15s: %s\n", "Last element", "not initialised (list is empty)");
	}
	else
	{
		printf("%-15s: %ld\n", "Last element", list->lastElement->data);
	}
}

void test_print_active_element(DLList *list)
{
	if (list->activeElement == NULL)
	{
		printf("%-15s: %s\n", "Active element", "not initialised (no item is active)");
	}
	else
	{
		printf("%-15s: %ld\n", "Active element", list->activeElement->data);
	}
}
