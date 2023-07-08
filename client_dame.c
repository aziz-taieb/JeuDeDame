#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdint.h>
#define PORT_DAME 7777


#include "constantes.h"
#include "fonctions.h"

//Serveur -- blanc et sinon noir

void usage(char *nom_prog)
{

	fprintf(stderr, "Usage: %s addr_ipv6"
            "Exemple: %s 2001:db8:3c4d:15:0:d234:3eee::\n",nom_prog, nom_prog);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}
	/* 1. Création d'une socket tcp ipv6 */
	int sock = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}

	/* 2. Création de la sockaddr */
	int stat;
	struct addrinfo hints={
		.ai_socktype = SOCK_STREAM,
		.ai_flags=AI_V4MAPPED,
		.ai_family = AF_INET6
	};
	struct addrinfo *x;

	if((stat= getaddrinfo(argv[1],"7777", &hints, &x)) !=0){
		printf("%s\n", gai_strerror(stat));
		return 2;
	}

	/* 3. Tentative de connection */
	if (connect(sock, x->ai_addr, x->ai_addrlen) < 0) {
		perror("connect");
		exit(3);
	}
			
			 int t=0;//je l'ai ajouter pour ecrire sur le tableau d'octect
	uint8_t tab_octet[256];//il a precisez que une partie peut faire au max 239 octet donc j'ai mis ca pour l'instant 
	tab_octet[0]=0x01;//le premier octet est un FF ou un 01 selon que vous soyez blanc (serveur) ou noir (challenger),
	t++;
	memcpy(tab_octet+t,&(x->ai_addr),16);
	t+16;



/*Partie jeu**************************************************************************************************************/

   char buffer1[1024];
    char *buffer;
 
  int *mouv;
      damier d;   
    int i,a,i1,alt,y=0;
	 int num,zo,verif;
	 int coul;
int ch_aleat;
    damier_initialisation(&d);
  srand( time( NULL ) );

  
 
  verif=0;
 
    do{   
		buffer=malloc(sizeof(char)*1024);
      d.compteur_de_coup++;
	
	if(d.nb_restant_blanc==0){break;} 
      if(read(sock , buffer, 1024)<0){
					perror("read");}

		if(buffer[1]!='-'&& buffer[2]!='-'  &&  buffer[1]!='x'&&  buffer[2]!='x' ){
						printf("aucun mouvement possible du serveur egalité  \n  ");
						printf("  %s\n  ",buffer);
						break;
					} 			

	if(buffer=="aucun mouvement possible egalité"){
				printf("aucun mouvement possible du serveur egalité  %s\n  ",buffer);
				break;
		} 
		printf("on a recu ca %s\n  ",buffer);
	
		
				mouv=recupp_val(buffer);
				
				i1=0;
		
			

		


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
       


				mouv=mouvement_possible_final(d, PION_NOIR);
				
        if(size_tab(mouv)==0){ buffer="aucun mouvement possible egalité"; 
			if(write(sock , buffer, 1024)<0){
					perror("write");}
			break;} 

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
					if(write(sock , buffer, 1024)<0){
					perror("write");}
				
          for(a=0;a<1024;a++)
						{
							buffer[a]='\0';
						
						}
				

			

				for(a=0;a<NOMBRE_PION;a++)
						{
							mouv[a]=0;
						} 
						free(buffer);  
			
    }while(game_over(d)!=FIN_DE_PARTIE);
	
  printf("blanc restant %d et noir %d  \n",d.nb_restant_blanc,d.nb_restant_noir);

    affichage_gagnant(d);
	if(d.nb_restant_blanc!=0 && d.nb_restant_noir!=0 && d.compteur_de_coup!=50){
			printf("\n interruption causé par un mauvais coup en reseau\n  ");
			printf("ou par un aucun coup possible de l un es joueur donc EGALITE probable\n ");
	} 

    free(mouv);
	close(sock);
	detruire_damier(&d);



	

/*****************FIN PARTIE JEU **********************************************************************************************/
/*

	int sock_protocole = socket(AF_INET6, SOCK_STREAM, 0);
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




