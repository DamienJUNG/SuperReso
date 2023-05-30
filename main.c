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
	show_devices(&lan);
	free_Lan(&lan);
	return 0;
}