/*
 *  Předmět: Algoritmy (IAL) - FIT VUT v Brně
 *  Rozšíření pro příklad c206.c (Dvousměrně vázaný lineární seznam)
 *  Vytvořil: Daniel Dolejška, září 2024
 */

/* TENTO SOUBOR, PROSÍME, NEUPRAVUJTE! */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Využívá příklad c206 - dvousměrně vázaný seznam. */
#ifndef STUDENT_BUILD
#include "../c206/c206.h"
#else
#include "c206.h"
#endif

extern int MAX_PACKET_COUNT;

/** QoS Paket. */
typedef struct qos_packet_t {
	/** Identifikátor paketu. Neurčuje pořadí. */
	int id;
	/** Priorita odeslání paketu. */
	char priority;
} Packet, *PacketPtr;

/** QoS "fronta" s vlastní prioritou. */
typedef struct qos_packet_list_t {
	/** Priorita obsažených paketů. */
	char priority;
	/** "Fronta" obsahující pakety k odeslání. */
	DLList *list;
} QosPacketList, *QosPacketListPtr;

void receive_packet( DLList *packetLists, PacketPtr packet );

void send_packets( DLList *packetLists, DLList *outputPacketList, int packetCount );
