#ifndef SP_JEU_H_INCLUDED
#define SP_JEU_H_INCLUDED

#include <stdio.h>
#include "mesTypes.h"

int SP_Gestion_Clavier();
void SP_AFFICHER_STADE(int, int, int);
void SP_AFFICHER_SERPENT(ST_SNAKE, int);
void SP_CREER_POMME(ST_POMME *, int, ST_SNAKE, int, int, ST_MUR *);
void SP_CREER_MURS(ST_POMME *, ST_SNAKE, int, int, ST_MUR *);
int SP_CONFLIT(int, int, ST_SNAKE, ST_POMME *, ST_MUR *);
void SP_DEPLACER_SERPENT(ST_SNAKE *, int, int);
int SP_OBSTACLE(ST_SNAKE, int, int, ST_MUR *);
int SP_POMME_TOUCHEE(ST_POINT, ST_POMME);
void SP_MANGER(ST_SNAKE *, int);
void SP_AFFICHER_CADRE(int);

#endif // SP_JEU_H_INCLUDED
