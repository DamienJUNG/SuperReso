#include "station.h"
void affiche_mac_station(station ma_station){
    printf("### MAC ###\n");
    for(int i=0;i<6;i++){
        if(i==5){
            printf("%02x",ma_station.mac[i]);
        }
        else{
            printf("%02x:",ma_station.mac[i]);
        }
    }
    printf("\n");
}
void affiche_ip_station(station ma_station){
    printf("### IP ###\n");
    for(int i=0;i<4;i++){
        if (i==3){
            printf("%d",ma_station.ip[i]);
        }
        else{
            printf("%d.",ma_station.ip[i]);
        }
    }
    printf("\n");
}
void affiche_tout_station(station ma_station){
    printf("######### STATION #########\n");
    affiche_ip_station(ma_station);
    affiche_mac_station(ma_station);

}
