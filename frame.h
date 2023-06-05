#include <stdint.h>
#include <stdlib.h>

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

void create_frame(frame *frame,uint64_t src, uint64_t dest, uint8_t const *data, size_t size);
void show_frame(frame *frame);
