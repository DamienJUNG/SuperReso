typedef struct routeur {
	byte mac[6];
	int nb_Ports;
	int priorite;
	commut[60] tableCommut;//table de commutation
}