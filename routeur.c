#include "routeur.h"

void afficheRouteur(routeur monRout){
    printf("### MAC ###");
    for(int i=0;i<6;i++){
        printf("%u",monRout->mac[i]);
    }
    printf("\n",);
}
void afficheNbPorts(routeur monRout){
    printf("NOMBRE DE PORTS : %d\n",monRout->nb_Ports);
}
void affichePriorite(routeur monRout){
    printf("PRIORITE : %d\n",monRout->priorite);
}
void afficheCommutation(routeur monRout){
    printf("######### TABLE DE COMMUTATION #########\n");
    for(int i=0;i<64;i++){
        printf("###### ROUTEUR 1 ######\n");
        printf("### PORTS ###\n");
        for(int y=0;y<monRout->table[i]->nb_ligne;y++){
            printf("%d",monRout->table[i]->ports[y]);
        }
        printf("### MAC ###\n");
        for(int y=0;y<6;y++){
            printf("%u",monRout->table[i]->mac[y]);
        }
        printf("\n");
    }
}


void afficheTout(routeur monRout){
    printf("######### ROUTEUR #########\n");
    afficheRouteur(monRout);
    afficheNbPorts(monRout);
    affichePriorite(monRout);
    afficheCommutation(monRout);

}
