#include <stdio.h>
#include <Windows.h>
#include <unistd.h>
#include <stdlib.h>

void effacerEcran() {
    system("cls");  // Pour Windows
}

int main() {

    int ChoixBip = 2;
    int i;
    char MonAscii[16][1000];
    strcpy(MonAscii[0], "         _\n");
    strcpy(MonAscii[1], "        (:)_\n");
    strcpy(MonAscii[2], "      ,'    `.\n");
    strcpy(MonAscii[3], "     :        :\n");
    strcpy(MonAscii[4], "     |        |              ___\n");
    strcpy(MonAscii[5], "     |       /|    ______   // _\\\n");
    strcpy(MonAscii[6], "     ; -  _,' :  ,'      `. \\\\  -\\\n");
    strcpy(MonAscii[7], "    /          \\/          \\ \\\\  :\n");
    strcpy(MonAscii[8], "   (            :  ------.  `-'  |\n");
    strcpy(MonAscii[9], "____\\___    ____|______   \\______|_______\n");
    strcpy(MonAscii[10], "        |::|           '--`\n");
    strcpy(MonAscii[11], "        |::|\n");
    strcpy(MonAscii[12], "        |::|\n");
    strcpy(MonAscii[13], "        |::|\n");
    strcpy(MonAscii[14], "        |::;\n");
    strcpy(MonAscii[15], "        `:/\n");


    printf("Voulez-vous du son ? \n");

    do {
        printf("\n0 = muet    1 = son active \n");
        scanf("%d", &ChoixBip);
    } while (ChoixBip != 0 && ChoixBip != 1);

    for (i = 5; i < 21; i++) {
        usleep(150000); //obligé d'utiliser usleep car sleep pas assez précis
        if (ChoixBip == 1) {
            Beep(i * 100, 200);
        } else {
            usleep(200000); // pause assez longu
        }

        printf("%s", MonAscii[i - 5]);
    }
    effacerEcran();

//Déclaration des variables
    int option;
    int mdp;
    int temps;
    int scoretotal;
    int score1, score2, score3;
    int t1 = 5, t2 = 6, t3 = 7;

//initialisation des variables mdp1, mdp2, mdp3 qui respectivement ont la valeur
    int mdp1 = 1;
    int mdp2 = 2;
    int mdp3 = 3;


//nous affichons le menu disponible pour le joueur.
    printf("Menu principal : \n\n");
    printf("1)Regles du jeu\n");
    printf("2)Lancer un nouveau Jeu a partir du niveau 1\n");
    printf("3)Charger une partie\n");
    printf("4)Mot de passe\n");
    printf("5)Scores\n");
    printf("6)Quitter\n\n");
    printf("choisisssez une option entre 1 et 6.\n");
    scanf("%d", &option);


    //si le joueur appuie sur 1 alors les règles du jeu apparaissent.
    if (option == 1) {
        printf("-Initialement, le joueur possede 3 vies. \n\n");
        printf("-Chaque niveau devra etre resolu en moins de 120 secondes. Si le temps est ecoule, le joueur perd une \n"
               "vie et recommence le niveau Le but est de recuperer les 4 oiseaux du niveau sans se faire toucher par \n"
               "un obstacle \n\n");
    }

        //si le joueur appuie sur 2 alors il relancera un nouveau jeu donc une nouvelle partie qu'il devra ensuite sauvegardee
    else if (option == 2) {
        printf("Vous allez lancer un nouveau jeu a partir du niveau 1.\n");
        niv1();
    }

        //si le joueur appuie sur 3 alors il chargera sa partie qui a été sauvegardee
    else if (option == 3) {
        printf("Vous allez charger votre partie dernierement sauvegardee.\n");
    }

        // si le joeur appuie sur 4 il devra entrer un mot de passe, selon le mot de passe, il sera renvoyer vers le niveau 1,2 ou 3
    else if (option == 4) {
        printf("Entrer un mot de passe\n");
        scanf("%d", &mdp);
        if (mdp == mdp1) {
            printf("-vous allez jouer au niveau 1. \n\n");
        } else if (mdp == mdp2) {
            printf("-vous allez jouer au niveau 2 \n\n");
        } else if (mdp == mdp3) {
            printf("-vous allez jouer au niveau 3. \n\n");
        } else {
            printf("-votre mot de passe est incorect. \n\n");
        }

        // on affiche le score totale du joueur de cette maniere Sniveau = temps restant * 100
        //Au fur et à mesure des niveaux, les scores s'additionnent pour former le score final.
    } else if (option == 5) {
        score1 = t1 * 100;
        score2 = t2 * 100;
        score3 = t3 * 100;
        scoretotal = score1 + score2 + score3;
        scanf("%d", &scoretotal);
        printf("Votre score est : %d.\n", scoretotal);
    }

        // si le joueur appuie sur 6 il quittera le jeu.
    else if (option == 6) {
        printf("Vous avez decide de quitter le jeu, on vous attend pour une nouvelle aventure.\n");
        exit(0);
    } else {
        printf("veuillez taper un nombre entre 1 et 6\n");
    }
    return 0;
}
