#include "LAN.h"

void init_Lan(LAN *lan){
    lan->routeurs = malloc(sizeof(routeur) * 10);
    lan->stations = malloc(sizeof(station) * 10);
    lan->nb_routeur = 10;
    lan->nb_station = 10;
    lan->curs_routeur = 0;
    lan->curs_station = 0;
    /*graphe g;
    init_graphe(&g);
    lan->graphe = g;*/
    lan->appareils = malloc(sizeof(appareil)*20);
}

void free_Lan(LAN *lan){
    free(lan->routeurs);
    free(lan->stations);
    free(lan->appareils);
    //free_graphe(&lan->graphe);
    lan->nb_routeur = 0;
    lan->nb_station = 0;
    lan->curs_routeur = 0;
    lan->curs_station = 0;
}

void recupere_config(LAN *lan, char * filename){
	FILE* file = fopen(filename,"r");
    char buffer[2048];
    unsigned int appareils;
    fgets(buffer,2048,file);
    while(fgets(buffer,2048,file)!=NULL){
        char string[2];
        string[0] = buffer[0];
        string[1] = '\0';
    	if(strcmp(string,"2") && strstr(buffer,":")){
    		ajoute_routeur(lan, {routeur}());
    	}
    	else if(strcmp(string,"1") && strstr(buffer,":")){
            //ajoute_station();
    	}
    }
    fclose(file);
}

void ajoute_routeur(LAN *lan, routeur rout){
    lan->routeurs[lan->curs_routeur] = rout;
    lan->curs_routeur+=1;
}
void ajoute_station(LAN *lan, station stat){

}