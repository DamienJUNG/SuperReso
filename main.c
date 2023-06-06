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
	//show_devices(&lan);
	//afficher(lan.graphe);
	int rep=0;
	while(rep!=4){
		printf("1. Liste des équipements\n");
		printf("2. Structure du réseau\n");
		printf("3. Envoi de trame\n");
		printf("4. Quitter\n");
		scanf("%d",&rep);
		if(rep!=4){
			printf("\n################################\n################################\n################################\n\n");
			if(rep==1){
				printf("\t##############\n\t## Stations ##\n\t##############\n");
				show_stations(&lan);
				printf("\t##############\n\t## Switches ##\n\t##############\n");
				show_bridges(&lan);
			}
			else if(rep==2){
				show_network(&lan);
			}
			else if(rep==3){
				printf("Tables de commutations :\n");
				for (int i = 0; i < lan.nb_bridge; ++i)
				{
					printf("\t-- SWITCH %d --\n", i);
					print_commutation_table(lan.bridges[i]);
				}
				ask_frame(lan);
				printf("Tables de commutations :\n");
				for (int i = 0; i < lan.nb_bridge; ++i)
				{
					printf("\t-- SWITCH %d --\n", i);
					print_commutation_table(lan.bridges[i]);
				}
			}
			printf("################################\n################################\n################################\n\n");
		}
	}
	free_Lan(&lan);
	return 0;
}