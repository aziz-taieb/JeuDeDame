#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include "constantes.h"
#include "fonctions.h"

int main(int argc, char *argv[])
{
    char *buffer;
  //	int *mouv=calloc(21, sizeof(int));
  int *mouv;
      damier d;   
    int i,a,i1,alt,y=0;
	 int num,verif;
	 int coul;
int ch_aleat;
    damier_initialisation(&d);
  srand( time( NULL ) );

  
 
  verif=0;
    do{  
      d.compteur_de_coup++;
        mouv=mouvement_possible_final(d, PION_BLANC);
	
       if(size_tab(mouv)==0){ break;} 
       
         alt=rand() % size_tab(mouv);
        
				 ch_aleat= mouv[alt] ;
			
				 	

				for(a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	

	
				i1=0;
				
			

				if(d.tab[d.tabmanoury[ch_aleat].i][d.tabmanoury[ch_aleat].j].etat_case==PION_BLANC ){
					if(nombredepas_blanc(ch_aleat ,d)==0){
							
            mouv=rafale(d,PION_BLANC,ch_aleat);
             mouv[1]=droite_gauche_aleat(d,mouv[0]);
						buffer=tostring(0,mouv);
					} 
					else{
            mouv=rafale(d,PION_BLANC,ch_aleat);
						buffer=tostring(size_tab(mouv)-1,mouv);
					} 

						
				} 

				if(d.tab[d.tabmanoury[ch_aleat].i][d.tabmanoury[ch_aleat].j].etat_case==DAME_BLANC ){
						
					if(nombredepas_blanc_dame(ch_aleat ,d)==0){
							
            mouv=rafale(d,DAME_BLANC,ch_aleat);
			a=0;
			
			
			mouv[1]=droite_gauche_aleat(d,mouv[0]);   
			
						buffer=tostring(0,mouv);
					} 
					else{
            mouv=rafale(d,DAME_BLANC,ch_aleat);
						buffer=tostring(size_tab(mouv)-1,mouv);
					} 
 
						
				}

				if(verif_manger(buffer)==1){

					deplacement(&d,d.tabmanoury[mouv[0]].i, d.tabmanoury[mouv[0]].j, d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);
					make_king(&d, PION_BLANC,d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);
						



				}else{  
					i1=0;
					while(mouv[i1+1]!=0){
         
						coul= d.tab[d.tabmanoury[mouv[i1]].i][d.tabmanoury[mouv[i1]].j].etat_case;
						num=find_num_a_manger(d,mouv[i1],mouv[i1+1]);
						
						manger(d,coul,num, d.tabmanoury[mouv[i1]].i, d.tabmanoury[mouv[i1]].j, d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j );
						d.nb_restant_noir--;
						make_king(&d, PION_BLANC,d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j);
						i1++;


					}
					for( a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	
				} 
       
		 		damier_affichage(d);

				mouv=mouvement_possible_final(d, PION_NOIR);
				
        if(size_tab(mouv)==0){ break;} 

				alt=rand() % size_tab(mouv);
               ch_aleat= mouv[rand() % size_tab(mouv)] ;
			 
			
				for(a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	
            for(a=0;a<1024;a++)
						{
							buffer[a]='\0';
						}	
				

				i1=0;
				
			

				if(d.tab[d.tabmanoury[ch_aleat].i][d.tabmanoury[ch_aleat].j].etat_case==PION_NOIR ){
					if(nombredepas_noir(ch_aleat ,d)==0){
            mouv=rafale(d,PION_NOIR,ch_aleat);
			mouv[1]=droite_gauche_aleat(d,mouv[0]);

						buffer=tostring(0,mouv);
					} 
					else{
            mouv=rafale(d,PION_NOIR,ch_aleat);
						buffer=tostring(size_tab(mouv)-1,mouv);
					} 

						
				} 

				if(d.tab[d.tabmanoury[ch_aleat].i][d.tabmanoury[ch_aleat].j].etat_case==DAME_NOIR ){
						
					if(nombredepas_noir_dame(ch_aleat ,d)==0){
							
            mouv=rafale(d,DAME_NOIR,ch_aleat);
			
			mouv[1]=droite_gauche_aleat(d,mouv[0]);
				
						buffer=tostring(0,mouv);
					} 
					else{
            mouv=rafale(d,DAME_NOIR,ch_aleat);
						buffer=tostring(size_tab(mouv)-1,mouv);
					} 
 
						
				}

				if(verif_manger(buffer)==1){

					deplacement(&d,d.tabmanoury[mouv[0]].i, d.tabmanoury[mouv[0]].j, d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);
					make_king(&d, PION_NOIR,d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);

					 

				}else{
					i1=0;
					while(mouv[i1+1]!=0){

						coul= d.tab[d.tabmanoury[mouv[i1]].i][d.tabmanoury[mouv[i1]].j].etat_case;
						num=find_num_a_manger(d,mouv[i1],mouv[i1+1]);
						
						manger(d,coul,num, d.tabmanoury[mouv[i1]].i, d.tabmanoury[mouv[i1]].j, d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j );
						d.nb_restant_blanc--;
						make_king(&d, PION_NOIR,d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j);
						i1++;

						

					}
          
         
					for( a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	
				}
				
          for(a=0;a<1024;a++)
						{
							buffer[a]='\0';
						}
				

			

				for(a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}   
			damier_affichage(d);
    }while(game_over(d)!=FIN_DE_PARTIE);
	
  printf("blanc restant %d et noir %d  \n",d.nb_restant_blanc,d.nb_restant_noir);

    affichage_gagnant(d);


    free(mouv);
	
	detruire_damier(&d);

    return 0;
}  
