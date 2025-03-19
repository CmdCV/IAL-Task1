/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Rozšíření pro příklad c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Daniel Dolejška, září 2024
 */

#include "c206-ext.h"

bool error_flag;
bool solved;

/**
 * Tato metoda simuluje příjem síťových paketů s určenou úrovní priority.
 * Přijaté pakety jsou zařazeny do odpovídajících front dle jejich priorit.
 * "Fronty" jsou v tomto cvičení reprezentovány dvousměrně vázanými seznamy
 * - ty totiž umožňují snazší úpravy pro již zařazené položky.
 * 
 * Parametr `packetLists` obsahuje jednotlivé seznamy paketů (`QosPacketListPtr`).
 * Pokud fronta s odpovídající prioritou neexistuje, tato metoda ji alokuje
 * a inicializuje. Za jejich korektní uvolnení odpovídá volající.
 * 
 * V případě, že by po zařazení paketu do seznamu počet prvků v cílovém seznamu
 * překročil stanovený MAX_PACKET_COUNT, dojde nejdříve k promazání položek seznamu.
 * V takovémto případě bude každá druhá položka ze seznamu zahozena nehledě
 * na její vlastní prioritu ovšem v pořadí přijetí.
 * 
 * @param packetLists Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param packet Ukazatel na strukturu přijatého paketu
 */
void receive_packet(DLList *packetLists, PacketPtr packet) {
    // Najdeme nebo vytvoříme frontu s prioritou odpovídající paketu
    QosPacketListPtr targetQueue = NULL;
    DLL_First(packetLists);
    for (QosPacketListPtr queue; DLL_IsActive(packetLists); DLL_Next(packetLists)) {
        DLL_GetValue(packetLists, (long*)&queue);
        if (queue->priority == packet->priority) {
            targetQueue = queue;
            break;
        }
    }
    // Pokud fronta neexistuje, vytvoříme novou
    if (targetQueue == NULL) {
        targetQueue = (QosPacketListPtr) malloc(sizeof(QosPacketList));
        if (targetQueue == NULL) {
            return;
        }
        targetQueue->priority = packet->priority;
        targetQueue->list = (DLList *) malloc(sizeof(DLList));
        if (targetQueue->list == NULL) {
            free(targetQueue);
            return;
        }
        DLL_Init(targetQueue->list);
        DLL_InsertLast(packetLists, (long) targetQueue);
    }

    // Pokud seznam přesáhne maximální povolený počet, zmenšíme ho
    if (targetQueue->list->currentLength == MAX_PACKET_COUNT) {
        DLL_First(targetQueue->list);  // Aktivuje první prvek seznamu
        while (DLL_IsActive(targetQueue->list)) {
            DLL_DeleteAfter(targetQueue->list);  // Smažeme prvek za aktivním prvkem
            DLL_Next(targetQueue->list);  // Posune se o jeden prvek dopředu
        }
    }

    // Vložíme paket do fronty
    DLL_InsertLast(targetQueue->list, (long) packet);
}

/**
 * Tato metoda simuluje výběr síťových paketů k odeslání. Výběr respektuje
 * relativní priority paketů mezi sebou, kde pakety s nejvyšší prioritou
 * jsou vždy odeslány nejdříve. Odesílání dále respektuje pořadí, ve kterém
 * byly pakety přijaty metodou `receive_packet`.
 * 
 * Odeslané pakety jsou ze zdrojového seznamu při odeslání odstraněny.
 * 
 * Parametr `packetLists` obsahuje ukazatele na jednotlivé seznamy paketů (`QosPacketListPtr`).
 * Parametr `outputPacketList` obsahuje ukazatele na odeslané pakety (`PacketPtr`).
 * 
 * @param packetLists Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param outputPacketList Ukazatel na seznam paketů k odeslání
 * @param maxPacketCount Maximální počet paketů k odeslání
 */
void send_packets(DLList *packetLists, DLList *outputPacketList, int maxPacketCount) {
    // Projdeme všechny prioritní fronty (packetLists)
    while (outputPacketList->currentLength < maxPacketCount) {
        QosPacketListPtr highestPriorityList = NULL;

        // Najdeme neprázdnou frontu s nejvyšší prioritou
        DLL_First(packetLists);
        for (QosPacketListPtr currentQosList; DLL_IsActive(packetLists); DLL_Next(packetLists)) {
            DLL_GetValue(packetLists, (long*)&currentQosList);
            if (currentQosList->list->currentLength > 0 && (highestPriorityList == NULL || currentQosList->priority > highestPriorityList->priority)) {
                highestPriorityList = currentQosList;
            }
        }

        // Pokud neexistuje žádná neprázdná fronta s pakety, skončíme
        if (highestPriorityList == NULL) {
            break;
        }

        // Projdeme jednotlivé pakety v aktuální frontě
        DLL_First(highestPriorityList->list);
        for (long packetData; DLL_IsActive(highestPriorityList->list) && outputPacketList->currentLength < maxPacketCount; DLL_DeleteFirst(highestPriorityList->list)) {
            DLL_GetValue(highestPriorityList->list, &packetData);
            DLL_InsertLast(outputPacketList, packetData);
            DLL_Next(highestPriorityList->list);
        }
    }
}
