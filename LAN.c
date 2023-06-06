#include "LAN.h"

uint8_t count_frame;

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
}

void free_Lan(LAN *lan){
    free(lan->bridges);
    free(lan->stations);
    lan->bridges=NULL;
    lan->stations=NULL;
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
            my_bridge.table->nb_mac = 0;
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
            ajouter_arete(lan->graphe,(arete){source,destination});        
        }
    }
    fclose(file);
}

void add_bridge(LAN *lan, bridge *my_bridge){
    lan->bridges[lan->nb_bridge] = *my_bridge;
    lan->nb_bridge+=1;
}
void add_station(LAN *lan, station *stat){
    lan->stations[lan->nb_station] = *stat;
    lan->nb_station+=1;
}



void receive_frame(station *receiver, frame *message, uint8_t level){
    if(compare_mac(receiver->mac,message->destination) || compare_mac(message->destination,BROADCAST)){
        printf("Message lu par la station\n");
        shift(level);
        printf("Adresse mac : ");
        print_mac(receiver->mac);
        printf("\n");
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
        printf("\n");
        shift(level);
        printf("Adresse ip : ");
        print_ip(receiver->ip);
        printf("\n");
    }
}



void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message, uint8_t level){
    if(count_frame>lan->graphe->nb_aretes){
        return ;
    }
    count_frame++;
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
                if(know_destintaion(lan->bridges[actuel],message->source)==-1){
                lan->bridges[actuel].table[i].mac[lan->bridges[actuel].table[i].nb_mac] = message->source;
                lan->bridges[actuel].table[i].nb_mac = (lan->bridges[actuel].table[i].nb_mac+1)%10;
                }
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
        int i=0;
        while(sa[i]!=source && i<nb){
            i++;
        }
        lan->bridges[actuel].table[i].state=2;
        if(know_destintaion(lan->bridges[actuel],message->source)==-1){
            lan->bridges[actuel].table[i].mac[lan->bridges[actuel].table[i].nb_mac] = message->source;
            lan->bridges[actuel].table[i].nb_mac = (lan->bridges[actuel].table[i].nb_mac+1)%10;
        }
    }
    shift(level);
    printf("-- SWITCH %d --\n",actuel);
    if(transfert>0){
        printf("\n");
    }
}

void transfert_frame(sommet source, LAN *lan, frame *message){
    count_frame=0;
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



void show_stations(LAN *lan){
    printf("\n");
    for (int i = 0; i < lan->nb_station; ++i)
    {
        printf("\t## STATION %d ##\n",i);
        printf("\t## Adresse mac : ");
        print_mac(lan->stations[i].mac);
        printf("\n\t## Adresse ip : ");
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
        printf("\n\t## Nombre de ports : %d\n",lan->bridges[i].nb_ports);
        printf("\t## Priorité : %d\n",lan->bridges[i].priority);
        /*printf("Table de commutation :\n");
        print_commutation_table(lan->bridges[i]);*/
        printf("\n");
    }
}



void ask_frame(LAN lan){
    sommet source;
    sommet destination;

    printf("Entrez le numéro de la station source station :\n");
    scanf("%ld",&source);
    printf("Entrez le numéro de la station de destination station :\n");
    scanf("%ld",&destination);
    printf("\n");

    frame message;
    char * data = malloc(sizeof(char) * 1501);
    printf("Que voulez-vous mettre dans la trame ?\n");
    scanf("%1500s",data);
    if(destination==-1){
        create_frame(&message,lan.stations[source].mac,BROADCAST,(uint8_t const*)data, strlen(data));
    }
    else{
        create_frame(&message,lan.stations[source].mac,lan.stations[destination].mac,(uint8_t const*)data, strlen(data));
    }
    free(data);
    transfert_frame(source+lan.nb_bridge,&lan,&message);
    printf("\n\n## Voici le message qui a été transféré ##\n");
    show_frame(&message);
    printf("## Version prof de réseau ##\n");
    show_frame_for_dev(&message);
    printf("\n\n");
}

void show_network(LAN *lan){
    sommet sa[64];
    for(int i=0;i<lan->nb_bridge+lan->nb_station;i++){
        int nb = sommets_adjacents(lan->graphe,i,sa);
        printf("%d - ",i);
        if(i>=lan->nb_bridge){
            printf("station %d (%d voisins)",i-lan->nb_bridge,nb);
            if (nb>0)
            {
                printf(" :");
                for (int c = 0; c < nb; ++c)
                {
                    printf(" %d",sa[c]);
                }
            }
            printf("\n");
        }
        else{
            printf("swicth %d (%d voisins)",i,nb);
            if (nb>0)
            {
                printf(" :");
                for (int c = 0; c < nb; ++c)
                {
                    printf(" %d",sa[c]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}