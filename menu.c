#include "bibl.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>


int option;
int scoretotal;
int score1, score2, score3;
int t1 = 5, t2 = 6, t3 = 7;
char lettre ;


//initialisation des variables mdp1, mdp2, mdp3 qui respectivement ont la valeur
int mdp1 = 1;
int mdp2 = 2;
int mdp3 = 3;
int mdp0;


void regles(){
    printf("-Initialement, le joueur possede 3 vies. \n\n");
    printf("-Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, le joueur perd une \n"
           "vie et recommence le niveau. Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par \n"
           "un obstacle \n\n");
}

void mdp(int ChoixBip){
    printf("Entrer un mot de passe\n");
    scanf("%d", &mdp0);
    if (mdp0 == mdp1) {
        printf("-vous allez jouer au niveau 1. \n\n");
        nv1(ChoixBip);
    } else if (mdp0 == mdp2) {
        printf("-vous allez jouer au niveau 2 \n\n");
        nv2(ChoixBip);
    } else if (mdp0 == mdp3) {
        printf("-vous allez jouer au niveau 3. \n\n");
        nv3(ChoixBip);
    } else {
        printf("-votre mot de passe est incorect. \n\n");
    }
}

void score(){
    // on affiche le score total du joueur de cette maniere Sniveau = temps restant * 100
    score1 = t1 * 100;
    score2 = t2 * 100;
    score3 = t3 * 100;

    //Au fur et à mesure des niveaux, les scores s'additionnent pour former le score final.
    scoretotal = score1 + score2 + score3;
    scanf("%d", &scoretotal);
    printf("Votre score est : %d.\n", scoretotal);
    sleep(15);
}

void quitter(){
    printf("Vous avez decide de quitter le jeu, on vous attend pour une nouvelle aventure.\n");
    exit(0);
}
void menu(int ChoixBip) {

    //nous affichons le menu disponible pour le joueur.
    do {
        printf("Menu principal : \n\n");
        printf("1)Regles du jeu\n");
        printf("2)Lancer un nouveau Jeu a partir du niveau 1\n");
        printf("3)Charger une partie\n");
        printf("4)Mot de passe\n");
        printf("5)Scores\n");
        printf("6)Quitter\n\n");
        printf("choisisssez une option entre 1 et 6.\n");
        scanf("%d", &option);
        system("cls");
    } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6);


    //si le joueur appuie sur 1 alors les règles du jeu apparaissent.
    if (option == 1) {
        regles();
        printf("pour retourner dans le menu taper : o \n");
        lettre = getch();

        if (lettre == 'o') {
            do {
                EffacerEcran();
                printf("Menu principal : \n\n");
                printf("1)Lancer un nouveau Jeu a partir du niveau 1\n");
                printf("2)Charger une partie\n");
                printf("3)Mot de passe\n");
                printf("4)Scores\n");
                printf("5)Quitter\n\n");
                printf("choisisssez une option entre 1 et 5.\n");
                scanf("%d", &option);
                EffacerEcran();
            } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);

            if (option == 1) {
                printf("Vous allez lancer un nouveau jeu a partir du niveau 1.\n");
                nv1(ChoixBip);
            } else if (option == 2) {
                printf("Vous allez charger votre partie dernierement sauvegardee.\n");
            } else if (option == 3) {
                mdp(ChoixBip);
            } else if (option == 4) {
                score();
            }
        }
    }


        //si le joueur appuie sur 2 alors, il relancera un nouveau jeu donc une nouvelle partie qu'il devra ensuite sauvegardée
    else if (option == 2) {
        printf("Vous allez lancer un nouveau jeu a partir du niveau 1.\n");
        nv1(ChoixBip);
    }

        //si le joueur appuie sur 3 alors, il chargera sa partie qui a été sauvegardée
    else if (option == 3) {
        printf("Vous allez charger votre partie dernierement sauvegardee.\n");

    }

        // si le joueur appuie sur 4 il devra entrer un mot de passe, selon le mot de passe, il sera renvoyer vers le niveau 1,2 ou 3
    else if (option == 4) {
        mdp(ChoixBip);

    } else if (option == 5) {
        score();
    }
        // si le joueur appuie sur 6 il quittera le jeu.
    else if (option == 6) {
        quitter();
    }
}
