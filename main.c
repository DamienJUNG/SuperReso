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
	recupere_config(&lan,argv[1]);
	for (int i = 0; i < lan.nb_commutateur; ++i)
	{
		affiche_tout_commutateur(lan.commutateurs[i]);
		printf("\n");
	}
	for (int i = 0; i < lan.nb_station; ++i)
	{
		affiche_tout_station(lan.stations[i]);
		printf("\n");
	}
	free_Lan(&lan);
	return 0;
}