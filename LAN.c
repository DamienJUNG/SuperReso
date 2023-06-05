#include "LAN.h"

static void shift(uint8_t n){
    for(int i=0;i<n;i++){
        printf("\t");
    }
}

void init_Lan(LAN *lan){
    lan->bridges = malloc(sizeof(bridge) * 10);
    lan->stations = malloc(sizeof(station) * 10);
    lan->nb_bridge = 0;
    lan->nb_station = 0;
    lan->graphe = malloc(sizeof(graphe));
    init_graphe(lan->graphe);
    lan->devices = malloc(sizeof(device)*20);
}

void free_Lan(LAN *lan){
    free(lan->bridges);
    free(lan->stations);
    free(lan->devices);
    lan->bridges=NULL;
    lan->stations=NULL;
    lan->devices=NULL;
    free_graphe(lan->graphe);
    free(lan->graphe);
    lan->graphe = NULL;
    lan->nb_bridge = 0;
    lan->nb_station = 0;
}

void get_config(LAN *lan, const char *filename){
    char *token;
	FILE* file = fopen(filename,"r");
    char buffer[2048];
    unsigned int devices;
    fgets(buffer,2048,file);
    token = strtok(buffer," ");
    for(int i=0;i<atoi(token);i++){
        ajouter_sommet(lan->graphe);
    }
    while(fgets(buffer,2048,file)!=NULL){
        char string[2];
        string[0] = buffer[0];
        string[1] = '\0';
    	if(atoi(string)==BRIDGE && strstr(buffer,":")){
            bridge my_bridge;
            //Initailisation du découpage
            token = strtok(buffer,";");
            //Récupération de l'adresse mac
            token = strtok(NULL,";");
            char *mac = token; //On la stocke pour plus tard

            //Attribution du nombre de ports et de la priorité
            token = strtok(NULL,";");
            my_bridge.nb_ports = atoi(token);
            token = strtok(NULL,";");
            my_bridge.priority = atoi(token);
            //Construction de l'adresse mac
            my_bridge.mac = build_mac(mac);

            my_bridge.table = malloc(sizeof(commutation) * my_bridge.nb_ports);
            my_bridge.table->state = 0;
            for (int i = 0; i < my_bridge.nb_ports; ++i)
            {
                my_bridge.table[i].mac = malloc(sizeof(uint64_t) * 10);
                for (int c = 0; c < 10; ++c)
                {
                    my_bridge.table[i].mac[c] = 0;
                }
            }
            add_bridge(lan, &my_bridge);
    	}
    	else if(atoi(string)==STATION && strstr(buffer,":")){
            station stat;
            //Initailisation du découpage
            char *token = strtok(buffer,";");
            //Récupération de l'adresse ip
            token = strtok(NULL,";");       
            char *mac = token; //On la stocke pour plus tard

            //Récupération de l'adresse ip
            token = strtok(NULL,";");
            stat.ip = build_ip(token);
            stat.mac = build_mac(mac);
            add_station(lan, &stat);
    	}
        else{
            char *token = strtok(buffer,";");
            int source = atoi(token);
            token = strtok(NULL,";");
            int destination = atoi(token);
            ajouter_arete(lan->graphe,(arete){source,destination});        }
    }
    fclose(file);
}

void add_bridge(LAN *lan, bridge *my_bridge){
    lan->devices[lan->nb_bridge+lan->nb_station] = (device){BRIDGE,lan->nb_bridge};
    lan->bridges[lan->nb_bridge] = *my_bridge;
    lan->nb_bridge+=1;
}
void add_station(LAN *lan, station *stat){
    lan->devices[lan->nb_bridge+lan->nb_station] = (device){STATION,lan->nb_station};
    lan->stations[lan->nb_station] = *stat;
    lan->nb_station+=1;
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

void show_devices(LAN *lan){
    int max = lan->nb_station+lan->nb_bridge;
    for(int i=0;i<max;i++){
        if(lan->devices[i].type==BRIDGE){
            printf("### SWITCH ###\n");
            print_mac(lan->bridges[lan->devices[i].number].mac);
            printf("Priorité : %d\n",lan->bridges[lan->devices[i].number].priority);
            printf("Nombres de ports : %d\n",lan->bridges[lan->devices[i].number].nb_ports);
        }
        else{
            printf("### STATION ###\n");
            print_mac(lan->stations[lan->devices[i].number].mac);
            print_ip(lan->stations[lan->devices[i].number].ip);
        }
        printf("\n");
    }
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
    printf("\n");
}
void print_ip(uint32_t ip){
    printf("%d.",(uint8_t)(ip>>24));
    printf("%d.",(uint8_t)(ip>>16));
    printf("%d.",(uint8_t)(ip>>8));
    printf("%d\n",(uint8_t)ip);
    printf("\n");
}

void receive_frame(station *receiver, frame *message, uint8_t level){
    if(compare_mac(receiver->mac,message->destination) || compare_mac(message->destination,BROADCAST)){
        printf("Message lu par la station\n");
        shift(level);
        printf("Adresse mac : ");
        print_mac(receiver->mac);
        shift(level);
        printf("Adresse ip : ");
        print_ip(receiver->ip);
        printf("\n");
        //show_frame(message);
    }
    else{
        printf("Message ignoré par la station :\n");
        shift(level);
        printf("Adresse mac : ");
        print_mac(receiver->mac);
        shift(level);
        printf("Adresse ip : ");
        print_ip(receiver->ip);
        printf("\n");
    }
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

void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message, uint8_t level){

    int transfert=0;
    //Affichage en fonction du niveau de profondeur
    shift(level);
    printf("-- SWITCH %d --\n",actuel);
    sommet sa[64];
    int nb = sommets_adjacents(lan->graphe,actuel,sa);
    int is_knew = know_destintaion(lan->bridges[actuel],message->destination);
    if (is_knew==-1)
    {
        for(int i=0;i<nb;i++){
            if (sa[i]!=source)
            {
                //Envoie du message à l'équipement concerné
                if(sa[i]>=lan->nb_bridge){
                    shift(level);
                    printf("Envoi à la station %d :\n",sa[i]-lan->nb_bridge);
                    shift(level);
                    receive_frame(&lan->stations[sa[i]-lan->nb_bridge],message, level);
                }
                else
                {
                    transfert++;
                    commute_frame(actuel, lan, sa[i], message, level+1);
                }
            }
            else{
                lan->bridges[actuel].table[i].state=2;
                int c = 0;
                while(c < 10 && lan->bridges[actuel].table[i].mac[c]!=0){
                    c++;
                }
                if (c==9){
                    c=0;
                }
                lan->bridges[actuel].table[i].mac[c] = message->source;
            }
        }
    }
    else{
        //Envoie du message à l'équipement concerné
        if(sa[is_knew]>=lan->nb_bridge){
            shift(level);
            printf("Envoi à la station %d :\n",sa[is_knew]-lan->nb_bridge);
            shift(level);
            receive_frame(&lan->stations[sa[is_knew]-lan->nb_bridge],message, level);
        }
        else
        {
            transfert++;
            commute_frame(actuel, lan, sa[is_knew], message, level+1);
        }
    }
    shift(level);
    printf("-- SWITCH %d --\n",actuel);
    if(transfert>0){
        printf("\n");
    }
}

void transfert_frame(sommet source, LAN *lan, frame *message){
    sommet sa[64];
    int nb = sommets_adjacents(lan->graphe, source, sa);
    if(nb>0){
        printf("Départ station : %d\n",source - lan->nb_bridge);
    }
    else{
        printf("La station est isolée, et ne peut communiquer avec aucun autre appareil.\n");
    }
    int level = 0;
    for (int i = 0; i < nb; ++i)
    {
        if(sa[i]>=lan->nb_bridge){
            receive_frame(&lan->stations[sa[i]-lan->nb_bridge],message,0);
        }
        else
        {
            commute_frame(source, lan, sa[i], message,level);
        }
    }
}

int compare_mac(uint64_t mac1, uint64_t mac2){
    return mac1==mac2;
}

void show_stations(LAN *lan){
    printf("\n");
    for (int i = 0; i < lan->nb_station; ++i)
    {
        printf("\t## STATION %d ##\n",i);
        printf("\t## Adresse mac : ");
        print_mac(lan->stations[i].mac);
        printf("\t## Adresse ip : ");
        print_ip(lan->stations[i].ip);
    }
}

void show_bridges(LAN *lan){
    printf("\n");
    for (int i = 0; i < lan->nb_bridge; ++i)
    {
        printf("\t## SWITCH %d ##\n",i);
        printf("\t## Adresse mac : ");
        print_mac(lan->bridges[i].mac);
        printf("\t## Nombre de ports : %d\n",lan->bridges[i].nb_ports);
        printf("\t## Priorité : %d\n",lan->bridges[i].priority);
        /*printf("Table de commutation :\n");
        print_commutation_table(lan->bridges[i]);*/
        printf("\n");
    }
}

void print_commutation_table(bridge my_bridge){
    sommet sa[64];
    for (int i = 0; i < my_bridge.nb_ports; ++i)
    {
        if(my_bridge.table[i].state!=0){
            printf("état du port %d : ",i);
            if (my_bridge.table[i].state==1)
            {
                printf("racine");
            }
            else if (my_bridge.table[i].state==2)
            {
                printf("désigné");
            }
            else if (my_bridge.table[i].state==-1)
            {
                printf("désactivé");
            }
            printf("\n");
            printf("Adresse mac : ");
            for(int c=0;c<10 && my_bridge.table[i].mac[c]!=0;c++){
                print_mac(my_bridge.table[i].mac[c]);
                printf("\n");
            }
            printf("\n");
        }
    }
}