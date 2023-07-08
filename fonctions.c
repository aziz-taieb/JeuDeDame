#include "fonctions.h"

/***********************************************************************/
/***********************PARTIE GRAPHIQUE *******************************/

int var=0;
/*
Initialise le damier de départ avec les 20 pions noirs et les 20 pions blanc avec la notation manoury
*/
void damier_initialisation(damier *d){
    manoury_initialisation(d->tabmanoury);
    int n=1;
     d->tab=(case_damier **) malloc(sizeof(case_damier*)*TAILLE_DAMIER);
    for (int p=0;p<TAILLE_DAMIER;p++){
        d->tab[p]=(case_damier *) malloc(sizeof(case_damier)*TAILLE_DAMIER);
    }

    d->nb_restant_blanc=NOMBRE_PION;
    d->nb_restant_noir=NOMBRE_PION;
    d->compteur_de_coup=0;

    /*Initialisation des numéros de cases*/
    for(int i=0;i<TAILLE_DAMIER;i++){

        for(int j=0;j<TAILLE_DAMIER;j++){

            if((i % 2) == 0){
                if((j % 2) != 0){
                     d->tab[i][j].numero_case=n++;

                }
            }
            else{

                if((j % 2) == 0){
                    d->tab[i][j].numero_case=n++;
                }

            }
        }
    }

/* Initialisation des cases des pions noirs*/
    for(int e=0;e<4;e++){
        for(int j=0;j<TAILLE_DAMIER;j++){
            if( (d->tab[e][j].numero_case)!=0 ){

                d->tab[e][j].etat_case=PION_NOIR;
                }
        }
    }

/*Initialisation des cases des pions blancs*/
    for(int q=6;q<TAILLE_DAMIER;q++){
        for(int j=0;j<TAILLE_DAMIER;j++){
            if( (d->tab[q][j].numero_case)!=0 ){

                d->tab[q][j].etat_case=PION_BLANC;
                }
        }
    }
/*Initialisation des cases interdites*/
    for(int z1=0;z1<TAILLE_DAMIER;z1++){
        for(int z2=0;z2<TAILLE_DAMIER;z2++){
            if( (d->tab[z1][z2].numero_case)==0 ){

                d->tab[z1][z2].etat_case=CASE_INTERDITE;
                }
        }
    }
}

/*
Affiche le damier avec la notation manoury
*/
void damier_affichage_2 (damier d)
{
  int n=1;
    printf("\n 0   1   2   3   4   5   6   7   8   9  ") ;
    for(int i=0;i<TAILLE_DAMIER;i++)
    {
        printf("\n――――――――――――――――――――――――――――――――――――――――\n");
        for(int j=0;j<TAILLE_DAMIER;j++)
        {
          if(i%2 != 0)
          {
            if((j % 2) != 0)
            {
                 printf(" _ |");
            }
            else
            {
              printf(" %d |", n++);
            }
          }
          else
          {
            if((j % 2) == 0)
            {
                printf(" _ |");
            }
            else
            {
              printf(" %d |", n++);
            }
          }
        }
      }
    printf("\n―――――――――――――――――――――――――――――――――――――――――\n");
}

/*
Initialise avec la notation manoury le tableau de cases passé en argument
*/
void manoury_initialisation(manoury*tabmanoury){
  int cmp=0;
  cmp++;

  for(int i=0;i<10;i++){
    if((i % 2)==0)
    {
        for(int j=1;j<10;j+=2)
        {
            tabmanoury[cmp].i=i;
            tabmanoury[cmp].j=j;
            cmp++;
        }
    }
    else
    {
        for(int j=0;j<10;j+=2)
        {
            tabmanoury[cmp].i=i;
            tabmanoury[cmp].j=j;
            cmp++;
        }
    }
  }
}

/*
Affiche le damier avec les pions blancs et noirs
*/
void damier_affichage(damier d)
  {
   printf("\n      0   1   2   3   4   5   6   7   8   9  ") ;
    for(int i=0;i<TAILLE_DAMIER;i++){
        printf("\n    ―――――――――――――――――――――――――――――――――――――――――\n");
        printf("%d   ",i);
        for(int j=0;j<TAILLE_DAMIER;j++){

            switch(d.tab[i][j].etat_case) {
                case PION_BLANC :
                    printf("| B ") ;
                    break ;
                case PION_NOIR :
                    printf("| N ") ;
                    break ;
                case DAME_NOIR :
                    printf("|[N]") ;
                    break ;
                case DAME_BLANC :
                    printf("|[B]") ;
                    break ;
                default :
                    printf("|   ") ;
                    break ;
                }


        }
         printf("|   ") ;
    }
    printf("\n    ―――――――――――――――――――――――――――――――――――――――――\n");
}

/*
Déplace le damier de la position (i_depart, j_depart) à la position (i_arrive, j_arrive) si cela est possible
*/
void deplacement(damier *d,int i_depart,int j_depart,int i_arrive,int j_arrive){

  /* si la case de départ est hors du damier*/
    if(i_depart<0 ||i_depart>9 || j_depart<0 || j_depart>9){
        printf("\ncase de depart hors champ du damier\n");
        return ;
    }

/*si la position de départ ne contient pas de pion */
    if(d->tab[i_depart][j_depart].etat_case==CASE_VIDE){
        printf("\ncase vide\n");
        return ;
    }

/*si la position de départ est une case interdite*/
    if(d->tab[i_depart][j_depart].etat_case==CASE_INTERDITE){
        printf("\ncase de depart INTERDITE\n");
        return ;
    }

/* si la case d'arrivée est hors du damier*/
    if(i_arrive<0 || i_arrive>9 || j_arrive<0 || j_arrive>9){
        printf("\ncase d'arrivée hors champ du damier\n");
        return ;
     }

/*si la position d'arrivée est une case interdite*/
     if(d->tab[i_arrive][j_arrive].etat_case==CASE_INTERDITE){
        printf("\ncase d'arrivée INTERDITE\n");
        return ;
     }

/* si la case d'arrivée contient déja un pion*/
     if(d->tab[i_arrive][j_arrive].etat_case!=CASE_VIDE){
        printf("\ncase non vide\n");
        return ;
    }
    int a=d->tab[i_depart][j_depart].etat_case;
    d->tab[i_arrive][j_arrive].etat_case = a;
    d->tab[i_depart][j_depart].etat_case = CASE_VIDE;
}

/*
Si dans le damier la couleur indiquer en argument peut manger alors la fonction retourne le tableau des pions qui peuvent manger
Sinon si aucun pion ne peut manger on renvoie le tableau des pions qui peuvent se déplacer
*/
int*mouvement_possible(damier d,int couleur){
  int i=0;
  var=0;
  /*Initialisation du tableau des pions qui peuvent manger*/
  int*tabmv=calloc(20,sizeof(int));

  /*Initialisation du tableau des pions qui peuvent se déplacer*/
  int*tabmg=calloc(20,sizeof(int));

       for(int i=0;i<TAILLE_DAMIER;i++){
    for(int j=0;j<TAILLE_DAMIER;j++){
      if(couleur==PION_NOIR && d.tab[i][j].etat_case==PION_NOIR){
        if(i-1>=0 && j-1 >0 &&(d.tab[i-1][j-1].etat_case==1 ||d.tab[i-1][j-1].etat_case==-1)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0
        ||i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==1 ||d.tab[i-1][j+1].etat_case==-1)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0
        ||i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==1 ||d.tab[i+1][j-1].etat_case==-1)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0
        ||i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==1||d.tab[i+1][j+1].etat_case==-1)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0){
          /* si le pion de coordonnées (i,j) vérifie ses conditions alors elle peut manger*/
          ajouter(d.tab[i][j].numero_case ,tabmg);
          var=1;
          }
          }

          if(couleur==PION_BLANC && d.tab[i][j].etat_case==PION_BLANC){
        if(i-1>=0 && j-1 >=0 &&(d.tab[i-1][j-1].etat_case==2 ||d.tab[i-1][j-1].etat_case==-2)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0
        ||i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==2 ||d.tab[i-1][j+1].etat_case==-2)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0
        ||i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==2 ||d.tab[i+1][j-1].etat_case==-2)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0
        ||i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==2 ||d.tab[i+1][j+1].etat_case==-2)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0){
         ajouter(d.tab[i][j].numero_case ,tabmg);
          var=1;
        }}
        /* si var=0 alors le pion ne peut pas manger et on vérifie si il peut se déplacer afin de l'ajouter au tableau tabmv*/
        if(var==0 && couleur ==PION_NOIR){
        if((i+1<10 && j-1 >=0 &&d.tab[i+1][j-1].etat_case==0 && d.tab[i][j].etat_case==couleur)
        || (i+1<10 && j+1 <10 &&d.tab[i+1][j+1].etat_case==0 && d.tab[i][j].etat_case==couleur)){

        ajouter(d.tab[i][j].numero_case ,tabmv);
        }
      }

      if(var==0 && couleur ==PION_BLANC){
        if((i-1>=0 && j-1 >=0 &&d.tab[i-1][j-1].etat_case==0 && d.tab[i][j].etat_case==PION_BLANC)
        || (i-1>=0 && j+1 <10 &&d.tab[i-1][j+1].etat_case==0 && d.tab[i][j].etat_case==PION_BLANC)){

        ajouter(d.tab[i][j].numero_case ,tabmv);
        }
      }

      }
    }

    /*Libération de la mémoire occupée par les deux tableaux*/
    if(var==1){
      free(tabmv);
      return tabmg;
    }else{
      free(tabmg);
      return tabmv;
    }
}

/*
Change l'état du pion de couleur couleurPion qui est devenu une dame
C'est-à-dire si le pion blanc est arrivée dans une coordonnée (0,j_arrive) ou si le pion noir est arrivée à (9, j_arrive)
*/
void make_king(damier *d,int couleurPion,int i_arrive,int j_arrive){

  if(couleurPion==PION_BLANC){
    if(i_arrive==0){
            d->tab[i_arrive][j_arrive].etat_case=DAME_BLANC;
        }
    }
   if(couleurPion==PION_NOIR){
   if(i_arrive==9){
            d->tab[i_arrive][j_arrive].etat_case=DAME_NOIR;
        }
    }
    return;
}


/*
Prend une chaine de caractère en argument et renvoie 1 si il s'agit d'un déplacement
Renvoie 0 si il mange une case
a-b est le déplacement de a vers b
axb : une case est mangé entre a et b
*/

int verif_manger(char* buf){

    if(buf[1]=='-' || buf[2]=='-' ){

        return 1;}

    if(buf[1]=='x' || buf[2]=='x' ){

        return 0;}
}

/*
Ajoute la valeur indiquer en argument à la fin du tableau
*/
void ajouter(int val,int*tab){
  int i=0;
 while(tab[i]!=0){
    i++;
 }
  tab[i]=val;
}

/* Met fin à la partie*/
int game_over(damier d){

  if( d.compteur_de_coup>=50 || d.nb_restant_blanc==0 || d.nb_restant_noir==0)
    return FIN_DE_PARTIE;
  else
    return 0;
}

/*Affiche la couleur gagnante de la partie*/
void affichage_gagnant(damier d){

  if(d.nb_restant_blanc==0){
  printf("les noirs ont gagnés\nSi vous etes serveur PERDU\n");

  }else{

    if(d.nb_restant_noir==0){
        printf("les blancs ont gagnés\nSi vous etes client PERDU\n");
    }else {
              if(d.compteur_de_coup==50){
                  printf("EGALITE\n");}
              else{
                printf("INTERUPTION\n");
              }
        }
    }
}

/*********************************************************************************/
/**************************************PARTIE IA ********************************/

/*
Renvoie un tableau contenant toutes les dames de la couleur indiquée en argument
*/
int *chercher_les_dames(damier d,int couleur){
  int*tabdedame=calloc(20,sizeof(int));
  for(int i=0;i<TAILLE_DAMIER;i++){
    for(int j=0;j<TAILLE_DAMIER;j++){
      if(d.tab[i][j].etat_case==couleur){
        ajouter(d.tab[i][j].numero_case ,tabdedame);
      }
    }
  }
  return tabdedame;
}

/*
Si dans le damier les dames de la couleur indiquer en argument peuvent manger alors la fonction retourne le tableau des dames qui peuvent manger
Sinon si aucune dame de cette couleur ne peut manger on renvoie le tableau des dames qui peuvent se déplacer
*/
int*mouvement_possible_dame(damier d,int couleur,int*tab){
  int *tab_mv=calloc(20,sizeof(int));
  int *tab_mg=calloc(20,sizeof(int));
  int l=0;
  int var0,var1,var2,var3,var4;
  int i,j;

  while(tab[l]!=0){
    i=d.tabmanoury[tab[l]].i;
    j=d.tabmanoury[tab[l]].j;
    var0=0;
    var1=0;
    var2=0;
    var3=0;
    var4=0;
    for(int k=1;k<10;k++){
      if(((i-1>=0 && j-1 >=0 &&d.tab[i-1][j-1].etat_case==0 && d.tab[i][j].etat_case==couleur)
      || (i+1<10 && j+1 <10 &&d.tab[i+1][j+1].etat_case==0 && d.tab[i][j].etat_case==couleur)
      || (i-1>=0 && j+1 <10 &&d.tab[i-1][j+1].etat_case==0 && d.tab[i][j].etat_case==couleur)
      || (i+1<10 && j-1 >=0 &&d.tab[i+1][j-1].etat_case==0 && d.tab[i][j].etat_case==couleur))&&var==0&&var0==0){
        ajouter(tab[l],tab_mv);
        var0=1;
      }
      if(couleur==DAME_NOIR){
          if(var1==0&&(i-k>0 && j-k>0 &&(d.tab[i-k][j-k].etat_case==1 ||d.tab[i-k][j-k].etat_case==-1)&& i-k-1>=0 && j-k-1 >=0 &&d.tab[i-k-1][j-k-1].etat_case==0)){
          ajouter(tab[l],tab_mg);
          var=1;
          break;
        }else{
          if(i-k>=0 && j-k>=0 &&(d.tab[i-k][j-k].etat_case==2 ||d.tab[i-k][j-k].etat_case==-2)){
            var1=1;
          }
        }
          if(var2==0&&(i-k>0 && j+k <9 &&(d.tab[i-k][j+k].etat_case==1 ||d.tab[i-k][j+k].etat_case==-1)&& i-k-1>=0 && j+k+1 <10 &&d.tab[i-k-1][j+k+1].etat_case==0)){
            ajouter(tab[l],tab_mg);
            var=1;
            break;
          }else{
           if(i-k>=0 && j+k<10 &&(d.tab[i-k][j+k].etat_case==2 ||d.tab[i-k][j+k].etat_case==-2)){

              var2=1;
            }
          }
          if(var3==0&&(i+k<9 && j-k >0 &&(d.tab[i+k][j-k].etat_case==1 ||d.tab[i+k][j-k].etat_case==-1)&& i+k+1<10 && j-k-1 >=0 &&d.tab[i+k+1][j-k-1].etat_case==0)){
            ajouter(tab[l],tab_mg);
            var=1;
            break;
          }else{
            if(i+k<10 && j-k>=0 &&(d.tab[i+k][j-k].etat_case==2 ||d.tab[i+k][j-k].etat_case==-2)){
              var3=1;
              }
            }
          if(var4==0&&(i+k<9 && j+k <9 &&(d.tab[i+k][j+k].etat_case==1 ||d.tab[i+k][j+k].etat_case==-1)&& i+k+1>=0 && j+k+1 <10 &&d.tab[i+k+1][j+k+1].etat_case==0)){
            ajouter(tab[l],tab_mg);
            var=1;
            break;
          }else{
            if(i+k<10 && j+k<10 &&(d.tab[i+k][j+k].etat_case==2 ||d.tab[i+k][j+k].etat_case==-2)){
              var4=1;
            }
          }
        }
        if(couleur==DAME_BLANC){
            if(var1==0&&(i-k>0 && j-k>0 &&(d.tab[i-k][j-k].etat_case==2 ||d.tab[i-k][j-k].etat_case==-2)&& i-k-1>=0 && j-k-1 >=0 &&d.tab[i-k-1][j-k-1].etat_case==0)){
            ajouter(tab[l],tab_mg);
            var=1;
            break;
          }else{
            if(i-k>=0 && j-k>=0 &&(d.tab[i-k][j-k].etat_case==1 ||d.tab[i-k][j-k].etat_case==-1)){
              var1=1;
            }
          }
            if(var2==0&&(i-k>0 && j+k <9 &&(d.tab[i-k][j+k].etat_case==2 ||d.tab[i-k][j+k].etat_case==-2)&& i-k-1>=0 && j+k+1 <10 &&d.tab[i-k-1][j+k+1].etat_case==0)){
              ajouter(tab[l],tab_mg);
              var=1;
              break;
            }else{
              if(i-k>=0 && j+k<10 &&(d.tab[i-k][j+k].etat_case==1 ||d.tab[i-k][j+k].etat_case==-1)){
                var2=1;
              }
            }
            if(var3==0&&(i+k<9 && j-k >0 &&(d.tab[i+k][j-k].etat_case==2 ||d.tab[i+k][j-k].etat_case==-2)&& i+k+1<10 && j-k-1 >=0 &&d.tab[i+k+1][j-k-1].etat_case==0)){
              ajouter(tab[l],tab_mg);
              var=1;
              break;
            }else{
              if(i+k<10 && j-k>=0 &&(d.tab[i+k][j-k].etat_case==1 ||d.tab[i+k][j-k].etat_case==-1)){
                var3=1;
                }
              }
            if(var4==0&&(i+k<9 && j+k <9 &&(d.tab[i+k][j+k].etat_case==2 ||d.tab[i+k][j+k].etat_case==-2)&& i+k+1<10 && j+k+1 <10 &&d.tab[i+k+1][j+k+1].etat_case==0)){
              ajouter(tab[l],tab_mg);
              var=1;
              break;
            }else{
              if(i+k<10 && j+k<10 &&(d.tab[i+k][j+k].etat_case==1 ||d.tab[i+k][j+k].etat_case==-1)){
                var4=1;
              }
            }
          }
  }
  l++;
 }
 free(tab);
 if(var==1){

  free(tab_mv);
  return tab_mg;
 }else{

  free(tab_mg);
  return tab_mv;
 }
}

/*
tab : tableau de pions qui peuvent manger
tab2: tableau de dame qui peuvent manger
La fonction renvoie un tableau de choix maximal de pions en comparant le maximum du nombre de pas pour chacun des pions des deux tableaux
passée en argument
*/
int*choixoptimal(int*tab,int*tab2,damier d,int couleur){
  int i=0;
  int max=0;
  int*choix=calloc(21,sizeof(int));
  if(couleur==2){
    while(tab[i]!=0){
        if(nombredepas_noir(tab[i],d)>=max)
            max=nombredepas_noir(tab[i],d);
            i++;
        }
    i=0;
    while(tab2[i]!=0){
        if(nombredepas_noir_dame(tab2[i],d)>=max)
            max=nombredepas_noir_dame(tab2[i],d);
            i++;
        }
    i=0;
    while(tab[i]!=0){
        if(nombredepas_noir(tab[i],d)==max)
            ajouter(tab[i],choix);
            i++;
    }
    i=0;
    while(tab2[i]!=0){
        if(nombredepas_noir_dame(tab2[i],d)==max)
            ajouter(tab2[i],choix);
            i++;
    }
  }
  if(couleur==1){
    while(tab[i]!=0){
        if(nombredepas_blanc(tab[i],d)>=max)
            max=nombredepas_blanc(tab[i],d);
            i++;
        }
    i=0;
    while(tab2[i]!=0){
        if(nombredepas_blanc_dame(tab2[i],d)>=max)
            max=nombredepas_blanc_dame(tab2[i],d);
            i++;
         }
    i=0;
    while(tab[i]!=0){
        if(nombredepas_blanc(tab[i],d)==max)
            ajouter(tab[i],choix);
            i++;
    }
    i=0;
    while(tab2[i]!=0){
        if(nombredepas_blanc_dame(tab2[i],d)==max)
            ajouter(tab2[i],choix);
            i++;
    }
  }
  return choix;
}

/*
Avec le pion indiquer en argument, on cherche le nombre maximal de pion qu'il peut manger de manière récursive
On a 4 possibilités au maximum à chaque appel
On copie un autre damier afin d'effectuer les tests dessus et garder le damier initiale
On renvoie le nombre de pas maximal effectué du pion noir
*/
int nombredepas_noir(int pion ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int i=d.tabmanoury[pion].i;
  int j=d.tabmanoury[pion].j;
  if(i-1>=0 && j-1 >=0 &&(d.tab[i-1][j-1].etat_case==PION_BLANC||d.tab[i-1][j-1].etat_case==DAME_BLANC)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0)
  {
    /* manger le pion en haut à gauche*/
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion ,i-1,j-1,i-2,j-2);
    max1=nombredepas_noir(d.tab[i-2][j-2].numero_case,d1)+1;
  }
  if(i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==PION_BLANC ||d.tab[i-1][j+1].etat_case==DAME_BLANC)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0)
  {
    /* manger le pion en haut à droite*/
    damier d1=copierdamier(d);
    manger(d1, PION_NOIR ,pion ,i-1,j+1,i-2,j+2);
    max2=nombredepas_noir(d.tab[i-2][j+2].numero_case,d1)+1;
  }
  if(i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==PION_BLANC ||d.tab[i+1][j-1].etat_case==DAME_BLANC)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0)
  {
    /* manger le pion en bas à gauche*/
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion,i+1,j-1 ,i+2,j-2);
    max3=nombredepas_noir(d.tab[i+2][j-2].numero_case,d1)+1;
  }
  if(i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==PION_BLANC||d.tab[i+1][j+1].etat_case==DAME_BLANC)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0)
  {
    /* manger le pion en bas à droite*/
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion,i+1,j+1,i+2,j+2);
    max4=nombredepas_noir(d.tab[i+2][j+2].numero_case,d1)+1;
  }

  /* Comparaison de touts les maximums*/
  if(max1>=max2&&max1>=max3&&max1>=max4)return max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)return max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)return max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)return max4;
}

/*
Similaire à la fonction nombredepas_noir
*/
int nombredepas_blanc(int pion ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int i=d.tabmanoury[pion].i;
  int j=d.tabmanoury[pion].j;
  if(i-1>=0 && j-1 >=0 &&(d.tab[i-1][j-1].etat_case==PION_NOIR||d.tab[i-1][j-1].etat_case==DAME_NOIR)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion ,i-1,j-1,i-2,j-2);
    max1=nombredepas_blanc(d.tab[i-2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==PION_NOIR ||d.tab[i-1][j+1].etat_case==DAME_NOIR)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, PION_BLANC ,pion ,i-1,j+1,i-2,j+2);
    max2=nombredepas_blanc(d.tab[i-2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==PION_NOIR ||d.tab[i+1][j-1].etat_case==DAME_NOIR)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion,i+1,j-1 ,i+2,j-2);
    max3=nombredepas_blanc(d.tab[i+2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==PION_NOIR||d.tab[i+1][j+1].etat_case==DAME_NOIR)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion,i+1,j+1,i+2,j+2);
    max4=nombredepas_blanc(d.tab[i+2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }


  if(max1>=max2&&max1>=max3&&max1>=max4)return max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)return max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)return max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)return max4;
}

/*
Crée et renvoie un nouveau damier qui est la copie du damier passé en argument
*/
damier copierdamier(damier d){
  damier d1;
  damier_initialisation(&d1);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      d1.tab[i][j].numero_case= d.tab[i][j].numero_case;
      d1.tab[i][j].etat_case=d.tab[i][j].etat_case;
    }
  }
  return d1;
}

/*
Le pion de coordonnées (i1,j1) mange le pion de coordonnée (i,j) et se déplace aux coordonnées (i_arrive, j_arrive)
*/
void manger(damier d,int couleur ,int num,int i,int j,int i_arrive,int j_arrive){
  int i1=d.tabmanoury[num].i;
  int j1=d.tabmanoury[num].j;
  d.tab[i1][j1].etat_case=0;
  d.tab[i][j].etat_case=0;
  d.tab[i_arrive][j_arrive].etat_case=couleur;

}

/*
Destruction du damier
*/
void detruire_damier(damier *d){
    for (int p=0;p<TAILLE_DAMIER;p++){
        free(d->tab[p]);
    }
    free(d->tab);
}

/*
Prend un tableau et rend la chaîne de caractère a envoyé dans le réseau
*/

char* tostring(int nbCapture,int *tab){

    char *buffer;
    buffer=malloc(sizeof(char)*1024);
/*Si il y a 0 capture c'est un déplacement d'une case et met un "-" entre les 2 valeurs*/
    if(nbCapture ==0 ){
        const char* str1 = "-";
        char *num1,*num2;

        if (asprintf(&num1, "%d", tab[0]) == -1 || asprintf(&num2, "%d", tab[1]) == -1) {
            perror("asprintf");
        }
        else {
            strcat(strcpy(buffer, num1), str1);
            strcat(buffer, num2);
            printf("%s\n", buffer);
            free(num1);
            free(num2);
        }


    }
    /*Sinon il s'agit d'une prise et met un "x"*/
    else{

        const char* str2 = "x";
        char *num;

        if (asprintf(&num, "%d", tab[0]) == -1) {
                perror("asprintf");
        }
          strcpy(buffer, num);

        int i=0;
        while(i!=nbCapture){
             strcat(buffer, str2);

             if (asprintf(&num, "%d", tab[i+1]) == -1) {
                perror("asprintf");
                }else{
                strcat(buffer, num);
                printf("%s\n", buffer);
                }
               i++;
        }
         free(num);

    }
    return  buffer;
}

/*
Prend une chaîne de caractères en argument et met les éléments dans un tableau
*/
int* recupp_val(char *buffer){
     int *tab;

    const char *num;
    char *num1;
    char num2;

     num1=malloc(sizeof(char)*2);
     num1[0]='0';
     num1[1]='0';
     num2='0';
     tab=calloc(20,sizeof(int));
    int length = strlen( buffer );
    int j=0;
    int i=0;
    while( i<length) {
        if (isdigit( buffer[i] )) {

        if(isdigit( buffer[i+1] ) ){

            num1[0]= buffer[i];
            num1[1]= buffer[i+1];
            i+=3;

            tab[j]=atoi(num1);
            j++;
           }
           else{
            num2= buffer[i];
            i+=2;
            tab[j]=atoi(&num2);
            j++;

            }
    }

}
    return tab;
}

/*
Vide le tableau
*/
void vider_buffer(char*buf){
 for(int i=0;i<1024;i++){
   buf[i]='\0' ;
 }


}


/*
Avec la dame indiquer en argument, on cherche le nombre maximal de pion qu'elle peut manger de manière récursive
On a 4 possibilités au maximum à chaque appel
On copie un autre damier afin d'effectuer les tests dessus et garder le damier initiale
On renvoie le nombre de pas effectué du parcours le plus maximale de la dame
*/
int nombredepas_noir_dame(int num ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int i=d.tabmanoury[num].i;
  int j=d.tabmanoury[num].j;
  int l=1;
  while(i-l>=0 && j-l >=0&& d.tab[i-l][j-l].etat_case != PION_NOIR && d.tab[i-l][j-l].etat_case != DAME_NOIR)
  {
  if(d.tab[i-l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j-l].etat_case==PION_BLANC||d.tab[i-l][j-l].etat_case==DAME_BLANC)&& (i-l)-1>=0 && (j-l)-1>=0 && d.tab[(i-l)-1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num ,i-l,j-l,(i-l)-1,(j-l)-1);
    max1=nombredepas_noir_dame(d.tab[(i-l)-1][(j-l)-1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
  }
 }
 l=1;
  while((i-l)>=0 && (j+l) <10 && d.tab[i-l][j+l].etat_case != PION_NOIR && d.tab[i-l][j+l].etat_case != DAME_NOIR)
  {
  if(d.tab[i-l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j+l].etat_case==PION_BLANC ||d.tab[i-l][j+l].etat_case==DAME_BLANC)&& (i-l)-1>=0 && (j+l)+1<10 && d.tab[(i-l)-1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, DAME_NOIR ,num ,i-l,j+l,(i-l)-1,(j+l)+1);
    max2=nombredepas_noir_dame(d.tab[(i-l)-1][(j+l)+1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
 l=1;
  while((i+l)<10 && (j-l)>=0 && d.tab[i+l][j-l].etat_case != PION_NOIR && d.tab[i+l][j-l].etat_case != DAME_NOIR)
  {
  if(d.tab[i+l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j-l].etat_case==PION_BLANC ||d.tab[i+l][j-l].etat_case==DAME_BLANC)&& (i+l)+1<10 && (j-l)-1>=0 &&d.tab[(i+l)+1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num,i+l,j-l,(i+l)+1,(j-l)-1);
    max3=nombredepas_noir_dame(d.tab[(i+l)+1][(j-l)-1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
 l=1;
  while((i+l)<10 && (j+l)<10 && d.tab[i+l][j+l].etat_case != PION_NOIR && d.tab[i+l][j+l].etat_case != DAME_NOIR)
  {
  if(d.tab[i+l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j+l].etat_case==PION_BLANC||d.tab[i+l][j+l].etat_case==DAME_BLANC)&& (i+l)+1<10 && (j+l)+1<10 &&d.tab[(i+l)+1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num,i+l,j+l,(i+l)+1,(j+l)+1);
    max4=nombredepas_noir_dame(d.tab[(i+l)+1][(j+l)+1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }

  if(max1>=max2&&max1>=max3&&max1>=max4)return max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)return max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)return max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)return max4;
}

/*
Similaire à la fonction nombredepas_noir_dame
*/
int nombredepas_blanc_dame(int num ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int i=d.tabmanoury[num].i;
  int j=d.tabmanoury[num].j;
  int l=1;

  while((i-l)>=0 && (j-l)>=0 && d.tab[i-l][j-l].etat_case != PION_BLANC && d.tab[i-l][j-l].etat_case != DAME_BLANC)
  {
  if(d.tab[i-l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j-l].etat_case==PION_NOIR||d.tab[i-l][j-l].etat_case==DAME_NOIR)&& (i-l)-1>=0 && (j-l)-1>=0 && d.tab[(i-l)-1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num ,i-l,j-l,(i-l)-1,(j-l)-1);
    max1=nombredepas_blanc_dame(d.tab[(i-l)-1][(j-l)-1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i-l)>=0 && (j+l) <10 && d.tab[i-l][j+l].etat_case != PION_BLANC && d.tab[i-l][j+l].etat_case != DAME_BLANC)
  {
  if(d.tab[i-l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j+l].etat_case==PION_NOIR ||d.tab[i-l][j+l].etat_case==DAME_NOIR)&& (i-l)-1>=0 && (j+l)+1<10 && d.tab[(i-l)-1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, DAME_BLANC ,num ,i-l,j+l,(i-l)-1,(j+l)+1);
    max2=nombredepas_blanc_dame(d.tab[(i-l)-1][(j+l)+1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j-l)>=0 && d.tab[i+l][j-l].etat_case != PION_BLANC && d.tab[i+l][j-l].etat_case != DAME_BLANC)
  {
  if(d.tab[i+l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j-l].etat_case==PION_NOIR ||d.tab[i+l][j-l].etat_case==PION_NOIR)&& (i+l)+1<10 && (j-l)-1>=0 &&d.tab[(i+l)+1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num,i+l,j-l,(i+l)+1,(j-l)-1);
    max3=nombredepas_blanc_dame(d.tab[(i+l)+1][(j-l)-1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j+l)<10 && d.tab[i+l][j+l].etat_case != PION_BLANC && d.tab[i+l][j+l].etat_case != DAME_BLANC)
  {
  if(d.tab[i+l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j+l].etat_case==PION_NOIR||d.tab[i+l][j+l].etat_case==DAME_NOIR)&& (i+l)+1<10 && (j+l)+1<10 &&d.tab[(i+l)+1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num,i+l,j+l,(i+l)+1,(j+l)+1);
    max4=nombredepas_blanc_dame(d.tab[(i+l)+1][(j+l)+1].numero_case,d1)+1;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  if(max1>=max2&&max1>=max3&&max1>=max4)return max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)return max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)return max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)return max4;
}
int size_tab(int *tab){
  int i=0;
  while(tab[i]!=0)
    i++;

  return i;
}


/*fonctions pour le main*/
int*mouvement_possible_final(damier d,int couleur){
  int i=0;
  int p[1];
  p[0]=0;
  var=0;
  int*choix;
  if(couleur==1){
    int*tabdepion=mouvement_possible(d,couleur);
    if(var==0){
      int*tabdedame=mouvement_possible_dame(d,DAME_BLANC,chercher_les_dames(d,DAME_BLANC));
      if(var==1){
        free(tabdepion);
        choix=choixoptimal(p,tabdedame,d,1);
        free(tabdedame);
        printf("vous ne pouvez mangez que avec les dames : ");

        while(choix[i]!=0){
          printf("%d ",choix[i]);
          i++;
        }
        printf("\n");
        return choix;
      }else{
        choix=calloc(20,sizeof(int));
        printf("vous pouvez bouger avec : ");
        while(tabdedame[i]!=0){
          printf("%d ",tabdedame[i]);
          ajouter(tabdedame[i],choix);
          i++;
        }i=0;
        while(tabdepion[i]!=0){
          printf("%d ",tabdepion[i]);
          ajouter(tabdepion[i],choix);
          i++;
        }
        printf("\n");
        free(tabdepion);
        free(tabdedame);
        return choix;
      }
    }else{
      int*tabdedame=mouvement_possible_dame(d,DAME_BLANC,chercher_les_dames(d,DAME_BLANC));
      choix=choixoptimal(tabdepion,tabdedame,d,1);
      printf("vous pouvez manger avec : ");
      while(choix[i]!=0){
       printf("%d ",choix[i]);
        i++;
      }
      printf("\n");
      free(tabdepion);
      free(tabdedame);
      return choix;
    }
  }

  if(couleur==2){

    int*tabdepion=mouvement_possible(d,couleur);


     int y=0;

    if(var==0){


      int*tabdedame=mouvement_possible_dame(d,DAME_NOIR,chercher_les_dames(d,DAME_NOIR));
      if(var==1){
        free(tabdepion);
        choix=choixoptimal(p,tabdedame,d,2);
        free(tabdedame);
        printf("vous ne pouvez mangez que avec les dames : ");
        while(choix[i]!=0){
          printf("%d ",choix[i]);
          i++;
        }
        printf("\n");
        return choix;
      }else{
        choix=calloc(20,sizeof(int));
        printf("vous pouvez bouger avec : ");
        while(tabdedame[i]!=0){
          printf("%d ",tabdedame[i]);
          ajouter(tabdedame[i],choix);
          i++;
        }i=0;
        while(tabdepion[i]!=0){
          printf("%d ",tabdepion[i]);
          ajouter(tabdepion[i],choix);
          i++;
        }
        printf("\n");
        free(tabdepion);
        free(tabdedame);
        return choix;
      }
    }else{  printf("on rentre plutot ici ,? ");
      int*tabdedame=mouvement_possible_dame(d,DAME_NOIR,chercher_les_dames(d,DAME_NOIR));
      choix=choixoptimal(tabdepion,tabdedame,d,2);
      printf("vous pouvez manger avec : ");
      while(choix[i]!=0){
        printf("%d ",choix[i]);
        i++;
      }
      printf("\n");
      free(tabdepion);
      free(tabdedame);
      return choix;
    }
  }

}


/*
Retourner un numéro de case à manger
*/
int find_num_a_manger(damier d,int debut,int fin){

  int i_d,i_f,j_d,j_f;
  i_d=d.tabmanoury[debut].i;

  j_d=d.tabmanoury[debut].j;

  i_f=d.tabmanoury[fin].i;

  j_f=d.tabmanoury[fin].j;

  int l=1;

  while( abs(i_d-i_f) > l)
   {
    if(i_f<i_d){
      if(j_f<j_d){
        if(d.tab[i_d-l][j_d-l].etat_case!=CASE_VIDE && d.tab[i_d-l][j_d-l].etat_case!=CASE_INTERDITE )
       {
          return d.tab[i_d-l][j_d-l].numero_case;
       }

      }
      if(j_f>j_d){
        if(d.tab[i_d-l][j_d+l].etat_case!=CASE_VIDE && d.tab[i_d-l][j_d+l].etat_case!=CASE_INTERDITE )
       {
          return d.tab[i_d-l][j_d+l].numero_case;
       }

      }
    }

    if(i_f>i_d){
      if(j_f<j_d){
        if(d.tab[i_d+l][j_d-l].etat_case!=CASE_VIDE && d.tab[i_d+l][j_d-l].etat_case!=CASE_INTERDITE )
       {
          return d.tab[i_d+l][j_d-l].numero_case;
       }

      }
      if(j_f>j_d){
        if(d.tab[i_d+l][j_d+l].etat_case!=CASE_VIDE && d.tab[i_d+l][j_d+l].etat_case!=CASE_INTERDITE )
       {
          return d.tab[i_d+l][j_d+l].numero_case;
       }

      }
    }

    l++;
  }

}

/*
Stocke le nombre maximale de pas que peut faire le pion passé en argument
L'ajoute dans un tableau
Renvoie un numéro de case aléatoire de ce même tableau
*/

int choixdepaspion_blanc(int pion ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int max=0;
  int i=d.tabmanoury[pion].i;
  int j=d.tabmanoury[pion].j;
  if(i-1>=0 && j-1 >=0 &&(d.tab[i-1][j-1].etat_case==PION_NOIR||d.tab[i-1][j-1].etat_case==DAME_NOIR)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion ,i-1,j-1,i-2,j-2);
    max1=nombredepas_blanc(d.tab[i-2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==PION_NOIR ||d.tab[i-1][j+1].etat_case==DAME_NOIR)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, PION_BLANC ,pion ,i-1,j+1,i-2,j+2);
    max2=nombredepas_blanc(d.tab[i-2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==PION_NOIR ||d.tab[i+1][j-1].etat_case==DAME_NOIR)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion,i+1,j-1 ,i+2,j-2);
    max3=nombredepas_blanc(d.tab[i+2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==PION_NOIR||d.tab[i+1][j+1].etat_case==DAME_NOIR)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_BLANC ,pion,i+1,j+1,i+2,j+2);
    max4=nombredepas_blanc(d.tab[i+2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  int k=0;
  int y=0;
  int*tab=calloc(4,sizeof(int));
  if(max1>=max2&&max1>=max3&&max1>=max4)max=max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)max=max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)max=max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)max=max4;
  if(max==0)return 0;
  if(max==max1){ ajouter(d.tab[i-2][j-2].numero_case,tab); k++;}
  if(max==max2){ ajouter(d.tab[i-2][j+2].numero_case,tab); k++;}
  if(max==max3){ ajouter(d.tab[i+2][j-2].numero_case,tab); k++;}
  if(max==max4){ ajouter(d.tab[i+2][j+2].numero_case,tab); k++;}
  srand(time(NULL));
  y=rand()%k;
  k=tab[y];
  free(tab);
  return k;
}

/*
Principe similaire à la fonction choixdepaspion_blanc en prenant en compte les mouvements possibles de la dame
*/
int choixdepas_blanc_dame(int num ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int max=0;
  int i=d.tabmanoury[num].i;
  int j=d.tabmanoury[num].j;
  int l=1;
  int l1=0;
  int l2=0;
  int l3=0;
  int l4=0;
  while((i-l)>=0 && (j-l)>=0 && d.tab[i-l][j-l].etat_case != PION_BLANC && d.tab[i-l][j-l].etat_case != DAME_BLANC)
  {
  if(d.tab[i-l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j-l].etat_case==PION_NOIR||d.tab[i-l][j-l].etat_case==DAME_NOIR)&& (i-l)-1>=0 && (j-l)-1>=0 && d.tab[(i-l)-1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num ,i-l,j-l,(i-l)-1,(j-l)-1);
    max1=nombredepas_blanc_dame(d.tab[(i-l)-1][(j-l)-1].numero_case,d1)+1;
    l1=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i-l)>=0 && (j+l) <10 && d.tab[i-l][j+l].etat_case != PION_BLANC && d.tab[i-l][j+l].etat_case != DAME_BLANC)
  {
  if(d.tab[i-l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j+l].etat_case==PION_NOIR ||d.tab[i-l][j+l].etat_case==DAME_NOIR)&& (i-l)-1>=0 && (j+l)+1<10 && d.tab[(i-l)-1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, DAME_BLANC ,num ,i-l,j+l,(i-l)-1,(j+l)+1);
    max2=nombredepas_blanc_dame(d.tab[(i-l)-1][(j+l)+1].numero_case,d1)+1;
    l2=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j-l)>=0 && d.tab[i+l][j-l].etat_case != PION_BLANC && d.tab[i+l][j-l].etat_case != DAME_BLANC)
  {
  if(d.tab[i+l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j-l].etat_case==PION_NOIR ||d.tab[i+l][j-l].etat_case==DAME_NOIR)&& (i+l)+1<10 && (j-l)-1>=0 &&d.tab[(i+l)+1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num,i+l,j-l,(i+l)+1,(j-l)-1);
    max3=nombredepas_blanc_dame(d.tab[(i+l)+1][(j-l)-1].numero_case,d1)+1;
    l3=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j+l)<10 && d.tab[i+l][j+l].etat_case != PION_BLANC && d.tab[i+l][j+l].etat_case != DAME_BLANC)
  {
  if(d.tab[i+l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j+l].etat_case==PION_NOIR||d.tab[i+l][j+l].etat_case==DAME_NOIR)&& (i+l)+1<10 && (j+l)+1<10 &&d.tab[(i+l)+1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_BLANC ,num,i+l,j+l,(i+l)+1,(j+l)+1);
    max4=nombredepas_blanc_dame(d.tab[(i+l)+1][(j+l)+1].numero_case,d1)+1;
    l4=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
 int k=0;
 int y=0;
 int*tab=calloc(4,sizeof(int));
 if(max1>=max2&&max1>=max3&&max1>=max4)max=max1;
 if(max2>=max1&&max2>=max3&&max2>=max4)max=max2;
 if(max3>=max2&&max3>=max1&&max3>=max4)max=max3;
 if(max4>=max2&&max4>=max3&&max4>=max1)max=max4;
 if(max==0)return 0;
 if(max==max1){ ajouter(d.tab[i-l1-1][j-l1-1].numero_case,tab); k++;}
 if(max==max2){ ajouter(d.tab[i-l2-1][j+l2+1].numero_case,tab); k++;}
 if(max==max3){ ajouter(d.tab[i+l3+1][j-l3-1].numero_case,tab); k++;}
 if(max==max4){ ajouter(d.tab[i+l4+1][j+l4+1].numero_case,tab); k++;}
 srand(time(NULL));
 y=rand()%k;
 k=tab[y];
 free(tab);
 return k;
}

/*
Fonction qui mange les pions à partir du tableau de pas dans une copie du damier
Renvoie ce tableau de pas
*/
int*rafale(damier d,int couleur,int num){
  int*pas=calloc(100,sizeof(int));
  int k=0;
  int i,j;
  pas[0]=num;
  damier d1=copierdamier(d);
  if(couleur==1){
    while(nombredepas_blanc(num,d1)>0){
      k=choixdepaspion_blanc(num,d1);
      ajouter(k,pas);
      i=d.tabmanoury[find_num_a_manger(d1,num,k)].i;
      j=d.tabmanoury[find_num_a_manger(d1,num,k)].j;
      manger(d1,1,num,i,j,d1.tabmanoury[k].i,d1.tabmanoury[k].j);
      num=k;
    }
  }
  if(couleur==-1){
    while(nombredepas_blanc_dame(num,d1)>0){
      k=choixdepas_blanc_dame(num,d1);
      ajouter(k,pas);
      i=d.tabmanoury[find_num_a_manger(d1,num,k)].i;
      j=d.tabmanoury[find_num_a_manger(d1,num,k)].j;
      manger(d1,-1,num,i,j,d1.tabmanoury[k].i,d1.tabmanoury[k].j);
      num=k;
    }
  }
  if(couleur==2){
    while(nombredepas_noir(num,d1)>0){
      k=choixdepaspion_noir(num,d1);
      ajouter(k,pas);
      i=d.tabmanoury[find_num_a_manger(d1,num,k)].i;
      j=d.tabmanoury[find_num_a_manger(d1,num,k)].j;
      manger(d1,2,num,i,j,d1.tabmanoury[k].i,d1.tabmanoury[k].j);
      num=k;
    }
  }
  if(couleur==-2){
    while(nombredepas_noir_dame(num,d1)>0){
      k=choixdepas_noir_dame(num,d1);
      ajouter(k,pas);
      i=d.tabmanoury[find_num_a_manger(d1,num,k)].i;
      j=d.tabmanoury[find_num_a_manger(d1,num,k)].j;
      manger(d1,-2,num,i,j,d1.tabmanoury[k].i,d1.tabmanoury[k].j);
      num=k;
    }
  }
  detruire_damier(&d1);
  return pas;
}


/*
Similaire à choixdepaspion_blanc
*/
int choixdepaspion_noir(int pion ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int max=0;
  int i=d.tabmanoury[pion].i;
  int j=d.tabmanoury[pion].j;
  if(i-1>=0 && j-1 >=0 &&(d.tab[i-1][j-1].etat_case==PION_BLANC||d.tab[i-1][j-1].etat_case==DAME_BLANC)&& i-2>=0 && j-2 >=0 &&d.tab[i-2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion ,i-1,j-1,i-2,j-2);
    max1=nombredepas_noir(d.tab[i-2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i-1>=0 && j+1 <10 &&(d.tab[i-1][j+1].etat_case==PION_BLANC ||d.tab[i-1][j+1].etat_case==DAME_BLANC)&& i-2>=0 && j+2 <10 &&d.tab[i-2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, PION_NOIR ,pion ,i-1,j+1,i-2,j+2);
    max2=nombredepas_noir(d.tab[i-2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j-1 >=0 &&(d.tab[i+1][j-1].etat_case==PION_BLANC ||d.tab[i+1][j-1].etat_case==DAME_BLANC)&& i+2<10 && j-2 >=0 &&d.tab[i+2][j-2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion,i+1,j-1 ,i+2,j-2);
    max3=nombredepas_noir(d.tab[i+2][j-2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  if(i+1<10 && j+1 <10 &&(d.tab[i+1][j+1].etat_case==PION_BLANC||d.tab[i+1][j+1].etat_case==DAME_BLANC)&& i+2<10 && j+2<10 &&d.tab[i+2][j+2].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,PION_NOIR ,pion,i+1,j+1,i+2,j+2);
    max4=nombredepas_noir(d.tab[i+2][j+2].numero_case,d1)+1;
    detruire_damier(&d1);
  }
  int k=0;
  int y=0;
  int*tab=calloc(4,sizeof(int));
  if(max1>=max2&&max1>=max3&&max1>=max4)max=max1;
  if(max2>=max1&&max2>=max3&&max2>=max4)max=max2;
  if(max3>=max2&&max3>=max1&&max3>=max4)max=max3;
  if(max4>=max2&&max4>=max3&&max4>=max1)max=max4;
  if(max==0)return 0;

  if(max==max1){ ajouter(d.tab[i-2][j-2].numero_case,tab); k++;}
  if(max==max2){ ajouter(d.tab[i-2][j+2].numero_case,tab); k++;}
  if(max==max3){ ajouter(d.tab[i+2][j-2].numero_case,tab); k++;}
  if(max==max4){ ajouter(d.tab[i+2][j+2].numero_case,tab); k++;}
  srand(time(NULL));
  y=rand()%k;
  k=tab[y];
  free(tab);
  return k;
}

/*
Identique à la fonction choixdepas_blanc_dame
*/
int choixdepas_noir_dame(int num ,damier d){
  int max1=0;
  int max2=0;
  int max3=0;
  int max4=0;
  int max=0;
  int i=d.tabmanoury[num].i;
  int j=d.tabmanoury[num].j;
  int l=1;
  int l1=0;
  int l2=0;
  int l3=0;
  int l4=0;
  while((i-l)>=0 && (j-l)>=0 && d.tab[i-l][j-l].etat_case != PION_NOIR && d.tab[i-l][j-l].etat_case != DAME_NOIR)
  {
  if(d.tab[i-l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j-l].etat_case==PION_BLANC||d.tab[i-l][j-l].etat_case==DAME_BLANC)&& (i-l)-1>=0 && (j-l)-1>=0 && d.tab[(i-l)-1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num ,i-l,j-l,(i-l)-1,(j-l)-1);
    max1=nombredepas_noir_dame(d.tab[(i-l)-1][(j-l)-1].numero_case,d1)+1;
    l1=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i-l)>=0 && (j+l) <10 && d.tab[i-l][j+l].etat_case != PION_NOIR && d.tab[i-l][j+l].etat_case != DAME_NOIR)
  {
  if(d.tab[i-l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i-l][j+l].etat_case==PION_BLANC ||d.tab[i-l][j+l].etat_case==DAME_BLANC)&& (i-l)-1>=0 && (j+l)+1<10 && d.tab[(i-l)-1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1, DAME_NOIR ,num ,i-l,j+l,(i-l)-1,(j+l)+1);
    max2=nombredepas_noir_dame(d.tab[(i-l)-1][(j+l)+1].numero_case,d1)+1;
    l2=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j-l)>=0 && d.tab[i+l][j-l].etat_case != PION_NOIR && d.tab[i+l][j-l].etat_case != DAME_NOIR)
  {
  if(d.tab[i+l][j-l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j-l].etat_case==PION_BLANC ||d.tab[i+l][j-l].etat_case==DAME_BLANC)&& (i+l)+1<10 && (j-l)-1>=0 &&d.tab[(i+l)+1][(j-l)-1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num,i+l,j-l,(i+l)+1,(j-l)-1);
    max3=nombredepas_noir_dame(d.tab[(i+l)+1][(j-l)-1].numero_case,d1)+1;
    l3=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
  l=1;
  while((i+l)<10 && (j+l)<10 && d.tab[i+l][j+l].etat_case != PION_NOIR && d.tab[i+l][j+l].etat_case != DAME_NOIR)
  {
  if(d.tab[i+l][j+l].etat_case==CASE_VIDE){l++;}
  else{
    if((d.tab[i+l][j+l].etat_case==PION_BLANC||d.tab[i+l][j+l].etat_case==DAME_BLANC)&& (i+l)+1<10 && (j+l)+1<10 &&d.tab[(i+l)+1][(j+l)+1].etat_case==0)
  {
    damier d1=copierdamier(d);
    manger(d1,DAME_NOIR ,num,i+l,j+l,(i+l)+1,(j+l)+1);
    max4=nombredepas_noir_dame(d.tab[(i+l)+1][(j+l)+1].numero_case,d1)+1;
    l4=l;
    detruire_damier(&d1);
    break;
  }else break;
 }
 }
 int k=0;
 int y=0;
 int*tab=calloc(4,sizeof(int));
 if(max1>=max2&&max1>=max3&&max1>=max4)max=max1;
 if(max2>=max1&&max2>=max3&&max2>=max4)max=max2;
 if(max3>=max2&&max3>=max1&&max3>=max4)max=max3;
 if(max4>=max2&&max4>=max3&&max4>=max1)max=max4;
 if(max==0)return 0;
 if(max==max1){ ajouter(d.tab[i-l1-1][j-l1-1].numero_case,tab); k++;}
 if(max==max2){ ajouter(d.tab[i-l2-1][j+l2+1].numero_case,tab); k++;}
 if(max==max3){ ajouter(d.tab[i+l3+1][j-l3-1].numero_case,tab); k++;}
 if(max==max4){ ajouter(d.tab[i+l4+1][j+l4+1].numero_case,tab); k++;}
 srand(time(NULL));
 y=rand()%k;
 k=tab[y];
 free(tab);
 return k;
}


/*
Pour se déplacer aléatoirement à droite où à gauche
Renvoie le numéro de case où on s'est déplacer
*/
int droite_gauche_aleat(damier d,int num){
 int *tab=calloc(4,sizeof(int));
 int x;
 srand( time( NULL ) );
 if(d.tab[d.tabmanoury[num].i][d.tabmanoury[num].j].etat_case==PION_BLANC  ){

    if(d.tabmanoury[num].j+1<10 && d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j+1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j+1].numero_case;
      ajouter(x,tab);
    }
    if(d.tabmanoury[num].j-1>-1 && d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j-1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j-1].numero_case;
      ajouter(x,tab);
    }
 }

 if(d.tab[d.tabmanoury[num].i][d.tabmanoury[num].j].etat_case==PION_NOIR  ){

    if(d.tabmanoury[num].j+1<10 && d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j+1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j+1].numero_case;
      ajouter(x,tab);
    }
    if(d.tabmanoury[num].j-1>-1 && d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j-1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j-1].numero_case;
      ajouter(x,tab);
    }
 }
 if(d.tab[d.tabmanoury[num].i][d.tabmanoury[num].j].etat_case==DAME_BLANC || d.tab[d.tabmanoury[num].i][d.tabmanoury[num].j].etat_case==DAME_NOIR )
 {

    if(d.tabmanoury[num].j+1<10 && d.tabmanoury[num].i-1>-1 && d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j+1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j+1].numero_case;
      ajouter(x,tab);
    }
    if(d.tabmanoury[num].j-1>-1 && d.tabmanoury[num].i-1>-1 && d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j-1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i-1][d.tabmanoury[num].j-1].numero_case;
      ajouter(x,tab);
    }
     if(d.tabmanoury[num].j+1<10 && d.tabmanoury[num].i+1<10 && d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j+1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j+1].numero_case;
      ajouter(x,tab);
    }
    if(d.tabmanoury[num].j-1>-1 && d.tabmanoury[num].i+1<10 && d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j-1].etat_case==CASE_VIDE){
      x=d.tab[d.tabmanoury[num].i+1][d.tabmanoury[num].j-1].numero_case;
      ajouter(x,tab);
    }
 }   int e=0;


  x=rand() % size_tab(tab);

  return tab[x];

}
