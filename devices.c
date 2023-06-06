#include "devices.h"

uint64_t build_mac(char* token){
    uint64_t mac = 0;
    char *field = strtok(token,":");
    for(int i=0;i<5;i++){
        mac += str_to_int(field);
        mac = mac << 8;
        field = strtok(NULL,":");
    }
    mac += str_to_int(field);
    return mac;
}
unsigned int str_to_int(char* field){
    int i=0;
    int hex=0;
    int taille = strlen(field);
    while(field[i]!='\0'){
        if(field[i]>=48 && field[i]<=57){
            hex+=(field[i]-48) * power(16,(taille-i));
        }
        else if (field[i]>=65 && field[i]<=90){
            hex+= (field[i]-55) * power(16,(taille-i));
        }
        else if(field[i]>=97 && field[i]<=122){
            hex+=(field[i]-87) * power(16,(taille-i));
        }
        i++;
    }
    return hex;
}
int power(int nb, int expo){
    int res = 1;
    for(int i=1;i<expo;i++){
        res*=nb;
    }
    return res;
}

uint32_t build_ip(char* addr){
    uint32_t ip = 0;
    char *field = strtok(addr,".");
    for (int i = 0; i < 3; ++i)
    {
        ip += atoi(field);
        field = strtok(NULL,".");
        ip = ip << 8;
    }
    ip += atoi(field);
    return ip;
}

int know_destintaion(bridge my_bridge, uint64_t mac){
    for (int i = 0; i < my_bridge.nb_ports; ++i)
    {
        if (my_bridge.table[i].state!=0)
        {
            for (int c = 0;c<10 && my_bridge.table[i].mac[c]!=0; ++c)
            {
                if(compare_mac(my_bridge.table[i].mac[c], mac)){
                    return i;
                }
            }
        }   
    }
    return -1;
}

int compare_mac(uint64_t mac1, uint64_t mac2){
    return mac1==mac2;
}

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

void print_mac(uint64_t mac){
    for(int i=0;i<6;i++){
        if(i==5){
            printf("%02x",(uint8_t)(mac>>(40 - i * 8)));
        }
        else{
            printf("%02x:",(uint8_t)(mac>>(40 - i * 8)));
        }
    }
}

void print_ip(uint32_t ip){
    printf("%d.",(uint8_t)(ip>>24));
    printf("%d.",(uint8_t)(ip>>16));
    printf("%d.",(uint8_t)(ip>>8));
    printf("%d\n",(uint8_t)ip);
    printf("\n");
}

void print_commutation_table(bridge my_bridge)
{
    printf("o—————————————————————o——————o\n");
    printf("|        @mac         | PORT |\n");
    printf("o—————————————————————o——————o\n");
    for(int i=0;i<my_bridge.nb_ports;i++){
        for(int j=0;j<my_bridge.table[i].nb_mac;j++){
            printf("|  ");
            print_mac(my_bridge.table[i].mac[j]);
            printf("  |  %02d  |\n", i);
            printf("o—————————————————————o——————o\n");
        }
    }
    printf("\n");
}