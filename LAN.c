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
    lan->commutateurs=NULL;
    lan->stations=NULL;
    lan->appareils=NULL;
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
            commutateur comm;
            //Initailisation du découpage
            char *token = strtok(buffer,";");
            //Récupération de l'adresse mac
            token = strtok(NULL,";");
            char *mac = token; //On la stocke pour plus tard

            //Attribution du nombre de ports et de la priorité
            token = strtok(NULL,";");
            comm.nb_ports = atoi(token);
            token = strtok(NULL,";");
            comm.priorite = atoi(token);

            //Construction de l'adresse mac
            construit_mac(mac,comm.mac);

            ajoute_commutateur(lan, comm);
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
            construit_ip(token,stat.ip);
            construit_mac(mac,stat.mac);
            ajoute_station(lan, stat);
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

void construit_mac(char* token,unsigned char* mac){
    char *champ = strtok(token,":");
    for(int i=0;i<6;i++){
        mac[i] = converti_champ(champ);
        champ = strtok(NULL,":");
    }
}
unsigned int converti_champ(char* champ){
    int i=0;
    int hex=0;
    int taille = strlen(champ);
    while(champ[i]!='\0'){
        if(champ[i]>=48 && champ[i]<=57){
            hex+=(champ[i]-48) * puissance(16,(taille-i));
        }
        else if (champ[i]>=65 && champ[i]<=90){
            hex+= (champ[i]-55) * puissance(16,(taille-i));
        }
        else if(champ[i]>=97 && champ[i]<=122){
            hex+=(champ[i]-87) * puissance(16,(taille-i));
        }
        i++;
    }
    return hex;
}
int puissance(int nb, int expo){
    int res = 1;
    for(int i=1;i<expo;i++){
        res*=nb;
    }
    return res;
}

void construit_ip(char* token, unsigned char* ip){
    char *champ = strtok(token,".");
    for (int i = 0; i < 4; ++i)
    {
        ip[i]=atoi(champ);
        champ = strtok(NULL,".");
    }
}