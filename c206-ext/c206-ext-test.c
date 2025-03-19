/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Základní testy pro rozšíření příkladu c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Daniel Dolejška, září 2024
 */

#include "c206-ext-test-utils.h"

#include <stdio.h>
#include <stdlib.h>

#define TEST_COUNT ((long int) (sizeof(tests) / sizeof(void *)))

int MAX_PACKET_COUNT = 10;

TEST(test_receive_send, "Přijetí a odeslání jednoho packetu")
	DLL_Init(test_queue_list);
	DLL_Init(test_output_list);

	Packet packet = { .id = 1, .priority = 0 };
	receive_packet(test_queue_list, &packet);
	send_packets(test_queue_list, test_output_list, 1);

	test_print_current_queue_count(test_queue_list);
	test_print_list_of_packets(test_output_list);
ENDTEST

TEST(test_receive_send_order, "Přijetí a odeslání packetu respektuje pořadí")
	DLL_Init(test_queue_list);
	DLL_Init(test_output_list);

	Packet packet1 = { .id = 1, .priority = 0 };
	Packet packet2 = { .id = 2, .priority = 0 };
	Packet packet3 = { .id = 3, .priority = 0 };
	receive_packet(test_queue_list, &packet1);
	receive_packet(test_queue_list, &packet2);
	receive_packet(test_queue_list, &packet3);
	send_packets(test_queue_list, test_output_list, 3);

	test_print_current_queue_count(test_queue_list);
	test_print_list_of_packets(test_output_list);
ENDTEST

TEST(test_receive_send_priority, "Přijetí a odeslání packetu respektuje prioritu")
	DLL_Init(test_queue_list);
	DLL_Init(test_output_list);

	Packet packet1 = { .id = 1, .priority = 0 };
	Packet packet2 = { .id = 2, .priority = 10 };
	Packet packet3 = { .id = 3, .priority = 5 };
	receive_packet(test_queue_list, &packet1);
	receive_packet(test_queue_list, &packet2);
	receive_packet(test_queue_list, &packet3);
	send_packets(test_queue_list, test_output_list, 3);

	test_print_current_queue_count(test_queue_list);
	test_print_list_of_packets(test_output_list);
ENDTEST

TEST(test_receive_send_drop, "Přijetí packetu zahodí každý druhý packet při přeplnění")
	DLL_Init(test_queue_list);
	DLL_Init(test_output_list);
	MAX_PACKET_COUNT = 4;

	Packet packet1 = { .id = 1, .priority = 0 };
	Packet packet2 = { .id = 2, .priority = 0 };
	Packet packet3 = { .id = 3, .priority = 0 };
	Packet packet4 = { .id = 4, .priority = 0 };
	Packet packet5 = { .id = 5, .priority = 0 };
	receive_packet(test_queue_list, &packet1);
	receive_packet(test_queue_list, &packet2);
	receive_packet(test_queue_list, &packet3);
	receive_packet(test_queue_list, &packet4);
	receive_packet(test_queue_list, &packet5);
	send_packets(test_queue_list, test_output_list, 3);

	test_print_current_queue_count(test_queue_list);
	test_print_list_of_packets(test_output_list);
ENDTEST

void (*tests[])(void) = {
		test_receive_send,
		test_receive_send_order,
		test_receive_send_priority,
		test_receive_send_drop,
};

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [test_id]\n", argv[0]);
		return 1;
	}

	char *test_id_reminder = NULL;
	long test_id;
	if (argc == 2)
	{
		test_id = strtol(argv[1], &test_id_reminder, 10);
		if (test_id_reminder[0] != 0)
		{
			fprintf(stderr, "Usage: %s {test_id}\n", test_id_reminder);
			fprintf(stderr, "Unexpected test_id: %s\n", test_id_reminder);
			return 1;
		}

		if (test_id < 0)
		{
			test_id = TEST_COUNT + test_id;
		}

		if (test_id + 1 > TEST_COUNT)
		{
			fprintf(stderr, "Unknown test: %ld (test count: %ld)\n", test_id, TEST_COUNT);
			return 1;
		}

		tests[test_id]();
	}
	else
	{
		printf("C206 Extension - Doubly Linked List as a Queue\n");
		printf("==============================================\n");

		for (test_id = 0; test_id < TEST_COUNT; test_id++)
		{
			tests[test_id]();
		}
	}

	return 0;
}

/* Konec c206-test.c */
