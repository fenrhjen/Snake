#ifndef INIT_H
#define INIT_H
#include "constantes.h"

void initSnake(int snake[TAILLE_SNAKE][2],int len_snake);
void placePomme(int pommes[TAILLE_POMME][2], int len_pommes, int num, int snake[TAILLE_SNAKE][2], int len_snake);
void initPommes(int pommes[TAILLE_POMME][2], int len_pommes, int snake[TAILLE_SNAKE][2], int len_snake);

#endif 
