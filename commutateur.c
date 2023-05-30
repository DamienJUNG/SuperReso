#include "commutateur.h"

void affiche_commutateur(commutateur monCom){
    printf("### MAC ###\n");
    for(int i=0;i<6;i++){
        if(i==5){
            printf("%02x",monCom.mac[i]);
        }
        else{
            printf("%02x:",monCom.mac[i]);
        }
    }
    printf("\n");
}
void affiche_nbPorts(commutateur monCom){
    printf("NOMBRE DE PORTS : %d\n",monCom.nb_ports);
}
void affiche_priorite(commutateur monCom){
    printf("PRIORITE : %d\n",monCom.priorite);
}
void affiche_commutation(commutateur monCom){/*
    printf("######### TABLE DE COMMUTATION #########\n");
    for(int i=0;i<64;i++){
        printf("###### commutateur 1 ######\n");
        printf("### PORTS ###\n");
        for(int y=0;y<monCom.table[i].nb_ligne;y++){
            printf("%d",monCom.table[i].ports[y]);
        }
        printf("### MAC ###\n");
        for(int y=0;y<6;y++){
            printf("%x",monCom.table[i].mac[y]);
        }
        printf("\n");
    }*/
}


void affiche_tout_commutateur(commutateur monCom){
    printf("######### commutateur #########\n");
    affiche_commutateur(monCom);
    affiche_nbPorts(monCom);
    affiche_priorite(monCom);
    affiche_commutation(monCom);
}


