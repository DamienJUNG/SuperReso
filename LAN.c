#include "LAN.h"

void init_Lan(LAN *lan){
    lan->commutateurs = malloc(sizeof(commutateur) * 10);
    lan->stations = malloc(sizeof(station) * 10);
    lan->commutateur_capacite = 10;
    lan->station_capacite = 10;
    lan->nb_commutateur = 0;
    lan->nb_station = 0;
    /*graphe g;
    init_graphe(&g);
    lan->graphe = g;*/
    lan->appareils = malloc(sizeof(appareil)*20);
}

void free_Lan(LAN *lan){
    free(lan->commutateurs);
    free(lan->stations);
    free(lan->appareils);
    //free_graphe(&lan->graphe);
    lan->nb_commutateur = 0;
    lan->nb_station = 0;
    lan->commutateur_capacite = 0;
    lan->station_capacite = 0;
}

void recupere_config(LAN *lan, const char * filename){
	FILE* file = fopen(filename,"r");
    char buffer[2048];
    unsigned int appareils;
    fgets(buffer,2048,file);
    while(fgets(buffer,2048,file)!=NULL){
        char string[2];
        string[0] = buffer[0];
        string[1] = '\0';
    	if(atoi(string)==COMMUTATEUR && strstr(buffer,":")){
            char *token = strtok(buffer,";");
            token = strtok(NULL,";");
            commutateur comm;
            comm.mac = construit_mac(token);
            //ajoute_commutateur(lan, rout_rout);
    	}
    	else if(atoi(string)==STATION && strstr(buffer,":")){
            //ajoute_station();
    	}
    }
    fclose(file);
}

void ajoute_commutateur(LAN *lan, commutateur comm){
    lan->commutateurs[lan->nb_commutateur] = comm;
    lan->nb_commutateur+=1;
}
void ajoute_station(LAN *lan, station stat){
    lan->stations[lan->nb_station] = stat;
    lan->nb_station+=1;
}

unsigned char* construit_mac(char* token){
    unsigned char* mac = malloc(sizeof(char)*6);
    char *champ = strtok(token,":");
    for(int i=0;i<7 && champ != NULL;i++){
        mac[i] = strtol(champ,NULL,16);
        printf("%s",champ);
        if(i!=5){
            printf(":");
        }
        champ = strtok(NULL,":");
    }
    printf("\n");
    return mac;
}