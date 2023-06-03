#include <stdio.h>

#define BRIDGE 2
#define STATION 1
#define BROADCAST 0xffffffffffff
#define MAX_DEVICES 32

typedef struct commutation {
    uint64_t **mac;
    uint8_t *state;
}commutation;

typedef struct station
{
	uint64_t mac;
	uint32_t ip;
} station;

typedef struct bridge {
	uint64_t mac;
	uint8_t nb_ports;
	uint16_t priority;
	commutation table[64];//table de commutation
} bridge;

typedef struct device
{
	int type;
	int number;	
}device;

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

uint64_t build_mac(char* token);
unsigned int str_to_int(char* field);
int power(int nb, int expo);
uint32_t build_ip(char* addr);
void receive_frame(station *receiver, frame *message);
int compare_mac(uint64_t mac1, uint64_t mac2);
void create_frame(frame *frame,uint64_t src, uint64_t dest, uint8_t const *data, size_t size);
void show_frame(frame *frame);
