#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_MENU.h"
#include "SP_GESTION_JEU.h"
#include "SP_GESTION_IA.h"
#include "mesTypes.h"

int get_tableau(int tableau[20][40])
{
    int valeur = 1;
    for (int y = 0; y < 10; y++)
    {
        for (int x = 1; x < 40; x++)
        {
            tableau[2 * y][x] = valeur;
            valeur++;
        }
        for (int x = 39; x > 0; x--)
        {
            tableau[2 * y + 1][x] = valeur;
            valeur++;
        }
    }
    for (int y = 19; y >= 0; y--)
    {
        tableau[y][0] = valeur;
        valeur++;
    }
}

int SP_GET_DIR(ST_SNAKE serpent, ST_POMME pommes[15], int tableau[20][40], int nb_pomme)
{
    int pos_pomme[nb_pomme];
    for (int i = 0; i < nb_pomme; i++)
    {
        pos_pomme[i] = tableau[pommes[i].pos.y - 2][pommes[i].pos.x - 2];
    }
    int direction = -1;

    int pos_tete = tableau[serpent.tete.y - 2][serpent.tete.x - 2];
    int pos_queue = tableau[serpent.pos[0].y - 2][serpent.pos[0].x - 2];
    int pos_obj = pos_tete;
    int new_obj;
    int bon;

    // HAUT
    if (serpent.tete.y > 2)
    {
        new_obj = tableau[serpent.tete.y - 3][serpent.tete.x - 2];
        if (new_obj > pos_obj && abs(new_obj - pos_tete) < abs(new_obj - pos_queue))
        {
            bon = 1;
            for (int i = 0; i < nb_pomme; i++)
            {
                if (pos_tete < pos_pomme[i] && pos_pomme[i] < new_obj)
                {
                    bon = 0;
                }
            }
            if (bon)
            {
                pos_obj = new_obj;
                direction = HAUT;
            }
        }
    }

    // BAS
    if (serpent.tete.y < 21)
    {
        new_obj = tableau[serpent.tete.y - 1][serpent.tete.x - 2];
        if (new_obj > pos_obj && abs(new_obj - pos_tete) < abs(new_obj - pos_queue))
        {
            bon = 1;
            for (int i = 0; i < nb_pomme; i++)
            {
                if (pos_tete < pos_pomme[i] && pos_pomme[i] < new_obj)
                {
                    bon = 0;
                }
            }
            if (bon)
            {
                pos_obj = new_obj;
                direction = BAS;
            }
        }
    }

    // GAUCHE
    if (serpent.tete.x > 2)
    {
        new_obj = tableau[serpent.tete.y - 2][serpent.tete.x - 3];
        if (new_obj > pos_obj && abs(new_obj - pos_tete) < abs(new_obj - pos_queue))
        {

            bon = 1;
            for (int i = 0; i < nb_pomme; i++)
            {
                if (pos_tete < pos_pomme[i] && pos_pomme[i] < new_obj)
                {
                    bon = 0;
                }
            }
            if (bon)
            {
                pos_obj = new_obj;
                direction = GAUCHE;
            }
        }
    }

    // DROITE
    if (serpent.tete.x < 40)
    {
        new_obj = tableau[serpent.tete.y - 2][serpent.tete.x - 1];
        if ((new_obj > pos_obj && abs(new_obj - pos_tete) < abs(new_obj - pos_queue)) || new_obj == 1)
        {
            bon = 1;
            for (int i = 0; i < nb_pomme; i++)
            {
                if (pos_tete < pos_pomme[i] && pos_pomme[i] < new_obj)
                {
                    bon = 0;
                }
            }
            if (bon)
            {
                pos_obj = new_obj;
                direction = DROITE;
            }
        }
    }
    return direction;
}