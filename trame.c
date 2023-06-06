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
    //trame->data;
    unsigned char *data_temp = NULL;
    int taille = trame->type;
    int tailleBourrage = 46; //1454
    if(trame->type>=1454){
        tailleBourrage = tailleBourrage-(trame->type-1454); //obtient la taille du bourrage
    }
    data_temp = malloc(sizeof(unsigned char) * (trame->type+tailleBourrage)); // data temporaire
    for(int i=0;i<taille;i++){ // met le message dans le data temporaire
        data_temp[i]=data[i]
    }
    for(int i=taille-1;i<(trame->type+tailleBourrage);i++){ // effectue le bourrage du reste
        data_temp[i]=0;
    }
    trame->data=data_temp;

}
void show_trame(TRAME *trame){
    printf("««««« TRAME »»»»»\n");
    printf("|");
    for(int i=0;i<7;++){
        printf("%u",trame->preamble[i]);
    }
    printf("|%u|",trame->sof);
    for(int i=0;i<6;++){
        printf("%u",trame->destination[i]);
    }
    printf("|");
    for(int i=0;i<6;++){
        printf("%u",trame->source[i]);
    }
    printf("|%d|",trame->type)
    for(int i=0;i<trame->type;++){
        printf("%u",trame->data[i]);
    }
    printf("|");
    for(int i=0;i<4;++){
        printf("%u",trame->fcs[i]);
    }
    printf("|\n");
}

