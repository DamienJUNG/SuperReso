#include "LAN.h"
#include <unistd.h>


int main(int argc, char const *argv[])
{
	LAN lan;
	init_Lan(&lan);
	if(argc<2){
		get_config(&lan,"mylan_no_cycle.lan.txt");
	}
	else{
		get_config(&lan,argv[1]);
	}
	frame message;
	create_frame(&message,lan.stations[0].mac,lan.stations[1].mac,(uint8_t const*)"D'après W personne ne sait coder !!", strlen("D'après W personne ne sait coder..."));
	printf("La station 0 envoie un message à la station 1 :\n");
	sleep(2);
	transfert_frame(0+lan.nb_bridge,&lan,&message);
	create_frame(&message,lan.stations[1].mac,lan.stations[0].mac,(uint8_t const*)"Il a peut être raison...", strlen("Il a peut être raison..."));
	printf("Voyons comment la station 1 lui répond !\n\n");
	sleep(10);
	transfert_frame(1+lan.nb_bridge,&lan,&message);
	free_Lan(&lan);
	return 0;
}