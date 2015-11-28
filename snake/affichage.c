#include "affichage.h"
#include <stdio.h>
#include <string.h>


void ChargerImageArg(int x, int y, char* file, int xx, int yy, int l, int h){
  ChargerImage(file,x,y,xx,yy,l,h);/*cette fonction permet juste de reorganiser les arguments
                                     de la fonction ChargerImage pour une utilisation simplifiée*/
}

void printTerrain(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes){
  int i;
  /*reset image*/
  ChargerImage("images/fondsolmarron.png",BORD,BORD,0,0,60*TAILLE_CASE,40*TAILLE_CASE);

  /*affichage snake*/ 
  /*affichage tête*/
  if (snake[0][1]<snake[1][1]) ChargerImageArg( snake[0][0]*TAILLE_CASE+BORD,    snake[0][1]*TAILLE_CASE+BORD, SNAKE_HEAD_UP);
  if (snake[0][1]>snake[1][1]) ChargerImageArg( snake[0][0]*TAILLE_CASE+BORD,   (snake[0][1]-1)*TAILLE_CASE+BORD, SNAKE_HEAD_DOWN);
  if (snake[0][0]>snake[1][0]) ChargerImageArg((snake[0][0]-1)*TAILLE_CASE+BORD, snake[0][1]*TAILLE_CASE+BORD, SNAKE_HEAD_RIGHT);
  if (snake[0][0]<snake[1][0]) ChargerImageArg( snake[0][0]*TAILLE_CASE+BORD,    snake[0][1]*TAILLE_CASE+BORD, SNAKE_HEAD_LEFT);

  /*Affichage corps*/
  for (i=1; i<len_snake-1; i++) {
    if (snake[i][1]<snake[i+1][1]) ChargerImageArg( snake[i][0]*TAILLE_CASE+BORD,    snake[i][1]*TAILLE_CASE+BORD, SNAKE_BODY_UP);
    if (snake[i][1]>snake[i+1][1]) ChargerImageArg( snake[i][0]*TAILLE_CASE+BORD,   (snake[i][1]-1)*TAILLE_CASE+BORD, SNAKE_BODY_DOWN);
    if (snake[i][0]>snake[i+1][0]) ChargerImageArg((snake[i][0]-1)*TAILLE_CASE+BORD, snake[i][1]*TAILLE_CASE+BORD, SNAKE_BODY_RIGHT);
    if (snake[i][0]<snake[i+1][0]) ChargerImageArg( snake[i][0]*TAILLE_CASE+BORD,    snake[i][1]*TAILLE_CASE+BORD, SNAKE_BODY_LEFT);
  }
  /*Affichage queue*/
  if (snake[i][1]>snake[i-1][1]) ChargerImageArg(snake[i][0]*TAILLE_CASE+BORD, snake[i][1]*TAILLE_CASE+BORD, SNAKE_TAIL_UP);
  if (snake[i][1]<snake[i-1][1]) ChargerImageArg(snake[i][0]*TAILLE_CASE+BORD, snake[i][1]*TAILLE_CASE+BORD, SNAKE_TAIL_DOWN);
  if (snake[i][0]<snake[i-1][0]) ChargerImageArg(snake[i][0]*TAILLE_CASE+BORD, snake[i][1]*TAILLE_CASE+BORD, SNAKE_TAIL_RIGHT);
  if (snake[i][0]>snake[i-1][0]) ChargerImageArg(snake[i][0]*TAILLE_CASE+BORD, snake[i][1]*TAILLE_CASE+BORD, SNAKE_TAIL_LEFT);

  /*affichage pommes*/
  for (i=0; i<len_pommes; i++) ChargerImageArg(pommes[i][0]*TAILLE_CASE+BORD,pommes[i][1]*TAILLE_CASE+BORD,APPLE);
}




void printTime(unsigned long int time,unsigned long int tempsActuel ){
  char tabSecondes[3]={}, tabMinutes[50]={};/*On prépare une case de plus au cas où les minutes dépassent 99*/
  int secondes,minutes;
  secondes=(int)((tempsActuel-time)/1000000);
  minutes=secondes/60;
  secondes=secondes%60;
  sprintf(tabSecondes,"%02d",secondes);/*conversion entier en chaîne caractères*/
  sprintf(tabMinutes,"%02d",minutes);
  strcat(strcat(tabMinutes,":"),tabSecondes);/* reviens a faire  " tabMinutes=$tabMinutes:$tabSecondes "  en bash*/
  EcrireTexte(BORD,40*TAILLE_CASE+BORD+30,tabMinutes,2);
}

void printScore(int score){
  char str[15];
  sprintf(str, "%05d", score);
  EcrireTexte(60*TAILLE_CASE+BORD-TailleChaineEcran("00000",2),40*TAILLE_CASE+BORD+30,str,2);
}

void printScreen(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes, unsigned long int time,unsigned long int tempsActuel, int score){
  EffacerEcran(CouleurParNom("black"));
  printTerrain(snake, len_snake, pommes, len_pommes);
  ChoisirCouleurDessin(CouleurParNom("white"));
  printScore(score);
  printTime(time,tempsActuel);
  CopierZone(1,0,0,0,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40,0,0);
}


