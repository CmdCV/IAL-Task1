#include "c201.h"
#include "c201-test-utils.h"

#include <stdio.h>
#include <stdlib.h>

#define TEST_COUNT ((long int) (sizeof(tests) / sizeof(void *)))


TEST(test_init, "Inicializace struktury")
	List_Init(test_list);

	test_print_list(test_list);
ENDTEST

TEST(test_get_first_empty, "Získání hodnoty prvního prvku v prázdném seznamu")
	List_Init(test_list);
	test_print_list(test_list);

	int test_result;
	List_GetFirst(test_list, &test_result);
ENDTEST

TEST(test_first_empty, "Aktivace prvního prvku v prázdném seznamu")
	List_Init(test_list);
	test_print_list(test_list);

	List_First(test_list);
	test_print_active_element(test_list);
ENDTEST

TEST(test_insert_first, "Vkládání nových prvků na první místo")
	List_Init(test_list);

	List_InsertFirst(test_list, 4);
	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);

	test_print_list(test_list);
ENDTEST

TEST(test_get_value_inactive, "Získání hodnoty prvku v seznamu bez aktivního prvku")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	int test_result;
	List_GetValue(test_list, &test_result);
ENDTEST

TEST(test_set_value_inactive, "Aktualizace hodnoty prvku v seznamu bez aktivního prvku")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	List_SetValue(test_list, 3);
	test_print_list(test_list);
ENDTEST

TEST(test_next_inactive, "Aktivace následujícího prvku v seznamu bez aktivního prvku")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	List_Next(test_list);
	test_print_active_element(test_list);
ENDTEST

TEST(test_get_first, "Získání hodnoty prvního prvku")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	int test_result;
	List_GetFirst(test_list, &test_result);
	printf("%-15s: %d\n", "Returned value", test_result);
ENDTEST

TEST(test_get_value, "Získání hodnot aktivních prvků")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	int test_result;
	List_First(test_list);
	List_GetValue(test_list, &test_result);
	printf("%-15s: %d\n", "Returned value", test_result);

	List_Next(test_list);
	List_GetValue(test_list, &test_result);
	printf("%-15s: %d\n", "Returned value", test_result);

	List_Next(test_list);
	List_GetValue(test_list, &test_result);
	printf("%-15s: %d\n", "Returned value", test_result);
ENDTEST

TEST(test_set_value, "Aktualizace hodnot aktivních prvků")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);

	List_SetValue(test_list, 99);
	test_print_list(test_list);

	List_First(test_list);
	List_SetValue(test_list, 3);
	test_print_list(test_list);

	List_Next(test_list);
	List_Next(test_list);
	List_SetValue(test_list, 1);

	test_print_list(test_list);
ENDTEST

TEST(test_first_next_activity, "Nastavení aktivity na následnících")
	List_Init(test_list);
	test_print_active_element(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);

	List_First(test_list);
	test_print_list(test_list);

	List_Next(test_list);
	test_print_active_element(test_list);

	List_Next(test_list);
	test_print_active_element(test_list);

	List_Next(test_list);
	test_print_active_element(test_list);
ENDTEST

TEST(test_is_active, "Aktivita seznamu")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);
	printf("Is list element active? %s\n", List_IsActive(test_list) ? "Yes" : "No");

	List_First(test_list);
	printf("Is list element active? %s\n", List_IsActive(test_list) ? "Yes" : "No");

	List_Next(test_list);
	printf("Is list element active? %s\n", List_IsActive(test_list) ? "Yes" : "No");

	List_Next(test_list);
	printf("Is list element active? %s\n", List_IsActive(test_list) ? "Yes" : "No");

	List_Next(test_list);
	printf("Is list element active? %s\n", List_IsActive(test_list) ? "Yes" : "No");
ENDTEST

TEST(test_insert_after_last, "Vložení několika prvků na poslední místo")
	List_Init(test_list);

	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	List_First(test_list);
	List_InsertAfter(test_list, 2);
	test_print_list(test_list);

	List_Next(test_list);
	List_InsertAfter(test_list, 3);
	test_print_list(test_list);

	List_Next(test_list);
	List_InsertAfter(test_list, 4);
	test_print_list(test_list);
ENDTEST

TEST(test_delete_first, "Zrušení prvního prvku v seznamu")
	List_Init(test_list);

	List_InsertFirst(test_list, 1);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 3);
	test_print_list(test_list);

	List_DeleteFirst(test_list);
	test_print_list(test_list);

	List_DeleteFirst(test_list);
	test_print_list(test_list);

	List_DeleteFirst(test_list);
	test_print_list(test_list);

	List_DeleteFirst(test_list);
	test_print_list(test_list);
ENDTEST

TEST(test_delete_after, "Zrušení prvku po aktivním prvku")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	List_InsertFirst(test_list, 1);

	List_DeleteAfter(test_list);
	test_print_list(test_list);

	List_First(test_list);
	List_DeleteAfter(test_list);
	test_print_list(test_list);

	List_Next(test_list);
	List_DeleteAfter(test_list);
	test_print_list(test_list);

	List_Next(test_list);
	List_DeleteAfter(test_list);
	test_print_list(test_list);
ENDTEST

TEST(test_dispose, "Zrušení prvků seznamu")
	List_Init(test_list);

	List_InsertFirst(test_list, 3);
	List_InsertFirst(test_list, 2);
	List_InsertFirst(test_list, 1);
	test_print_list(test_list);

	List_Dispose(test_list);
	test_print_list(test_list);
ENDTEST

void (*tests[])(void) = {
		test_init,
		test_get_first_empty,
		test_first_empty,
		test_insert_first,
		test_get_value_inactive,
		test_set_value_inactive,
		test_next_inactive,
		test_get_first,
		test_get_value,
		test_set_value,
		test_is_active,
		test_first_next_activity,
		test_insert_after_last,
		test_delete_first,
		test_delete_after,
		test_dispose,
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
		printf("C201 - Linked List, Basic Tests\n");
		printf("===============================\n");

		for (test_id = 0; test_id < TEST_COUNT; test_id++)
		{
			tests[test_id]();
		}
	}

	return 0;
}

/* Konec c201-test.c */
