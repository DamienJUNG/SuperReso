#include "LAN.h"

void recupere_config(LAN *lan, char * filename){
	FILE* file = fopen(rep[i]->d_name,"r");
    char buffer[2048];
    unsigned int routeurs = 0;
    unsigned int stations = 0;
    unsigned int nb_ligne = 0;
    unsigned int appareils;
    unsigned int ;
    fgets(buffer,2048,file);
    while(fgets(buffer,2048,file)!=NULL){
    	nb_ligne++;
    	if(strcmp(buffer[0],"2") && strstr(buffer,":")){
    		routeurs++;
    	}
    	else if(strcmp(buffer[0],"1") && strstr(buffer,":")){
    		stations++;
    	}
    }
    fseek(file, nb_ligne,SEEK_SET);
    if(nb_ligne>1){
    	lan->nb_routeur = routeurs;
		lan->nb_station = stations;
		fgets(buffer,2048,file);
		printf("%d\n",atoi(buffer));;

    }
    fclose(file);
}

void ajoute_routeur(LAN *lan, routeur rout){

}
void ajoute_stations(LAN *lan, stations stat){

}