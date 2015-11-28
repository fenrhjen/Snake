#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include<time.h>
#include<string.h>

#define BORD 10 /*nbre pixel contour écran*/

void printTerrain(int snake[300][2], int len_snake, int pommes[20][2], int len_pommes){
  int i;
  /*reset image*/
  ChargerImage("background.png",BORD,BORD,0,0,600,400);

  /*affichage snake*/
  for (i=0; i<len_snake-1; i++) {
    DessinerSegment(snake[i][0]*10,snake[i][1]*10,snake[i+1][0]*10,snake[i+1][1]*10);
  }

  /*affichage pommes*/
  for (i=0; i<len_pommes; i++) ChargerImage("pomme.png",pommes[i][0]*10,pommes[i][1]*10,0,0,10,10);
}

void printTime(unsigned long int time ){
  /*ECRIT VINCENT*/
  char tabSecondes[3]={}, tabMinutes[50]={};/*On prépare une case de plus au cas où les minutes dépassent 99*/
  int secondes,minutes;
  secondes=(int)((Microsecondes()-time)/1000000);
  minutes=secondes/60;
  secondes=secondes%60;
  sprintf(tabSecondes,"%d",secondes);/*conversion entier en chaîne caractères*/
  sprintf(tabMinutes,"%d",minutes);
  strcat(strcat(tabMinutes,":"),tabSecondes);
  EcrireTexte(10,380,tabMinutes,1);
  printf("%d\n", secondes);
  printf("%d", minutes);
}

void printScore(int score){
  char str[15];
  sprintf(str, "%d", score);
  EcrireTexte(10,100,str,2);
}

void printScreen(int snake[300][2], int len_snake, int pommes[20][2], int len_pommes, int time, int score){
  EffacerEcran(CouleurParNom("black"));
  printTerrain(snake, len_snake, pommes, len_pommes);
  printScore(score);
  printTime(time);
}

void initSnake(int snake[300][2]){
  int i;
  for (i=10;i<300;i++)
    snake[i][0]=-1;
  for (i=0; i<10; i++){
    snake[i][0]=30;
    snake[i][1]=20+i;
    
  }
}

void placePomme(int pommes[20][2], int num){
  pommes[num][0]=rand()%60;
  pommes[num][1]=rand()%40;
}

void initPommes(int pommes[20][2]){
  int i;
  for (i=0; i<5; i++) placePomm:xe(pommes, i);
}



int main(void) {
  int snake[300][2],
      len_snake=10,
      pommes[20][2],
      len_pommes=5,
      i;
  unsigned long int temps = Microsecondes();
  initSnake(snake);
  initPommes(pommes);
  
  srand(time(NULL));
  InitialiserGraphique();
  CreerFenetre(BORD,BORD,600+2*BORD,400+BORD+40);

  printTerrain(snake, len_snake, pommes, len_pommes);
  printTime(temps);
    
  Touche();
  FermerGraphique();
  return EXIT_SUCCESS;
}
