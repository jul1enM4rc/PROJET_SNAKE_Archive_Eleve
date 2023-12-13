#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"
#include "mesTypes.h"

/*===================================================================================
/ Nom Sémantique : FONCTION SP_Gestion_Clavier

/ Semantique : Gère la détection des événements clavier sur les touches de direction

/ Paramétres :
/ direction (OUT) - entier : Contient la direction sollicitée par l'utilisateur
/ DROITE = 0 , GAUCHE = 1 , BAS = 2 , HAUT = 3, ENTREE = 4 et -1 SINON
/ Pré-condition : AUCUNE
/ Post conditions : la direction vaut -1,0,1,2,3 4
/ ====================================================================================
/ Test : le chiffre renvoyé correspond à la direction appuyée
/ ====================================================================================*/

int SP_Gestion_Clavier()
{
    char direction;
    int dir;

    if (kbhit())
    {

        direction = getkey();

        switch (direction)
        {

        case KEY_UP:
            dir = HAUT;
            break;
        case KEY_DOWN:
            dir = BAS;
            break;
        case KEY_LEFT:
            dir = GAUCHE;
            break;
        case KEY_RIGHT:
            dir = DROITE;
            break;
        case KEY_ENTER:
            dir = ENTREE;
            break;
        }
    }
    else
    {
        dir = -1;
    }
    return dir;
}

/*===================================================================================
/ Nom Sémantique : FONCTION afficher_stade

/ Sémantique : Affiche dans la console le stade de jeu

/ Paramètres :
/ H (IN) - entier : Contient la hauteur du stade
/ L (IN) - entier : Contient la largeur du stade
/ couleur_fond (IN) - entier : Contient la couleur du stade
/ Pré-condition : H et L positifs; couleur de fond entre 1 et 16
/ Post conditions : AUCUNE
/ ====================================================================================
/ Test : le stade s'affiche selon plusieurs valeurs de hauteur, largeur et couleur
/ ====================================================================================*/

void SP_AFFICHER_STADE(int H, int L, int couleur_fond)
{
    cls();
    setColor(WHITE);
    for (int i = 0; i < L + 2; i++)
    {
        printf("#");
    }
    printf("\n");
    for (int y = 0; y < H; y++)
    {
        printf("#");
        for (int x = 0; x < L; x++)
        {
            printStadeElement(x + 2, y + 2, couleur_fond);
        }
        setColor(WHITE);
        printf("#\n");
    }
    for (int i = 0; i < L + 2; i++)
    {
        printf("#");
    }
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_AFFICHER_SERPENT

/ Sémantique : Affiche le serpent dans le stade

/ Paramètres :
/ serpent (IN) - ST_SNAKE : Serpent
/ couleur (IN) - entier : Couleur du serpent
/ Pré-condition : serpent initialisé
/ Post conditions : AUCUNE
/ ====================================================================================
/ Test : Le serpent s'affiche à la bonne position avec la bonne couleur
/ ====================================================================================*/

void SP_AFFICHER_SERPENT(ST_SNAKE serpent, int couleur)
{
    printSnakeHead(serpent.tete.x, serpent.tete.y, couleur);
    for (int i = 0; i < serpent.taille; i++)
    {
        printSnakeBody(serpent.pos[i].x, serpent.pos[i].y, couleur);
    }
}

/*===================================================================================
/ Nom Sémantique : PROCEDURE SP_AFFICHER_CADRE

/ Sémantique : Affiche le cadre contenant le score

/ Paramètres :
/ largeur (IN) - entier : Largeur du stade
/ Pré-condition : AUCUNE
/ Post conditions : AUCUNE
/ ====================================================================================
/ Test : Le cadre s'affiche à la bonne position pour chaque taille du stade
/ ====================================================================================*/

void SP_AFFICHER_CADRE(int largeur)
{
    gotoxy(largeur + 10, 5);
    setColor(RED);
    printf("###################### \n");
    gotoxy(largeur + 10, 6);
    printf("#                    # \n");
    gotoxy(largeur + 10, 7);
    printf("#   score =  0       # \n");
    gotoxy(largeur + 10, 8);
    printf("#                    # \n");
    gotoxy(largeur + 10, 9);
    printf("###################### \n");
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_CREER_POMME

/ Sémantique : Génère de nouvelles coordonnées pour une pomme et l'affiche

/ Paramètres :
/ pommes (IN/OUT) - ST_POMME[15] : Liste des pommes
/ index (IN) - entier : numéro de la pomme à générer
/ serpent (IN) - ST_SNAKE : serpent
/ hauteur (IN) - entier : hauteur du stade
/ largeur (IN) - entier : largeur du stade
/ murs (IN) - ST_MURS[800] : Liste des murs intérieurs
/ Pré-condition : index entre 0 et 14; serpent initialisé
/ Post conditions : nouvelles coordonées valides (ni dans murs, ni dans serpent ni dans autre pomme)
/ ====================================================================================
/ Test : Une pomme se crée dans un endroit sans murs, ni serpent, ni autre pomme
/ ====================================================================================*/

void SP_CREER_POMME(ST_POMME pommes[15], int index, ST_SNAKE serpent, int hauteur, int largeur, ST_MUR murs[800])
{
    /* Trouver des coordonnées aléatoires */
    int x_rand;
    int y_rand;
    do
    {
        x_rand = random() % largeur + 2;
        y_rand = random() % hauteur + 2;
    } while (SP_CONFLIT(x_rand, y_rand, serpent, pommes, murs));
    pommes[index].pos.x = x_rand;
    pommes[index].pos.y = y_rand;

    /* Afficher la pomme */
    printPomme(pommes[index].pos.x, pommes[index].pos.y, pommes[index].couleur);
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_CREER_MURS

/ Sémantique : Génère de nouvelles coordonnées pour un mur et l'affiche

/ Paramètres :
/ pommes (IN) - ST_POMME[15] : Liste des pommes
/ serpent (IN) - ST_SNAKE : serpent
/ hauteur (IN) - entier : hauteur du stade
/ largeur (IN) - entier : largeur du stade
/ murs (IN/OUT) - ST_MURS[800] : Liste des murs intérieurs
/ Pré-condition : serpent initialisé
/ Post conditions : nouvelles coordonées valides (ni dans autre murs, ni dans serpent ni dans  pomme)
/ ====================================================================================
/ Test : Un mur se crée dans un endroit sans autre murs, ni serpent, ni pomme
/ ====================================================================================*/

void SP_CREER_MURS(ST_POMME pommes[15], ST_SNAKE serpent, int hauteur, int largeur, ST_MUR murs[800])
{
    /* Trouver des coordonnées aléatoires */
    int x_rand;
    int y_rand;
    do
    {
        x_rand = random() % largeur + 2;
        y_rand = random() % hauteur + 2;
    } while (SP_CONFLIT(x_rand, y_rand, serpent, pommes, murs));
    murs[serpent.taille - 4].pos.x = x_rand;
    murs[serpent.taille - 4].pos.y = y_rand;

    /* Afficher la pomme */
    gotoxy(murs[serpent.taille - 4].pos.x, murs[serpent.taille - 4].pos.y);
    setColor(WHITE);
    printf("#");
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_CONFLIT

/ Sémantique : Verifie que les coordonnees fournies ne sont ni dans un mur, ni dans le serpent, ni dans une pomme

/ Paramètres :
/ x (IN) - entier : coordonnee horizontale
/ y (IN) - entier : coordonnee verticale
/ serpent (IN) - ST_SNAKE : serpent
/ pommes (IN) - ST_POMME[15] : Liste des pommes
/ murs (IN) - ST_MURS[800] : Liste des murs intérieurs
/ Pré-condition : serpent initialisé
/ Post conditions : nouvelles coordonées valides (ni dans autre murs, ni dans serpent ni dans  pomme)
/ ====================================================================================
/ Test :
/ ====================================================================================*/

int SP_CONFLIT(int x, int y, ST_SNAKE serpent, ST_POMME pommes[15], ST_MUR murs[800])
{
    /* element dans tete */
    if (x == serpent.tete.x && y == serpent.tete.y)
    {
        return 1;
    }
    /* element dans body */
    for (int i = 0; i < serpent.taille; i++)
    {
        if (x == serpent.pos[i].x && y == serpent.pos[i].y)
        {
            return 1;
        }
    }
    /* element dans pommes */
    for (int i = 0; i < 15; i++)
    {
        if (x == pommes[i].pos.x && y == pommes[i].pos.y)
        {
            return 1;
        }
    }
    /* element dans murs */
    for (int i = 0; i < serpent.taille - 4; i++)
    {
        if (x == murs[i].pos.x && y == murs[i].pos.y)
        {
            return 1;
        }
    }
    return 0;
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_DEPLACER_SERPENT

/ Sémantique : Met a jours les coordonnees des elements du serpent et les affiche

/ Paramètres :
/ serpent (IN/out) - ST_SNAKE : serpent
/ couleur_snake (IN) - entier : couleur du serpent
/ couleur_fond (IN) - entier : couleur du stade
/ Pré-condition : serpent initialisé, couleurs entre 0 et 15
/ Post conditions : aucune
/ ====================================================================================
/ Test : En exagérant le temps d'execution, le mouvement se fait comme prevu
/ ====================================================================================*/

void SP_DEPLACER_SERPENT(ST_SNAKE *serpent, int couleur_snake, int couleur_fond)
{
    /* deplacer la queue*/
    (*serpent).old_tail.x = (*serpent).pos[0].x;
    (*serpent).old_tail.y = (*serpent).pos[0].y;
    for (int t = 0; t < (*serpent).taille - 1; t++)
    {
        (*serpent).pos[t].x = (*serpent).pos[t + 1].x;
        (*serpent).pos[t].y = (*serpent).pos[t + 1].y;
    }
    (*serpent).pos[(*serpent).taille - 1].x = (*serpent).tete.x;
    (*serpent).pos[(*serpent).taille - 1].y = (*serpent).tete.y;
    printStadeElement((*serpent).old_tail.x, (*serpent).old_tail.y, couleur_fond);
    printSnakeBody((*serpent).tete.x, (*serpent).tete.y, couleur_snake);

    /* deplacer la tete*/
    switch ((*serpent).direction)
    {
    case DROITE:
        (*serpent).tete.x++;
        break;
    case BAS:
        (*serpent).tete.y++;
        break;
    case GAUCHE:
        (*serpent).tete.x--;
        break;
    case HAUT:
        (*serpent).tete.y--;
        break;
    }
    printSnakeHead((*serpent).tete.x, (*serpent).tete.y, couleur_snake);
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_OBSTACLE

/ Sémantique : Verifie si la tete du serpent est rentree dans un mur ou son propre corps

/ Paramètres :
/ serpent (IN) - ST_SNAKE : serpent
/ hauteur (IN) - entier : hauteur du stade
/ largeur (IN) - entier : largeur du stade
/ murs (IN) - ST_MURS[800] : Liste des murs intérieurs
/ Pré-condition : serpent initialisé
/ Post conditions : aucune
/ ====================================================================================
/ Test : retourne 1 en situation d'obstacle
/ ====================================================================================*/

int SP_OBSTACLE(ST_SNAKE serpent, int hauteur, int largeur, ST_MUR murs[800])
{
    // serpent dans bords
    if (serpent.tete.x == 1 || serpent.tete.x == largeur + 2 || serpent.tete.y == 1 || serpent.tete.y == hauteur + 2)
    {
        return 1;
    }
    // serpent dans corps
    for (int i = 0; i < serpent.taille; i++)
    {
        if (serpent.tete.x == serpent.pos[i].x && serpent.tete.y == serpent.pos[i].y)
        {
            return 1;
        }
    }
    // serpent dans mur
    for (int i = 0; i < serpent.taille - 3; i++)
    {
        if (serpent.tete.x == murs[i].pos.x && serpent.tete.y == murs[i].pos.y)
        {
            return 1;
        }
    }
    return 0;
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_POMME_TOUCHEE

/ Sémantique : Verifie si la tete du serpent est sur une pomme

/ Paramètres :
/ tete (IN) - ST_POINT : tete du serpent
/ pommes (IN) - ST_POMME[15] : Liste des pommes
/ Pré-condition : aucune
/ Post conditions : aucune
/ ====================================================================================
/ Test : retourne 1 quand le serpent heurte une pomme
/ ====================================================================================*/

int SP_POMME_TOUCHEE(ST_POINT tete, ST_POMME pomme)
{
    if (tete.x == pomme.pos.x && tete.y == pomme.pos.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*===================================================================================
/ Nom Sémantique : FONCTION SP_MANGER

/ Sémantique : Agrandit le serpent et affiche le nouveau bout de corps (lorsqu'une pomme est mangee)

/ Paramètres :
/ serpent (IN/OUT) - ST_SNAKE : serpent
/ couleur_snake (IN) - entier : couleur du serpent
/ Pré-condition : serpent initialisé, avec ancienne position de la queue stockee dans old_tail
/ Post conditions : aucune
/ ====================================================================================
/ Test : le serpent grandit lors d'un appel de cette fonction
/ ====================================================================================*/

void SP_MANGER(ST_SNAKE *serpent, int couleur_snake)
{
    for (int i = (*serpent).taille; i > 0; i--)
    {
        (*serpent).pos[i] = (*serpent).pos[i - 1];
    }
    (*serpent).pos[0] = (*serpent).old_tail;
    printSnakeBody((*serpent).pos[0].x, (*serpent).pos[0].y, couleur_snake);
    (*serpent).taille++;
}
