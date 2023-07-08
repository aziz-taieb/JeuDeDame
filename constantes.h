#ifndef CONSTANTES
#define CONSTANTES

    # define PION_BLANC 1
    # define DAME_BLANC -1
    # define PION_NOIR 2
    # define DAME_NOIR -2
    # define CASE_VIDE 0
    # define CASE_INTERDITE -99
    # define NOMBRE_PION 20
    # define TAILLE_DAMIER 10
    # define FIN_DE_PARTIE 1
    //# define HUMAIN 0
    //# define CPU 1
    typedef struct
    {
       int i,j;
    }manoury;

    typedef struct
    {
        int numero_case;
        int etat_case;
    }case_damier;

    typedef struct
    {
        case_damier **tab;
        int nb_restant_blanc ;
        int nb_restant_noir ;
        int compteur_de_coup;
        manoury tabmanoury[51];
    }damier;

#endif
