#include "frame.h"

#include <string.h>
#include <stdio.h>

void create_frame(frame *frame, uint64_t src, uint64_t dest, uint8_t const *data, size_t size){
    for(int i=0;i<=7;i++){
        frame->preamble[i]=170; // oui c'est pas ouf chut
    }
    frame->sof = 171;
    frame->source = src;
    frame->destination = dest;
    frame->type = size;
    frame->data = malloc(size);
    memcpy(frame->data, data, size);
    for(int i=0;i<=4;i++){
        frame->fcs[i]=1; // oui c'est pas ouf chut
    }
}
void show_frame(frame *frame){
    printf("««««« frame »»»»»\n");
    printf("|");
    for(int i=0;i<7;i++){
        printf("%b",frame->preamble);
    }
    printf("|\n|%b|\n",frame->sof);
    /*
    for(int i=0;i<6;i++){
        if(i!=5){
        printf("%02x:",frame->destination[i]);
        }
        else{
            printf("%02x",frame->destination[i]);   
        }
    }
    printf("\n|");
    for(int i=0;i<6;i++){
        if(i!=5){
            printf("%02x:",frame->source[i]);
        }
        else{
            printf("%02x",frame->source[i]);   
        }
    }*/
    printf("\n|%d|\n",frame->type);
    for(int i=0;i<frame->type;i++){
        printf("%c",frame->data[i]);
    }
    printf("\n|");
    for(int i=0;i<4;i++){
        printf("%u",frame->fcs[i]);
    }
    printf("|\n");
}




























