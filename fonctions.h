#ifndef FONCTIONS
#define FONCTIONS

    #include "constantes.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <time.h>
    #include <stdint.h>

    void damier_initialisation(damier *d);
    void manoury_initialisation(manoury*tabmanoury);
    void damier_affichage(damier d);
    void damier_affichage_2 (damier d);
    void deplacement(damier *d,int i_depart,int j_depart,int i_arrive,int j_arrive);
    void make_king(damier *d,int couleurPion,int i_arrive,int j_arrive);
   // int * mouvement_possible(damier d,int couleur);
    int*mouvement_possible(damier d,int couleur);
    void ajouter(int val,int*tab);
    int game_over(damier d);
    int verif_manger(char* buf);
    void affichage_gagnant(damier d);

    void pion_rafale (damier d,int couleur, int i, int j);

    int*choixoptimal(int*tab,int*tab2,damier d,int couleur);
    int nombredepas_blanc(int pion ,damier d);
    int nombredepas_noir(int pion ,damier d);
    damier copierdamier(damier d);
    void manger(damier d,int couleur ,int num,int i,int j,int i_arrive,int j_arrive);
    int *chercher_les_dames(damier d,int couleur);
    int*mouvement_possible_dame(damier d,int couleur,int*tab);
    int nombredepas_noir_dame(int num ,damier d);
    int nombredepas_blanc_dame(int num ,damier d);
    int* recupp_val(char *buffer);
    int find_num_a_manger(damier d,int debut,int fin);
    void detruire_damier(damier *d);
    char* tostring(int nbCapture,int *tab);

    /*fonctions pour le main*/
    int*mouvement_possible_final(damier d,int couleur);

    int size_tab(int *tab);
    void vider_buffer(char*buf);
    
    int choixdepas_blanc_dame(int num ,damier d);
    int choixdepaspion_blanc(int pion ,damier d);
    int*rafale(damier d,int couleur,int num);
    int choixdepaspion_noir(int pion ,damier d);
    int choixdepas_noir_dame(int num ,damier d);
    int droite_gauche_aleat(damier d,int num);

#endif
