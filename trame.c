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





























