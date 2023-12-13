#include <stdio.h>
#include "myLib.h"
#include "mesTypes.h"
#include <math.h>
#include <unistd.h>
#include "SP_GESTION_JEU.h"
#include "SP_GESTION_MENU.h"
#include "SP_GESTION_IA.h"

int main()
{
    /*--------- Initialisation elements ---------*/
    ST_PARAM_JEU parametres;
    SP_INIT_PARAM(&parametres);

    ST_SNAKE serpent;

    ST_JOUEUR joueur;

    ST_POMME pommes[15];
    for (int i = 0; i < 15; i++)
    {
        pommes[i].couleur = 4;
    }

    ST_MUR murs[400];

    /*--------- Initialisation fichier Highscore ---------*/
    char nom_fichier[60];
    sprintf(nom_fichier, "Highscores/highscore_vitesse_%d_taille_%d_nb_pommes_%d_murs_%d.txt", parametres.difficulte, parametres.H_stade / 5 - 2, parametres.nb_pommes, parametres.murs);
    FILE *highscore_file;

    /*--------- Message Bienvenue ---------*/
    cls();
    SP_MESSAGE_BIENVENUE(&joueur);

    /*--------- Initialisation variable d'etat ---------*/
    int choix = 1;

    int perdu = 0;
    int new_dir;

    int tableau[20][40];

    while (choix != 4)
    {
        SP_MENU_PRINCIPAL(&choix);
        switch (choix)
        {
        case 1: // { LANCER JEU }
            /*--------- Creer Serpent ---------*/
            hidecursor();
            serpent.direction = DROITE;
            serpent.tete.x = 7;
            serpent.tete.y = parametres.H_stade / 2;
            serpent.taille = 4;
            for (int i = 0; i < 4; i++)
            {
                serpent.pos[i].x = 3 + i;
                serpent.pos[i].y = serpent.tete.y;
            }

            SP_AFFICHER_STADE(parametres.H_stade, parametres.L_stade, parametres.couleur_stade);
            SP_AFFICHER_SERPENT(serpent, parametres.couleur_snake);
            for (int i = 0; i < parametres.nb_pommes; i++)
            {
                SP_CREER_POMME(pommes, i, serpent, parametres.H_stade, parametres.L_stade, murs);
            }
            for (int i = 0; i < 400; i++)
            {
                murs[i].pos.x = 0;
                murs[i].pos.y = 0;
            }
            SP_AFFICHER_CADRE(parametres.L_stade);
            int perdu = 0;
            int new_dir;

            get_tableau(tableau);

            while (SP_Gestion_Clavier() == -1)
            {
                msleep(10);
            }

            while (perdu == 0)
            {
                fflush(stdin);
                if (!parametres.IA)
                {
                    new_dir = SP_Gestion_Clavier();
                } else {
                    new_dir = SP_GET_DIR(serpent, pommes, tableau, parametres.nb_pommes);
                }

                if (new_dir > -1 && new_dir < 4 && (new_dir + serpent.direction) != 1 && (new_dir + serpent.direction) != 5)
                {
                    serpent.direction = new_dir;
                }
                SP_DEPLACER_SERPENT(&serpent, parametres.couleur_snake, parametres.couleur_stade);
                if (SP_OBSTACLE(serpent, parametres.H_stade, parametres.L_stade, murs))
                {
                    perdu = 1;

                    SP_MESSAGE_PERDU(serpent.taille - 4);

                    int score_lu;
                    char line[20];

                    if (access(nom_fichier, F_OK) != -1)
                    {
                        highscore_file = fopen(nom_fichier, "r");
                        for (int i = 0; i < 8; i++)
                        {
                            fgets(line, 20, highscore_file);
                        }
                        fclose(highscore_file);
                        score_lu = atoi(line);
                    }
                    else
                    {
                        score_lu = -1;
                    }

                    if (score_lu < serpent.taille - 4)
                    {
                        highscore_file = fopen(nom_fichier, "wt");
                        fprintf(highscore_file, "========== Highscore ==========\n\nNom du joueur:\n%s\n\nScore:\n%i\n\n===============================", joueur.nom, serpent.taille - 4);
                        fclose(highscore_file);
                    }
                }
                for (int i = 0; i < parametres.nb_pommes; i++)
                {
                    if (SP_POMME_TOUCHEE(serpent.tete, pommes[i]))
                    {
                        SP_MANGER(&serpent, parametres.couleur_snake);
                        SP_CREER_POMME(pommes, i, serpent, parametres.H_stade, parametres.L_stade, murs);
                        gotoxy(parametres.L_stade + 23, 7);
                        printf("%i", serpent.taille - 4);
                        if (parametres.murs == 1)
                        {
                            SP_CREER_MURS(pommes, serpent, parametres.H_stade, parametres.L_stade, murs);
                        }
                    }
                }
                msleep(200 / (pow(2, parametres.difficulte - (serpent.direction / 2))));
            }
            break;
        case 2: // { MODIFIER PARAMETRES }
            SP_MENU_PARAMETRE(&parametres);
            sprintf(nom_fichier, "Highscores/highscore_vitesse_%d_taille_%d_nb_pommes_%d_murs_%d.txt", parametres.difficulte, parametres.H_stade / 5 - 2, parametres.nb_pommes, parametres.murs);
            break;
        case 3: // { AFFICHER HIGHSCORE }
            cls();
            FILE *scores;
            scores = fopen(nom_fichier, "r");
            char line[256];
            while (fgets(line, 256, scores))
            {
                printf("%s", line);
            }
            while (SP_Gestion_Clavier() != 4)
            {
                msleep(10);
            }
            cls();
            break;
        case 4: // { QUITTER }
            break;
        default:
            break;
        }
    }
    return 0;
}
