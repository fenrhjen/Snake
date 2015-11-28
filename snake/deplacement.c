#include "deplacement.h"
#include "constantes.h"
#include "init.h"


void DeplacementSnake(int snake[TAILLE_SNAKE][2],int len_snake,int direction[2]){
  int i;

  for(i=len_snake-1;i>=0;i--){
    snake[i+1][0]=snake[i][0];/*actualisation nouvelle position des parties du serpent*/
    snake[i+1][1]=snake[i][1];
  }
  POS_X_HEAD_SNAKE=POS_X_HEAD_SNAKE+direction[0];
  POS_Y_HEAD_SNAKE=POS_Y_HEAD_SNAKE+direction[1]; 
}
int CheckCollisionBord(int snake[TAILLE_SNAKE][2],int* done){
  /*******CHECK COLLISIONS BORDS TERRAIN*******/
  if(POS_X_HEAD_SNAKE==-1 || POS_X_HEAD_SNAKE==60){/*les bords x=0 ou x=610(pas 61 car on multiplie par 10 pour obtenir les réelles coordonnées*/
    *done=1;
  }
  if(POS_Y_HEAD_SNAKE==-1 || POS_Y_HEAD_SNAKE==40){/*les bords y=0 ou =410, car 400 appartient tjr au terrain de jeu*/
    *done=1;
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
void CheckCollisionQueue(int snake[TAILLE_SNAKE][2],int len_snake, int* done){
  int i;
  for(i=1;i<len_snake;i++){
    if(POS_X_HEAD_SNAKE==snake[i][0] && POS_Y_HEAD_SNAKE==snake[i][1])
      *done=1;
  }
}
