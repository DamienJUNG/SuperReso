#include "routeur.h"

void affiche_routeur(routeur monRout){
    printf("### MAC ###\n");
    for(int i=0;i<6;i++){
        printf("%x",monRout->mac[i]);
    }
    printf("\n",);
}
void affiche_nbPorts(routeur monRout){
    printf("NOMBRE DE PORTS : %d\n",monRout->nb_Ports);
}
void affiche_priorite(routeur monRout){
    printf("PRIORITE : %d\n",monRout->priorite);
}
void affiche_commutation(routeur monRout){
    printf("######### TABLE DE COMMUTATION #########\n");
    for(int i=0;i<64;i++){
        printf("###### ROUTEUR 1 ######\n");
        printf("### PORTS ###\n");
        for(int y=0;y<monRout->table[i]->nb_ligne;y++){
            printf("%d",monRout->table[i]->ports[y]);
        }
        printf("### MAC ###\n");
        for(int y=0;y<6;y++){
            printf("%x",monRout->table[i]->mac[y]);
        }
        printf("\n");
    }
}


void affiche_tout_routeur(routeur monRout){
    printf("######### ROUTEUR #########\n");
    afficheRouteur(monRout);
    afficheNbPorts(monRout);
    affichePriorite(monRout);
    afficheCommutation(monRout);

}
