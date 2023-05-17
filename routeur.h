#include "commutation.h"
typedef struct routeur {
	byte mac[6];
	int nb_ports;
	int priorite;
	commutation[64] table;//table de commutation
}