#include "commutation.h"
typedef struct routeur {
	unsigned char *mac;
	unsigned int nb_ports;
	unsigned int priorite;
	commutation table[64];//table de commutation
}routeur;
void affiche_routeur(routeur monRout);
void affiche_nbPorts(routeur monRout);
void affiche_priorite(routeur monRout);
void affiche_commutation(routeur monRout);
void affiche_tout_routeur(routeur monRout);