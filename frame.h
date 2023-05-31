#include <stdint.h>
#include <stdlib.h>

typedef struct frame
{
	unsigned char preamble[7];
    unsigned char sof;
    unsigned char destination[6];
    unsigned char source[6];
    unsigned int type;
    uint8_t *data;
    unsigned char fcs[4];

}frame;

void create_frame(frame *frame,unsigned char *src, unsigned char *dest, uint8_t const *data, size_t size);
void show_frame(frame *frame);



























