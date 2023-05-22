#include "LAN.h"
int main(int argc, char const *argv[])
{
	LAN lan;
	init_Lan(&lan);
	recupere_config(&lan,argv[1]);
	free_Lan(&lan);
	return 0;
}