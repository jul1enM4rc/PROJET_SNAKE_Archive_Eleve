#ifndef SP_GESTION_MENU_H_INCLUDED
#define SP_GESTION_MENU_H_INCLUDED

#include <stdio.h>
#include "mesTypes.h"

void SP_MENU_PRINCIPAL(int *);
void SP_MENU_PARAMETRE(ST_PARAM_JEU *);
void SP_MESSAGE_BIENVENUE(ST_JOUEUR *);
void SP_MESSAGE_PERDU(int);
void SP_INIT_PARAM(ST_PARAM_JEU *);

#endif // SP_GESTION_MENU_H_INCLUDED