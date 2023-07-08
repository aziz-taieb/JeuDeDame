#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>

#define PORT_DAME 7777
#include "constantes.h"
#include "fonctions.h"

int main(int argc, char *argv[])
{

    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in6 sa = { .sin6_family = AF_INET6,
				  .sin6_port = htons(PORT_DAME),
				  .sin6_addr.s6_addr =htonl(INADDR_ANY)};

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if (bind(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
        perror("bind");
        exit(3);
    }
	uint8_t tab_octet[256];//il a precisez que une partie peut faire au max 239 octet donc j'ai mis ca pour l'instant 

    if (listen(sock, 128) < 0) {
        perror("listen");
        exit(2);
    }

    struct sockaddr_in6 addr_clt6;
    socklen_t addrlen6 = sizeof(struct sockaddr_in6);

    int sock_echange = accept(sock, (struct sockaddr *) &addr_clt6, &addrlen6);

    char addr_char[INET6_ADDRSTRLEN];
    if (inet_ntop(AF_INET6, &(addr_clt6.sin6_addr), addr_char, INET6_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
    }
	printf("%s \n ",addr_char);
    
		 int t=0;//je l'ai ajouter pour ecrire sur le tableau d'octect
	
	tab_octet[0]=0xff;//le premier octet est un FF ou un 01 selon que vous soyez blanc (serveur) ou noir (challenger),
	t++;
	memcpy(tab_octet+t,&(addr_clt6.sin6_addr),16);
	t+16;


   /*Partie jeu**************************************************************************************************************/
   
     char *buffer;
	 char buffer1[1024]; 
  
  int *mouv;
      damier d;   
    int i,a,i1,alt,zo,y=0;
	 int num,verif;
	 int coul;
int ch_aleat;
    damier_initialisation(&d);
  srand( time( NULL ) );

  
 
  verif=0;
    do{  
      d.compteur_de_coup++;
        mouv=mouvement_possible_final(d, PION_BLANC);
	
       if(size_tab(mouv)==0){ buffer="aucun mouvement possible egalité"; 
			if(write(sock_echange , buffer, 1024)<0){
					perror("write");}
			break;} 
       
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
						
					/**********************************************************************/
					*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[0];
					t++;
					*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[1];
					t++;
					/**********************************************************************/


				}else{  
					i1=0;
					while(mouv[i1+1]!=0){
         
						coul= d.tab[d.tabmanoury[mouv[i1]].i][d.tabmanoury[mouv[i1]].j].etat_case;
						num=find_num_a_manger(d,mouv[i1],mouv[i1+1]);
						
						manger(d,coul,num, d.tabmanoury[mouv[i1]].i, d.tabmanoury[mouv[i1]].j, d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j );
						d.nb_restant_noir--;
						make_king(&d, PION_BLANC,d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j);
						

						 /**********************************************************************/
						    
						*(tab_octet + t*sizeof(uint8_t)) = mouv[i1];
							t++;
						if(mouv[i1+2]==0){
							*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[i1+1];
							t++;

						}	
						/**********************************************************************/
						i1++;
					}

					for( a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	
				} 
       
		 		for( a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}

				
			
				 
			if(write(sock_echange , buffer, 1024)<0){
					perror("write");}
			 
				
            for(a=0;a<1024;a++)
						{
							buffer[a]='\0';
						
						}	
				

				i1=0;
			
		if(d.nb_restant_noir==0){break;} 
		printf("blanc restant %d et noir %d  \n",d.nb_restant_blanc,d.nb_restant_noir);
			 if(read(sock_echange , buffer, 1024)<0){
					perror("read");}
					printf("j'ai recup ca du client %s\n  ",buffer);
					if(buffer[1]!='-'&& buffer[2]!='-'  &&  buffer[1]!='x'&&  buffer[2]!='x' ){
						printf("  %s\n  ",buffer);
						break;
					} 
			
		 	
				
				mouv=recupp_val(buffer);
				
			

				if(verif_manger(buffer)==1){

					deplacement(&d,d.tabmanoury[mouv[0]].i, d.tabmanoury[mouv[0]].j, d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);
					make_king(&d, PION_NOIR,d.tabmanoury[mouv[1]].i, d.tabmanoury[mouv[1]].j);

					 /**********************************************************************/
					*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[0];
					t++;
					*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[1];
					t++;
					/**********************************************************************/
					 

				}else{
					i1=0;
					while(mouv[i1+1]!=0){

						coul= d.tab[d.tabmanoury[mouv[i1]].i][d.tabmanoury[mouv[i1]].j].etat_case;
						num=find_num_a_manger(d,mouv[i1],mouv[i1+1]);
						
						manger(d,coul,num, d.tabmanoury[mouv[i1]].i, d.tabmanoury[mouv[i1]].j, d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j );
						d.nb_restant_blanc--;
						make_king(&d, PION_NOIR,d.tabmanoury[mouv[i1+1]].i, d.tabmanoury[mouv[i1+1]].j);



						 /**********************************************************************/
						    
						*(tab_octet + t*sizeof(uint8_t)) = mouv[i1];
							t++;
						if(mouv[i1+2]==0){
							*(tab_octet + t*sizeof(uint8_t)) = 0x80+mouv[i1+1];
							t++;

						}	
						/**********************************************************************/
						i1++;

						

					}
          
         
					for( a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}	
				}
				free(buffer);
    
				

			

				for(a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						}   
			
    }while(game_over(d)!=FIN_DE_PARTIE); 
	printf("blanc restant %d et noir %d  \n",d.nb_restant_blanc,d.nb_restant_noir);
	close(sock_echange);
     affichage_gagnant(d);
	if(d.nb_restant_blanc!=0 && d.nb_restant_noir!=0 && d.compteur_de_coup!=50){
			printf("\n interruption causé par un mauvais coup en reseau\n  ");
			printf("ou par un aucun coup possible de l un es joueur donc EGALITE probable\n ");
	}
   
    free(mouv);
	
	detruire_damier(&d);

close(sock_echange); 
 close(sock);



/*****************FIN PARTIE JEU **********************************************************************************************/


/*	int sock_protocole = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}
	char serveur_ip[]="2001:910:1410:523:0:fada:80af:2bc2" ;

	
	struct sockaddr_in6 sa = { .sin_family = AF_INET6, .sin_port = htons(PORT_DAME)};
	if (inet_pton(AF_INET6,ip , &sa.sin_addr) != 1) {
		fprintf(stderr, "adresse ipv6 non valable\n");
		exit(1);
	}

	
	if (connect(sock_protocole, (struct sockaddr *) &sa, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
		exit(3);
	}
	
int q9;
for(int to=0;to<256;to++) { 
q9=tab_octet[to];
	
	if(write(sock_protocole , &q9 , sizeof(uint8_t))<0){
					perror("write");}
}	 
	for(a=0;a<1024;a++)
			{
				buffer[a]='\0';
			}
	if(read(sock_protocole , buffer , sizeof(buffer))<0){
					perror("write");}
	printf("\n\n%s\n",buffer);				

close(sock_protocole);*/

    return 0;
}


