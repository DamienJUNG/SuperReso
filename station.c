#include "station.h"

void affiche_mac_station(station maStation){
    printf("### MAC ###\n");
    for(int i=0;i<6;i++){
        printf("%x",maStation->mac[i]);
    }
    printf("\n",);
}
void affiche_ip_station(station maStation){
    printf("### IP ###\n");
    for(int i=0;i<4;i++){
        printf("%d",maStation->ip[i]);
    }
    printf("\n",);
}
void affiche_tout_station(station maStation){
    printf("######### STATION #########\n");
    affiche_ip_station(maStation);
    affiche_mac_station(maStation);

}
