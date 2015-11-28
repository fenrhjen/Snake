#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<graph.h>
#include "constantes.h"

int main(void) {

  srand((unsigned int)time(NULL));
  int snake[TAILLE_SNAKE][2],
      len_snake=10,
      pommes[TAILLE_POMME][2],
      len_pommes=5,
      direction[2]={0,-1},
      score=0,
      done=0;
  unsigned long int tempsDepart=Microsecondes(), tempsTmp;
  unsigned long int prochainAffichage=0,prochainDeplacement=0;
  initSnake(snake,len_snake);
  initPommes(pommes, len_pommes, snake, len_snake);
  InitialiserGraphique();
  CreerFenetre(BORD,BORD,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40);
  ChoisirEcran(1);/*on dessine tout dans un ecran virtuel (cela joue le role de buffer)
                    puis dans la fonction printScreen on copie l'ecran virtuel sur l'ecran reel*/


  while(!done){
    if(Microsecondes()>prochainAffichage){
      printScreen(snake, len_snake,  pommes, len_pommes, tempsDepart, score);
      prochainAffichage=Microsecondes()+CYCLE;
    }
    tempsTmp=Microsecondes();
    GestionTouche(snake, direction, &done);
    tempsDepart+=Microsecondes()-tempsTmp;
    if(Microsecondes()>prochainDeplacement){
      DeplacementSnake(snake, len_snake, direction);
      CheckCollisionBord(snake, &done);
      CheckCollisionPomme(len_pommes, pommes, snake, &len_snake, &score);
      prochainDeplacement=Microsecondes()+100000;
    }
  }
  FermerGraphique();
  return EXIT_SUCCESS;
}

