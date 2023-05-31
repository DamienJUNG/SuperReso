#include "LAN.h"
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
	printf("Coucou\n");
	show_devices(&lan);
	afficher(lan.graphe);

	/*sommet source;
	sommet destination;

	printf("Entrez le numéro de la station source station :\n");
	scanf("%ld",&source);
	printf("Entrez le numéro de la station de destination station :\n");
	scanf("%ld",&destination);*/

	printf("nb aretes: %ld\n",lan.graphe->nb_aretes);

	frame message;
	char const* data = "coucou";
	create_frame(&message,lan.stations[lan.devices[7].number].mac,lan.stations[lan.devices[8].number].mac,(uint8_t const*)data, strlen(data));
	transfert_frame(7,&lan,&message);
	free_Lan(&lan);
	return 0;
}