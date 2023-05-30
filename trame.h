#include <stdio.h>

typedef struct TRAME
{
	unsigned char preamble[7];
    unsigned char sof;
    unsigned char destination[6];
    unsigned char source[6];
    unsigned int type;
    unsigned char *data;
    unsigned char fcs[4];

}trame;

void init_trame(TRAME *trame);
void create_trame(TRAME *trame,unsigned char *src, unsigned char *dest,unsigned char *data);
void show_trame(TRAME *trame);



























