#include "commutation.h"
typedef struct routeur {
	byte mac[6];
	int nb_Ports;
	int priorite;
	commutation[64] tableCommut;//table de commutation
}