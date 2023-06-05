#include "LAN.h"

void ask_frame(LAN lan){
	sommet source;
	sommet destination;

	printf("Entrez le numéro de la station source station :\n");
	scanf("%ld",&source);
	printf("Entrez le numéro de la station de destination station :\n");
	scanf("%ld",&destination);
	printf("\n");

	frame message;
	char const* data = "coucou";
	if(destination==-1){
		create_frame(&message,lan.stations[source].mac,BROADCAST,(uint8_t const*)data, strlen(data));
	}
	else{
		create_frame(&message,lan.stations[source].mac,lan.stations[destination].mac,(uint8_t const*)data, strlen(data));
	}
	transfert_frame(source+lan.nb_bridge,&lan,&message);
}

int main(int argc, char const *argv[])
{
	if (argc<2)
	{
		printf("Vous devez spécifier un fichier de configuration\n");
		return 0;
	}
	LAN lan;
	init_Lan(&lan);
	get_config(&lan,argv[1]);
	//show_devices(&lan);
	//afficher(lan.graphe);
	int rep=0;
	while(rep!=4){
		printf("1. Consulter la liste des stations\n");
		printf("2. Consulter la liste des switch\n");
		printf("3. Faire une simulation d'envoie de trame\n");
		printf("4. Quitter\n");
		scanf("%d",&rep);
		if(rep!=4){
			printf("################################\n################################\n################################\n\n");
			if(rep==1){
				show_stations(&lan);
			}
			else if(rep==2){
				show_bridges(&lan);
			}
			else if(rep==3){
				ask_frame(lan);
			}
			printf("################################\n################################\n################################\n\n");
		}
	}
	free_Lan(&lan);
	return 0;
}