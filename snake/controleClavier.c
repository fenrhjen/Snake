#include "controleClavier.h"
#include <graph.h>
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
      CopierZone(1,0,0,0,60*TAILLE_CASE+2*BORD,40*TAILLE_CASE+BORD+40,0,0);
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
