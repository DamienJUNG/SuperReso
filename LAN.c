#include "LAN.h"

void init_Lan(LAN *lan){
    lan->Switchs = malloc(sizeof(Switch) * 10);
    lan->stations = malloc(sizeof(station) * 10);
    lan->Switch_capacite = 10;
    lan->station_capacite = 10;
    lan->nb_Switch = 0;
    lan->nb_station = 0;
    lan->graphe = malloc(sizeof(graphe));
    init_graphe(lan->graphe);
    lan->devices = malloc(sizeof(device)*20);
}

void free_Lan(LAN *lan){
    free(lan->Switchs);
    free(lan->stations);
    free(lan->devices);
    lan->Switchs=NULL;
    lan->stations=NULL;
    lan->devices=NULL;
    free_graphe(lan->graphe);
    free(lan->graphe);
    lan->graphe = NULL;
    lan->nb_Switch = 0;
    lan->nb_station = 0;
    lan->Switch_capacite = 0;
    lan->station_capacite = 0;
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
    	if(atoi(string)==SWITCH && strstr(buffer,":")){
            printf("%s\n",buffer);
            Switch my_switch;
            //Initailisation du découpage
            token = strtok(buffer,";");
            //Récupération de l'adresse mac
            token = strtok(NULL,";");
            char *mac = token; //On la stocke pour plus tard

            //Attribution du nombre de ports et de la priorité
            token = strtok(NULL,";");
            my_switch.nb_ports = atoi(token);
            token = strtok(NULL,";");
            my_switch.priority = atoi(token);

            //Construction de l'adresse mac
            build_mac(mac,my_switch.mac);

            add_Switch(lan, &my_switch);
    	}
    	else if(atoi(string)==STATION && strstr(buffer,":")){
            printf("%s\n",buffer);
            station stat;
            //Initailisation du découpage
            char *token = strtok(buffer,";");
            //Récupération de l'adresse ip
            token = strtok(NULL,";");       
            char *mac = token; //On la stocke pour plus tard

            //Récupération de l'adresse ip
            token = strtok(NULL,";");
            build_ip(token,stat.ip);
            build_mac(mac,stat.mac);
            add_station(lan, &stat);
    	}
        else{
            char *token = strtok(buffer,";");
            int source = atoi(token);
            token = strtok(NULL,";");
            int destination = atoi(token);
            ajouter_arete(lan->graphe,(arete){source,destination});
            printf("ici\n");
        }
    }
    fclose(file);
}

void add_Switch(LAN *lan, Switch *my_switch){
    lan->devices[lan->nb_Switch+lan->nb_station] = (device){SWITCH,lan->nb_Switch};
    lan->Switchs[lan->nb_Switch] = *my_switch;
    lan->nb_Switch+=1;
}
void add_station(LAN *lan, station *stat){
    lan->devices[lan->nb_Switch+lan->nb_station] = (device){STATION,lan->nb_station};
    lan->stations[lan->nb_station] = *stat;
    lan->nb_station+=1;
}

void build_mac(char* token,unsigned char* mac){
    char *field = strtok(token,":");
    for(int i=0;i<6;i++){
        mac[i] = str_to_int(field);
        field = strtok(NULL,":");
    }
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

void build_ip(char* token, unsigned char* ip){
    char *field = strtok(token,".");
    for (int i = 0; i < 4; ++i)
    {
        ip[i]=atoi(field);
        field = strtok(NULL,".");
    }
}

void show_devices(LAN *lan){
    int max = lan->nb_station+lan->nb_Switch;
    for(int i=0;i<max;i++){
        if(lan->devices[i].type==SWITCH){
            printf("### Switch ###\n");
            print_mac(lan->Switchs[lan->devices[i].number].mac);
            printf("Priorité : %d\n",lan->Switchs[lan->devices[i].number].priority);
            printf("Nombres de ports : %d\n",lan->Switchs[lan->devices[i].number].nb_ports);
        }
        else{
            printf("### STATION ###\n");
            print_mac(lan->stations[lan->devices[i].number].mac);
            print_ip(lan->stations[lan->devices[i].number].ip);
        }
        printf("\n");
    }
}

void print_mac(unsigned char* mac){
    printf("Adresse mac : ");
    for(int i=0;i<6;i++){
        if(i==5){
            printf("%02x",mac[i]);
        }
        else{
            printf("%02x:",mac[i]);
        }
    }
    printf("\n");
}
void print_ip(unsigned char* ip){
    printf("Adresse ip : ");
    for(int i=0;i<4;i++){
        if (i==3){
            printf("%02d",ip[i]);
        }
        else{
            printf("%02d.",ip[i]);
        }
    }
    printf("\n");
}

void receive_frame(station *receiver, frame *message){
    if(compare_mac(receiver->mac,message->destination)){
        /*printf("Message lu par la station :");
        print_mac(receiver->mac);
        show_frame(message);*/
    }
    else{
        /*printf("Message ignoré par la station :");
        print_mac(receiver->mac);*/
    }
}

void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message){
    sommet sa[64];
    printf("-- SOMMET %d --\n",actuel);
    int nb = sommets_adjacents(lan->graphe,actuel,sa);
    for(int i=0;i<nb;i++){
        if(sa[i]==source){
            continue;
        }
        if(lan->devices[sa[i]].type==SWITCH)
        {
            printf("Passage par le sommet : %d\n",sa[i]);
            commute_frame(actuel, lan, sa[i], message);
        }
        if(lan->devices[sa[i]].type==STATION){
            printf("Envoi au sommet : %d\n",sa[i]);
            int index = lan->devices[sa[i]].number;
            receive_frame(&lan->stations[index],message);
        }
    }
    printf("\n");
}

void transfert_frame(sommet source, LAN *lan, frame *message){
    sommet sa[64];
    int nb = sommets_adjacents(lan->graphe, source, sa);
    printf("Départ sommet : %d\n",source);
    for (int i = 0; i < nb; ++i)
    {
        printf("Passage sommet : %d\n",sa[i]);
        if(lan->devices[sa[i]].type==SWITCH)
        {
            commute_frame(source, lan, lan->devices[sa[i]].number, message);
        }
        if(lan->devices[sa[i]].type==STATION){
            int index = lan->devices[sa[i]].number;
            receive_frame(&lan->stations[index],message);
        }
    }
}

int compare_mac(unsigned char* mac1, unsigned char *mac2){
    for (int i = 0; i < 6; ++i)
    {
        if(mac1[i]!=mac2[i]){
            return 0;
        }
    }
    return 1;
}



/*void affiche_my_switchutation(Switch monCom){
    printf("######### TABLE DE my_switchUTATION #########\n");
    for(int i=0;i<64;i++){
        printf("###### Switch 1 ######\n");
        printf("### PORTS ###\n");
        for(int y=0;y<monCom.table[i].nb_ligne;y++){
            printf("%d",monCom.table[i].ports[y]);
        }
        printf("### MAC ###\n");
        for(int y=0;y<6;y++){
            printf("%x",monCom.table[i].mac[y]);
        }
        printf("\n");
    }
}*/