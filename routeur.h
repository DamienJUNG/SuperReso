#include "commutation.h"
typedef struct routeur {
	byte mac[6];
	int nb_ports;
	int priorite;
	commutation[64] table;//table de commutation
}
void affiche_routeur(routeur monRout);
void affiche_nbPorts(routeur monRout);
void affiche_priorite(routeur monRout);
void affiche_commutation(routeur monRout);
void affiche_tout_routeur(routeur monRout);