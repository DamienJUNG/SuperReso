#include "trame.h"

void init_trame(TRAME *trame){

    for(int i=0;i<=7;i++){
        trame->preamble[i]=170; // oui c'est pas ouf chut
    }
    trame->sof = 171
    //trame->destination
    //trame->source
    //trame->type
    //trame->data
    for(int i=0;i<=4;i++){
        trame->fcs[i]=1; // oui c'est pas ouf chut
    }
}
void create_trame(TRAME *trame,unsigned char *src, unsigned char *dest,unsigned char *data){
    trame->source=src;
    trame->destination=dest;
    trame->type=strlen(data);
    trame->data;
}
void show_trame(TRAME *trame){
    printf("««««« TRAME »»»»»\n");
    printf("|");
    for(int i=0;i<7;++){
        printf("%u",trame->preamble[i]);
    }
    printf("|%u|",sof);
    for(int i=0;i<6;++){
        printf("%u",trame->destination[i]);
    }
    printf("|");
    for(int i=0;i<6;++){
        printf("%u",trame->source[i]);
    }
    printf("|%d|",type)
    for(int i=0;i<type;++){
        printf("%u",trame->data[i]);
    }
    printf("|");
    for(int i=0;i<4;++){
        printf("%u",trame->fcs[i]);
    }
    printf("|");


}




























