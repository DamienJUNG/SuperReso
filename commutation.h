typedef struct commutation {
    unsigned int priorite;
    unsigned char mac[6]; // adresse des switch 
    unsigned int nb_ligne;
    unsigned int ports;
}commutation;