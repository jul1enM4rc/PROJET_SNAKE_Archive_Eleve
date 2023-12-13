#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_MENU.h"
#include "SP_GESTION_JEU.h"
#include "mesTypes.h"

/*===================================================================================
/ Nom Sémantique : FONCTION SP_MENU_PRINCIPAL

/ Semantique : Affiche le menu principal et gère l'interaction avec l'utilisateur

/ Paramètres :
/ choix (IN/OUT) - entier : Contient le choix de l'action decidée dans le menu principal
/ Pré-condition : le choix vaut 1,2,3,4
/ Post conditions : le choix vaut 1,2,3,4
/ ====================================================================================
/ Test : Le menu s'affiche bien et le choix renvoyé correspond à celui selectionné
/ ====================================================================================*/
void SP_MENU_PRINCIPAL(int *choix)
{
    cls();
    int touche = 0;
    while (touche != 4)
    {
        if (touche != -1)
        {
            gotoxy(1, 1);
            setColor(GREY);
            printf("*************************************************************************\n");
            printf("*                                                                       *\n");
            printf("*");
            setColor(GREEN);
            printf("   ,d8888b.                        888                                 ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  d88P  Y88b                       888                                 ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("   Y88b.                           888                                 ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("    Y888b.     88888b.     8888b.  888  888   .d88b.                   ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("       8Y88b.  888  88b       88b  888 .88P  d8P  Y8b                  ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("         888b  888  888  .d888888  888888K   88888888                  ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("   Y88b  d88P  888  888  888  888  888  88b  Y8b.                      ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("     Y8888P    888  888   Y888888  888  888   Y8888P                   ");
            setColor(GREY);
            printf("*\n");
            printf("*                                                                       *\n");
            printf("*     __________________________________________________                *\n");
            printf("*    |                                                  |               *\n");
            printf("*    |     Que voulez-vous faire?                       |               *\n");
            printf("*    |                                                  |               *\n");
            printf("*    |          1.  ");
            if (*choix == 1)
            {
                setColor(LIGHTBLUE);
            }
            printf("Jouer");
            setColor(GREY);
            printf("                               |               *\n");
            printf("*    |          2.  ");
            if (*choix == 2)
            {
                setColor(LIGHTBLUE);
            }
            printf("Parametres");
            setColor(GREY);
            printf("                          |               *\n");
            printf("*    |          3.  ");
            if (*choix == 3)
            {
                setColor(LIGHTBLUE);
            }
            printf("Highscore");
            setColor(GREY);
            printf("                           |               *\n");
            printf("*    |          4.  ");
            if (*choix == 4)
            {
                setColor(LIGHTBLUE);
            }
            printf("Quitter");
            setColor(GREY);
            printf("                             |               *\n");
            printf("*    |__________________________________________________|               *\n");
            printf("*                                                                       *\n");
            printf("*************************************************************************\n");
        }
        touche = SP_Gestion_Clavier();
        if (touche == 3 && *choix > 1)
        {
            *choix -= 1;
        }
        else if (touche == 2 && *choix < 4)
        {
            *choix += 1;
        }
    }
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_MENU_PARAMETRE

/ Semantique : Affiche le menu des paramètres et gère l'interaction avec l'utilisateur

/ Paramètres :
/ parametre (IN/OUT) - ST_PARAM_JEU : Contient les parametres du jeu initialisé dans le main
/ Pré-condition : parametre initialisé
/ Post conditions : attribut de parametre cohérent
/ ====================================================================================
/ Test : Le menu s'affiche bien et les parametres renvoyés correspondent à ceux selectionnés
/ ====================================================================================*/
void SP_MENU_PARAMETRE(ST_PARAM_JEU *parametre)
{
    cls();
    int touche = 0;
    int selection = 0;
    while (touche != 4)
    {
        if (touche != -1)
        {
            gotoxy(1, 1);
            setColor(GREY);
            printf("***************************************************************************************\n");
            printf("*");
            setColor(GREEN);
            printf("  8888888b.                                                 888                      ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888   Y88b                                                888                      ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888    888                                                888                      ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888   d88P 8888b.  888d888 8888b.  88888b.d88b.   .d88b.  888888 888d888 .d88b.    ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  8888888P       88b 888P        88b 888  888  88b d8P  Y8b 888    888P   d8P  Y8b   ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888       .d888888 888    .d888888 888  888  888 88888888 888    888    88888888   ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888       888  888 888    888  888 888  888  888 Y8b.     Y88b.  888    Y8b.       ");
            setColor(GREY);
            printf("*\n*");
            setColor(GREEN);
            printf("  888        Y888888 888     Y888888 888  888  888   Y8888    Y888 888      Y8888    ");
            setColor(GREY);
            printf("*\n");
            printf("*                                                                                     *\n");
            printf("*     ________________________________________________________________                *\n");
            printf("*    |                                                                |               *\n");
            printf("*    |     Modification Des Parametres: (entree pour revenir)         |               *\n");
            printf("*    |                                                                |               *\n");
            printf("*    |       a) ");
            if (selection == 0)
            {
                setColor(LIGHTBLUE);
            }
            printf("Couleur du serpent");
            setColor((*parametre).couleur_snake);
            printf("         ******0");
            setColor(GREY);
            printf("                    |               *\n");
            printf("*    |       b) ");
            if (selection == 1)
            {
                setColor(LIGHTBLUE);
            }
            printf("Couleur du stade");
            setColor((*parametre).couleur_stade);
            printf("           #######");
            setColor(GREY);
            printf("                    |               *\n");
            printf("*    |       c) ");
            if (selection == 2)
            {
                setColor(LIGHTBLUE);
            }
            printf("Difficulte");
            setColor(GREY);
            if ((*parametre).difficulte == 1)
            {
                setColor(LIGHTGREEN);
            }
            printf("        facile");
            setColor(GREY);
            if ((*parametre).difficulte == 2)
            {
                setColor(LIGHTGREEN);
            }
            printf("    moyen");
            setColor(GREY);
            if ((*parametre).difficulte == 3)
            {
                setColor(LIGHTGREEN);
            }
            printf("    difficile");
            setColor(GREY);
            printf("        |               *\n");
            printf("*    |       d) ");
            if (selection == 3)
            {
                setColor(LIGHTBLUE);
            }
            printf("Dimensions");
            setColor(GREY);
            if ((*parametre).H_stade == 15)
            {
                setColor(LIGHTGREEN);
            }
            printf("         petit");
            setColor(GREY);
            if ((*parametre).H_stade == 20)
            {
                setColor(LIGHTGREEN);
            }
            printf("    moyen");
            setColor(GREY);
            if ((*parametre).H_stade == 25)
            {
                setColor(LIGHTGREEN);
            }
            printf("    grand");
            setColor(GREY);
            printf("            |               *\n");
            printf("*    |       e) ");
            if (selection == 4)
            {
                setColor(LIGHTBLUE);
            }
            printf("Nombre de pomme   ");
            setColor(GREY);
            for (int i = 1; i < 16; i++)
            {
                if ((*parametre).nb_pommes == i)
                {
                    setColor(LIGHTGREEN);
                }
                printf("%i ", i);
                setColor(GREY);
            }
            setColor(GREY);
            printf("|               *\n");
            printf("*    |       f) ");
            if (selection == 5)
            {
                setColor(LIGHTBLUE);
            }
            printf("Generation de murs");
            setColor(GREY);
            if ((*parametre).murs == 0)
            {
                setColor(LIGHTGREEN);
            }
            printf("         off");
            setColor(GREY);
            if ((*parametre).murs == 1)
            {
                setColor(LIGHTGREEN);
            }
            printf("         on");
            setColor(GREY);
            printf("             |               *\n");
            printf("*    |       g) ");
            if (selection == 6)
            {
                setColor(LIGHTBLUE);
            }
            printf("Mode de jeu (beta)");
            setColor(GREY);
            if ((*parametre).IA == 0)
            {
                setColor(LIGHTGREEN);
            }
            printf("         Joueur");
            setColor(GREY);
            if ((*parametre).IA == 1)
            {
                setColor(LIGHTGREEN);
            }
            printf("    Ordinateur");
            setColor(GREY);
            printf("       |               *\n");
            printf("*    |________________________________________________________________|               *\n");
            printf("*                                                                                     *\n");
            printf("***************************************************************************************\n");
        }
        touche = SP_Gestion_Clavier();
        if (touche == 3 && selection > 0)
        {
            selection -= 1;
        }
        else if (touche == 2 && selection < 6)
        {
            selection += 1;
        }
        else if (touche == 0)
        {
            switch (selection)
            {
            case 0:
                if ((*parametre).couleur_snake < 15)
                {
                    (*parametre).couleur_snake += 1;
                }
                break;
            case 1:
                if ((*parametre).couleur_stade < 15)
                {
                    (*parametre).couleur_stade += 1;
                }
                break;
            case 2:
                if ((*parametre).difficulte < 3)
                {
                    (*parametre).difficulte += 1;
                }
                break;
            case 3:
                if ((*parametre).H_stade < 25)
                {
                    (*parametre).H_stade += 5;
                    (*parametre).L_stade += 10;
                }
                break;
            case 4:
                if ((*parametre).nb_pommes < 15)
                {
                    (*parametre).nb_pommes += 1;
                }
                break;
            case 5:
                if ((*parametre).murs == 0)
                {
                    (*parametre).murs += 1;
                }
                break;
            case 6:
                if ((*parametre).IA == 0)
                {
                    (*parametre).IA += 1;
                    (*parametre).murs = 0;
                }
                break;
            default:
                break;
            }
        }
        else if (touche == 1)
        {
            switch (selection)
            {
            case 0:
                if ((*parametre).couleur_snake > 0)
                {
                    (*parametre).couleur_snake -= 1;
                }
                break;
            case 1:
                if ((*parametre).couleur_stade > 0)
                {
                    (*parametre).couleur_stade -= 1;
                }
                break;
            case 2:
                if ((*parametre).difficulte > 1)
                {
                    (*parametre).difficulte -= 1;
                }
                break;
            case 3:
                if ((*parametre).H_stade > 15)
                {
                    (*parametre).H_stade -= 5;
                    (*parametre).L_stade -= 10;
                }
                break;
            case 4:
                if ((*parametre).nb_pommes > 1)
                {
                    (*parametre).nb_pommes -= 1;
                }
                break;
            case 5:
                if ((*parametre).murs == 1)
                {
                    (*parametre).murs -= 1;
                }
                break;
            case 6:
                if ((*parametre).IA == 1)
                {
                    (*parametre).IA -= 1;
                }
                break;
            default:
                break;
            }
        }
    }
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_MESSAGE_BIENVENUE

/ Semantique : Affiche le message de bienvenue et demande le nom du joueur

/ Paramétres :
/ joueur (IN/OUT) - ST_JOUEUR* : Pointe vers le joueur
/ Pré-condition : AUCUNE
/ Post conditions : le joueur a un nom
/ ====================================================================================
/ Test : le nom du joueur est mit a jour
/ ====================================================================================*/
void SP_MESSAGE_BIENVENUE(ST_JOUEUR *joueur)
{
    /*--------- Message Bienvenue ---------*/
    setColor(GREEN);
    printf("########################################## \n");
    printf("#     Bienvenue dans le jeu de Snake     # \n");
    printf("########################################## \n");

    setColor(YELLOW);
    gotoxy(10, 5);
    printf("Quel est votre nom?    ");
    scanf("%s", (*joueur).nom);
    printf("\n Bienvenue %s, a vous de jouer !!! \n", (*joueur).nom);

    gotoxy(1, 9);
    setColor(RED);
}

/*===================================================================================
/ Nom Sémantique : PROCEDURE SP_MESSAGE_PERDU

/ Semantique : Affiche l'encadre indiquant la fin de la partie, avec le score

/ Paramétres :
/ score (IN) - entier : Score realise
/ Pré-condition : AUCUNE
/ Post conditions : AUCUN
/ ====================================================================================
/ Test : le chiffre renvoyé correspond é la direction appuyée
/ ====================================================================================*/
void SP_MESSAGE_PERDU(int score)
{
    cls();
    setColor(WHITE);
    printf("******************************************************\n");
    printf("*  ");
    setColor(RED);
    printf("8888888b.                        888              ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888   Y88b                       888              ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888    888                       888              ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888   d88P  .d88b.  888d888  .d88888 888  888     ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("8888888P   d8P  Y8b 888P    d88  888 888  888     ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888        88888888 888     888  888 888  888     ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888        Y8b.     888     Y88b 888 Y88b 888     ");
    setColor(WHITE);
    printf("*\n*  ");
    setColor(RED);
    printf("888          Y8888  888       Y88888   Y88888     ");
    setColor(WHITE);
    printf("*\n");
    printf("*    ____________________________________________    *\n");
    printf("*   |                                            |   *\n");
    printf("*   |   Score :                                  |   *\n");
    printf("*   |                                            |   *\n");
    printf("*   |____________________________________________|   *\n");
    printf("*                                                    *\n");
    printf("******************************************************\n");
    gotoxy(20, 12);
    printf("%i", score);
    while (SP_Gestion_Clavier() != 4)
    {
        msleep(10);
    }
    cls();
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_INIT_PARAM

/ Semantique : Initialise les parametres du jeu

/ Paramétres :
/ parametres (IN/OUT) - ST_PARAM_JEU* : stocke les parametres du jeu
/ Pré-condition : AUCUNE
/ Post conditions : les parametres sont ceux de bases
/ ====================================================================================
/ Test : les parametres sont bien initialise au bonne valeurs
/ ====================================================================================*/
void SP_INIT_PARAM(ST_PARAM_JEU *parametres)
{
    (*parametres).couleur_snake = 3;
    (*parametres).couleur_stade = 0;
    (*parametres).difficulte = 2;
    (*parametres).H_stade = 20;
    (*parametres).L_stade = 40;
    (*parametres).nb_pommes = 1;
    (*parametres).murs = 0;
    (*parametres).IA = 0;
}
