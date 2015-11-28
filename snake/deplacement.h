#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include "constantes.h"
void DeplacementSnake(int snake[TAILLE_SNAKE][2],int len_snake,int direction[2]);
int CheckCollisionBord(int snake[TAILLE_SNAKE][2],int* done);
void CheckCollisionPomme(int len_pommes, int pommes[TAILLE_POMME][2], int snake[TAILLE_SNAKE][2], int* len_snake, int* score);
void CheckCollisionQueue(int snake[TAILLE_SNAKE][2],int len_snake, int* done);
#endif
