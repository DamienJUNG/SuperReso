#include "devices.h"

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

void create_frame(frame *message, uint64_t src, uint64_t dest, uint8_t const *data, size_t size){
    for(int i=0;i<=7;i++){
        frame->preamble[i]=170; // oui c'est pas ouf chut
    }
    message->sof = 171;
    message->source = src;
    message->destination = dest;
    message->type = size;
    message->data = malloc(size);
    memcpy(message->data, data, size);
    for(int i=0;i<=4;i++){
        message->fcs[i]=1; // oui c'est pas ouf chut
    }
        //trame->data;
    unsigned char *data_temp = NULL;
    int sizeM = message->type;
    int sizeFiller = 46; //1454
    if(message->type>=1454){
        sizeFiller = sizeFiller-(sizeM-1454); //obtient la taille du bourrage
    }
    data_temp = malloc(sizeof(unsigned char) * (sizeM+sizeFiller)); // data temporaire
    for(int i=0;i<sizeM;i++){ // met le message dans le data temporaire
        data_temp[i]=data[i];
    }
    for(int i=sizeM-1;i<(sizeM+sizeFiller);i++){ // effectue le bourrage du reste
        data_temp[i]=0;
    }
    message->data=data_temp;
}
void show_frame(frame *message){
    printf("««««« TRAME »»»»»\n");
    printf("|");
    for(int i=0;i<7;i++){
        printf("%u",message->preamble[i]);
    }
    printf("|%u|",message->sof);
    print_mac(message->destination);
    printf("\n|");
    print_mac(message->source);
    printf("\n|%d|",message->type);
    for(int i=0;i<message->type;i++){ // affichage du data pour les noobs
        printf("%u",message->data[i]);
    }
    printf("|");
    for(int i=0;i<4;i++){
        printf("%u",message->fcs[i]);
    }
    printf("|\n");
}
void show_frame_for_dev(frame *frame){
    printf("««««« TRAME »»»»»\n");
    printf("|");
    for(int i=0;i<7;i++){
        printf("%u",message->preamble[i]);
    }
    printf("|%u|",message->sof);
    print_mac(message->destination);
    printf("\n|");
    print_mac(message->source);
    printf("\n|%d|",message->type);
    int sizeFiller = 46;
    if(message->type>=1454){
        sizeFiller = sizeFiller-(message->type-1454); //obtient la taille du bourrage
    }
    for(int i=0;i<message->type+sizeFiller;i++){ // afiche le data pour les vrai
        printf("%u",message->data[i]);
    }
    printf("|");
    for(int i=0;i<4;i++){
        printf("%u",message->fcs[i]);
    }
    printf("|\n");

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