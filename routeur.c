#include "routeur.h"

void afficheRouteur(routeur monRout){
    
    for(int i=0;i<6;i++){
        printf("MAC : %u",monRout->mac[i]);
    }
}
void afficheNbPorts(routeur monRout){
    printf("NOMBRE DE PORTS : %d",monRout->nb_Ports);
}
void affichePriorite(routeur monRout){
    printf("PRIORITE : %d",monRout->priorite);
}
void afficheCommunation(routeur monRout){
    for(int i=0;i<64;i++){
        for(){
            
        }
    }
}


void afficheTout(routeur monRout){

}
