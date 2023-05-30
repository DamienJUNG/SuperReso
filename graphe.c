#include "graphe.h"
void init_graphe(graphe *g)
{
    // initialise les champs internes du graphe g
    // - pas de sommets, pas d'arêtes
    // - allocation d'un tableau d'arêtes de capacité initiale 8
    g->ordre = 0;
    g->nb_aretes = 0;
    g->aretes_capacite = 8;
    g->aretes = malloc(sizeof(arete) * g->aretes_capacite);
}

void free_graphe(graphe *g)
{
    // réinitialise les champs internes du graphe g
    g->ordre = 0;
    g->aretes_capacite = 0;
    g->nb_aretes = 0;
    // libère la mémoire du tableau d'arêtes
    free(g->aretes);
    g->aretes = NULL;
}

size_t ordre(graphe const *g)
{
    return g->ordre;
}

size_t nb_aretes(graphe const *g)
{
    return g->nb_aretes;
}

void ajouter_sommet(graphe *g)
{
    g->ordre++;
}

// une fonction locale "static arete swap_arete(arete a)" pourra être utile
// cette fonction retourne une nouvelle arête dont les sommets sont les même que l'arête reçue mais inversés
static arete swap_arete(arete a){
    // arete b;
    // b.s1 = a.s2;
    // b.s2 = a.s1;
    // return b;
    return (arete){a.s2, a.s1};
}

bool existe_arete(graphe const *g, arete a)
{
    // retourne true si l'arête a est contenue dans le graphe g, false sinon
    if(a.s1 > ordre(g) || a.s2 > ordre(g)){
        return false;
    }
    // /!\ l'arête (s1,s2) et l'arête (s2,s1) sont équivalentes
    if (a.s1 > a.s2){
        a = swap_arete(a);
    }
    for(int i=0;i<g->nb_aretes;i++){
        if((a.s1==g->aretes[i].s1 && a.s2==g->aretes[i].s2)){
            return true;
        }
    }
    return false;
}

bool ajouter_arete(graphe *g, arete a)
{
    // retourne true si l'arête a bien été ajoutée, false sinon
    if(a.s1>=ordre(g) || a.s2>=ordre(g))
        return false;
    if(a.s1==a.s2)
        return false;
    if(existe_arete(g,a))
        return false;
    
    if(g->nb_aretes == g->aretes_capacite){
        g->aretes = realloc(g->aretes,g->aretes_capacite * 2 * sizeof(arete));
        g->aretes_capacite *= 2;
    }
    if (a.s1 > a.s2){
        a = swap_arete(a);
    }

    g->aretes[nb_aretes(g)] = a;
    g->nb_aretes++;
    return true;
    // /!\ si la capacité actuelle du tableau d'arêtes n'est pas suffisante,
    // /!\ il faut le réallouer.
    // /!\ on peut par exemple doubler la capacité du tableau actuel.
}


size_t index_arete(graphe const *g, arete a)
{
    // retourne l'index de l'arête au sein du tableau d'arêtes de g si l'arête a existe dans g,
    if(a.s1>a.s2){
        a = swap_arete(a);
    }

    for(int i=0;i<g->nb_aretes;i++){
        if(a.s1==g->aretes[i].s1 && a.s2==g->aretes[i].s2){
            return i;
        }
    }
    // la valeur UNKNOWN_INDEX sinon
    return UNKNOWN_INDEX;
}

size_t sommets_adjacents(graphe const *g, sommet s, sommet sa[])
{
    int nb=0;
    // après s'être assuré que le sommet s existe dans g
    if(s>=ordre(g)){
        return nb;
    }
    // remplit le tableau sa avec les sommets adjacents de s dans g
    for(int i=0;i<g->nb_aretes;i++){
        if(g->aretes[i].s1==s){
            sa[nb] = g->aretes[i].s2;
            nb+=1;
        }
        else if(g->aretes[i].s2==s)
        {
            sa[nb] = g->aretes[i].s1;
            nb+=1;
        }
    }
    // et retourne le nombre de sommets ainsi stockés
    // (le tableau sa est supposé assez grand pour contenir les sommets adjacents)

    return nb;
}
