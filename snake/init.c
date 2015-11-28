#include "init.h"
#include "constantes.h"


void initSnake(int snake[TAILLE_SNAKE][2],int len_snake){
  int i;
  for (i=0; i<len_snake; i++){
    snake[i][0]=30;
    snake[i][1]=20+i;
  }
}


void initPommes(int pommes[TAILLE_POMME][2], int len_pommes, int snake[TAILLE_SNAKE][2], int len_snake){
  int i;
  for (i=0; i<len_pommes; i++) placePomme(pommes, len_pommes, i, snake, len_snake);
}


void placePomme(int pommes[TAILLE_POMME][2], int len_pommes, int num, int snake[TAILLE_SNAKE][2], int len_snake){
  int isOnSomething, i;
  do{
    isOnSomething=0;/*vaut 1 si la pomme aléatoire est soit sur le snake soit sur une autre pomme*/

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
