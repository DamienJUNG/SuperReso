#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct frame
{
	uint8_t preamble[7];
    uint8_t sof;
    uint64_t destination;
    uint64_t source;
    uint8_t type;
    uint8_t *data;
    uint8_t fcs[4];
}frame;


typedef struct commutation {
    uint64_t *mac;
    uint8_t nb_mac;
    int state;
} commutation;

typedef struct station
{
	uint64_t mac;
	uint32_t ip;
} station;

typedef struct bridge {
	uint64_t mac;
	uint8_t nb_ports;
	uint16_t priority;
	commutation *table; //table de commutation
} bridge;

uint64_t build_mac(char* token);
unsigned int str_to_int(char* field);
int power(int nb, int expo);
uint32_t build_ip(char* addr);
int know_destintaion(bridge my_bridge, uint64_t mac);
int compare_mac(uint64_t mac1, uint64_t mac2);
void create_frame(frame *frame,uint64_t src, uint64_t dest, uint8_t const *data, size_t size);
void print_mac(uint64_t mac);
void print_ip(uint32_t ip);
void print_commutation_table(bridge my_bridge);