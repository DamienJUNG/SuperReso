#include "commutation.h"
#include <stdio.h>
typedef struct commutateur {
	unsigned char mac[6];
	unsigned int nb_ports;
	unsigned int priorite;
	commutation table[64];//table de commutation
}commutateur;
void affiche_commutateur(commutateur monCom);
void affiche_nbPorts(commutateur monCom);
void affiche_priorite(commutateur monCom);
void affiche_commutation(commutateur monCom);
void affiche_tout_commutateur(commutateur monCom);