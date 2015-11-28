#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "constantes.h"

void ChargerImageArg(int x, int y, char* file, int xx, int yy, int l, int h);
void printTerrain(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes);
void printTime(unsigned long int time, unsigned long int tempsActuel);
void printScore(int score);
void printScreen(int snake[TAILLE_SNAKE][2], int len_snake, int pommes[TAILLE_POMME][2], int len_pommes, unsigned long int time,unsigned long int tempsActuel, int score);


#endif 
