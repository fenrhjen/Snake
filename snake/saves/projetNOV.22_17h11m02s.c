#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<graph.h>
#include "constantes.h"

#define POS_X_HEAD_SNAKE snake[0][0]
#define POS_Y_HEAD_SNAKE snake[0][1]
#define TAILLE_POMME 20
#define TAILLE_SNAKE 300
void ChargerImageArg(int x, int y, char* file, int xx, int yy, int l, int h){
  ChargerImage(file,x,y,xx,yy,l,h);/*cette fonction permet juste de reorganiser les arguments
                                     de la fonction ChargerImage pour une utilisation simplifiée*/
}

void printTerrain(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes){
  int i;
  /*reset image*/
  ChargerImage("images/fondvertdegrade.png",BORD,BORD,0,0,60*TAILLE_CASE,40*TAILLE_CASE);

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




void printTime(unsigned long int time ){
  char tabSecondes[3]={}, tabMinutes[50]={};/*On prépare une case de plus au cas où les minutes dépassent 99*/
  int secondes,minutes;
  secondes=(int)((Microsecondes()-time)/1000000);
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

void printScreen(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes, unsigned long int time, int score){
  EffacerEcran(CouleurParNom("black"));
  printTerrain(snake, len_snake, pommes, len_pommes);
  ChoisirCouleurDessin(CouleurParNom("white"));
  printScore(score);
  printTime(time);
  CopierZone(1,0,0,0,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40,0,0);
}

void initSnake(int snake[TAILLE_SNAKE][2],int len_snake){
  int i;
  for (i=0; i<len_snake; i++){
    snake[i][0]=30;
    snake[i][1]=20+i;
  }
}

void placePomme(int pommes[TAILLE_POMME][2], int len_pommes, int num, int snake[TAILLE_SNAKE][2], int len_snake){
  int isOnSomething=0,/* vaut 1 si la pomme aléatoire est soit sur le snake soit sur une autre pomme*/
      i;
  do{
    pommes[num][0]=rand()%60;/*pomme aléatoire*/
    pommes[num][1]=rand()%40;
    for (i=0; i<len_snake; i++){ /*on verifie que la pomme placé est pas sur le snake*/
      if (snake[i][0]==pommes[num][0] &&
          snake[i][1]==pommes[num][1])
        isOnSomething=1;
    }
    for (i=0; i<len_pommes; i++){ /*on verifie que la pomme placé est pas sur une autre POMME*/
      if (pommes[i][0]==pommes[num][0] &&
          pommes[i][1]==pommes[num][1] &&
          num!=i)
        isOnSomething=1;
    }
  }while(isOnSomething==1);/*il ne faut pas que la pomme placée soit "sur" qqchose 
                         donc on relance l'aléatoire tant que la pomme est sur qqchose*/
}

void initPommes(int pommes[TAILLE_POMME][2], int len_pommes, int snake[TAILLE_SNAKE][2], int len_snake){
  int i;
  for (i=0; i<len_pommes; i++) placePomme(pommes, len_pommes, i, snake, len_snake);
}

void GestionTouche(int snake[TAILLE_SNAKE][2],int direction[2], int* done){
  unsigned int touchePress;
  /*Deplacement à droite*/
  if (ToucheEnAttente()==1){
    touchePress=Touche();
    if(touchePress==XK_Escape){
      *done=1;
    }else
    if(touchePress==XK_space){
      ChargerImageArg(0,0,IMAGE_PAUSE);
      while(Touche()!=XK_space);
    }
    /******UPDATE DIRECTION********/
    if(touchePress==XK_Right && direction[0]==0){
      direction[0]=1;
      direction[1]=0;
    }else
    /*Deplacement à gauche*/
    if (touchePress==XK_Left && direction[0]==0){
      direction[0]=-1;
      direction[1]=0;
    }else
    /*Deplacement en haut*/
    if(touchePress==XK_Up && direction[1]==0){
      direction[0]=0;
      direction[1]=-1;
    }else
    /*Deplacement en bas*/
    if(touchePress==XK_Down && direction[1]==0){
      direction[0]=0;
      direction[1]=1;
    }
  }
}

void DeplacementSnake(int snake[TAILLE_SNAKE][2],int len_snake,int direction[2]){
  int i;

  for(i=len_snake-1;i>=0;i--){
    snake[i+1][0]=snake[i][0];/*actualisation nouvelle position des parties du serpent*/
    snake[i+1][1]=snake[i][1];
  }
  POS_X_HEAD_SNAKE=POS_X_HEAD_SNAKE+direction[0];
  POS_Y_HEAD_SNAKE=POS_Y_HEAD_SNAKE+direction[1]; 
}
int CheckCollisionBord(int snake[TAILLE_SNAKE][2]){
  /*******CHECK COLLISIONS BORDS TERRAIN*******/
  if(POS_X_HEAD_SNAKE==-1 || POS_X_HEAD_SNAKE==60){/*les bords x=0 ou x=610(pas 61 car on multiplie par 10 pour obtenir les réelles coordonnées*/
    FermerGraphique();
    return EXIT_SUCCESS;
  }
  if(POS_Y_HEAD_SNAKE==-1 || POS_Y_HEAD_SNAKE==40){/*les bords y=0 ou =410, car 400 appartient tjr au terrain de jeu*/
    FermerGraphique();
    return EXIT_SUCCESS;
  }
}
void CheckCollisionPomme(int len_pommes, int pommes[TAILLE_POMME][2], int snake[TAILLE_SNAKE][2], int* len_snake, int* score){
  /********CHECK POMME MIAMIAM*******/
  int i;
  for(i=0;i<len_pommes;i++){
    if(POS_X_HEAD_SNAKE==pommes[i][0] && POS_Y_HEAD_SNAKE==pommes[i][1]){
      *score+=5;
      placePomme(pommes, len_pommes,i,snake,*len_snake);
      *len_snake+=1;
    }
  }
}




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
    tempsDepart+=tempsTmp-Microsecondes();
    if(Microsecondes()>prochainDeplacement){
      DeplacementSnake(snake, len_snake, direction);
      CheckCollisionBord(snake);
      CheckCollisionPomme(len_pommes, pommes, snake, &len_snake, &score);
      prochainDeplacement=Microsecondes()+100000;
    }
  }
  FermerGraphique();

}

