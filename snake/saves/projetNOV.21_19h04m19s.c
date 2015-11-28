#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<graph.h>
#include "constantes.h"

void ChargerImageArg(int x, int y, char* file, int xx, int yy, int l, int h){
  ChargerImage(file,x,y,xx,yy,l,h);
}

void printTerrain(int snake[300][2], int len_snake, int pommes[20][2], int len_pommes){
  int i;
  /*reset image*/
  ChargerImage("background.png",BORD,BORD,0,0,60*TAILLE_CASE,40*TAILLE_CASE);

  /*affichage snake*/
  if (snake[0][1]<snake[1][1]) ChargerImageArg( snake[0][0]*TAILLE_CASE,    snake[0][1]*TAILLE_CASE, SNAKE_HEAD_UP);
  if (snake[0][1]>snake[1][1]) ChargerImageArg( snake[0][0]*TAILLE_CASE,   (snake[0][1]-1)*TAILLE_CASE, SNAKE_HEAD_DOWN);
  if (snake[0][0]>snake[1][0]) ChargerImageArg((snake[0][0]-1)*TAILLE_CASE, snake[0][1]*TAILLE_CASE, SNAKE_HEAD_RIGHT);
  if (snake[0][0]<snake[1][0]) ChargerImageArg( snake[0][0]*TAILLE_CASE,    snake[0][1]*TAILLE_CASE, SNAKE_HEAD_LEFT);
  for (i=0; i<len_snake-1; i++) {
    if (snake[i][1]<snake[i+1][1]) ChargerImageArg( snake[i][0]*TAILLE_CASE,    snake[i][1]*TAILLE_CASE, SNAKE_BODY_UP);
    if (snake[i][1]>snake[i+1][1]) ChargerImageArg( snake[i][0]*TAILLE_CASE,   (snake[i][1]-1)*TAILLE_CASE, SNAKE_BODY_DOWN);
    if (snake[i][0]>snake[i+1][0]) ChargerImageArg((snake[i][0]-1)*TAILLE_CASE, snake[i][1]*TAILLE_CASE, SNAKE_BODY_RIGHT);
    if (snake[i][0]<snake[i+1][0]) ChargerImageArg( snake[i][0]*TAILLE_CASE,    snake[i][1]*TAILLE_CASE, SNAKE_BODY_LEFT);
  }
  if (snake[i][1]>snake[i-1][1]) ChargerImageArg(snake[i][0]*TAILLE_CASE, snake[i][1]*TAILLE_CASE, SNAKE_TAIL_UP);
  if (snake[i][1]<snake[i-1][1]) ChargerImageArg(snake[i][0]*TAILLE_CASE, snake[i][1]*TAILLE_CASE, SNAKE_TAIL_DOWN);
  if (snake[i][0]<snake[i-1][0]) ChargerImageArg(snake[i][0]*TAILLE_CASE, snake[i][1]*TAILLE_CASE, SNAKE_TAIL_RIGHT);
  if (snake[i][0]>snake[i-1][0]) ChargerImageArg(snake[i][0]*TAILLE_CASE, snake[i][1]*TAILLE_CASE, SNAKE_TAIL_LEFT);

  /*affichage pommes*/
  for (i=0; i<len_pommes; i++) ChargerImageArg(pommes[i][0]*TAILLE_CASE,pommes[i][1]*TAILLE_CASE,APPLE);
}

void printTime(unsigned long int time ){
  /*ECRIT VINCENT*/
  char tabSecondes[3]={}, tabMinutes[50]={};/*On prépare une case de plus au cas où les minutes dépassent 99*/
  int secondes,minutes;
  secondes=(int)((Microsecondes()-time)/1000000);
  minutes=secondes/60;
  secondes=secondes%60;
  sprintf(tabSecondes,"%02d",secondes);/*conversion entier en chaîne caractères*/
  sprintf(tabMinutes,"%02d",minutes);
  strcat(strcat(tabMinutes,":"),tabSecondes);
  EcrireTexte(BORD,40*TAILLE_CASE+BORD+30,tabMinutes,2);
}

void printScore(int score){
  char str[15];
  sprintf(str, "%05d", score);
  EcrireTexte(60*TAILLE_CASE+BORD-TailleChaineEcran("00000",2),40*TAILLE_CASE+BORD+30,str,2);
}

void printScreen(int snake[300][2], int len_snake, int pommes[20][2], int len_pommes, unsigned long int time, int score){
  EffacerEcran(CouleurParNom("black"));
  printTerrain(snake, len_snake, pommes, len_pommes);
  ChoisirCouleurDessin(CouleurParNom("white"));
  printScore(score);
  printTime(time);
  CopierZone(1,0,0,0,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40,0,0);
}

void initSnake(int snake[300][2]){
  int i;
  for (i=10;i<300;i++)
    snake[i][0]=-1;
  /*for (i=0; i<10; i++){
    snake[i][0]=30;
    snake[i][1]=20+i;
  }
  
   **********test affichage**************/
  snake[0][0]=30;  snake[0][1]=20;
  snake[1][0]=31;  snake[1][1]=20;
  snake[2][0]=31;  snake[2][1]=21;
  snake[3][0]=30;  snake[3][1]=21;
  snake[4][0]=30;  snake[4][1]=22;
  snake[5][0]=31;  snake[5][1]=22;
  snake[6][0]=31;  snake[6][1]=23;
  snake[7][0]=32;  snake[7][1]=23;
  snake[8][0]=32;  snake[8][1]=24;
  snake[9][0]=32;  snake[9][1]=25;
}

void placePomme(int pommes[20][2], int num){
  pommes[num][0]=rand()%60;
  pommes[num][1]=rand()%40;
}

void initPommes(int pommes[20][2]){
  int i;
  for (i=0; i<5; i++) placePomme(pommes, i);
}

int main(void) {

  int snake[300][2],
      len_snake=10,
      pommes[20][2],
      len_pommes=5;
  unsigned long int temps = Microsecondes(),suivant=0;
  initSnake(snake);
  initPommes(pommes);

  srand(time(NULL));
  InitialiserGraphique();
  CreerFenetre(BORD,BORD,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40);
  ChoisirEcran(1);


  /*EffacerEcran(CouleurParNom("black"));
  */
  while(ToucheEnAttente()==0){
    if(Microsecondes()>suivant){

      printScreen(snake, len_snake,  pommes, len_pommes, temps, 45 );
      suivant=Microsecondes()+CYCLE;
    }
  }
  Touche();
  FermerGraphique();

  return EXIT_SUCCESS;
}
