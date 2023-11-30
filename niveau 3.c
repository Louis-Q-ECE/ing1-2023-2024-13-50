#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>
#include "nieveu 2.h"

void EffacerEcran() {
    system("cls");  // Pour Windows
}
//Déclaration des variables

int option;
int mdp0;
int temps;
int scoretotal;
int score1, score2, score3;
int t1 = 5, t2 = 6, t3 = 7;
char lettre ;
int oiseauxRestant = 4;
int vie = 3;  // Nombre initial de vies
//initialisation des variables mdp1, mdp2, mdp3 qui respectivement ont la valeur
int mdp1 = 1;
int mdp2 = 2;
int mdp3 = 3;







struct TimerData {
    int temps;
};

// Fonction de thread pour gérer le timer
void *timerThread(void *arg) {
    struct TimerData *timerData = (struct TimerData *)arg;

    while ((*timerData).temps > 0) {
        sleep(1);
        printf("\rTemps restant : %d secondes", (*timerData).temps);
        fflush(stdout);
        (*timerData).temps--;
    }
    printf("\nLe compte à rebours est terminé !\n");

    pthread_exit(NULL);
}

void win(){
    pthread_exit(NULL);
    char O,N;
    // lorsque le joueur ramasse tous les oiseaux
    printf("Vous avez gagné ! Vous allez accéder au niveau suivant.\n");
    EffacerEcran();
    printf("voulez-vous continuer ? O/N\n");
    scanf("%c,%c",&O,&N);
    if(N){

    }else{
        menu();

    }
}

void nv3() {
    int oiseauxRestant=4;
    int ChoixBip;
    SetConsoleOutputCP(65001);
    int tab[12][22];
    int x = 10, y = 5;
    int vie = 3;  // Nombre initial de vies

    // Initialisation du plateau
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22; b++) {
            if (a == 0 || a == 11) {
                tab[a][b] = 1;  // les bordures du toit et du plancher
            } else if (b == 0 || b == 21) {
                tab[a][b] = 2; // les bordures des murs
            } else if (a == 1 && b == 1 || a == 10 && b == 1 || a == 1 && b == 20|| a == 10 && b == 20 ) {
                tab[a][b] = 3;
            } else if ( a == 2 && b == 10 ) { // bloc poussable vers le haut
                tab[a][b] = 4;
            }else if (a == 6 && b == 7) { // bloc poussable vers le bas
                tab[a][b] = 10;
            }else if (a == 5 && b == 7 ) { // bloc poussable vers la gauche
                tab[a][b] = 11;
            } else if (a == 5 && b == 13 ) { // bloc poussable vers la droite
                tab[a][b] = 12;
            } else if ( a == 10 && b == 16 ||a == 4 && b == 7) { // bloc cassable
                tab[a][b] = 5;
            } else if ((a == 6 && (b >= 8 && b <= 12)) || (a == 4 && (b >= 8 && b <= 9)) || (a == 4 && (b >= 11 && b <= 12))|| (a >= 7 && a <= 10 && b == 8) || (a == 1 && (b == 4 || b == 8 || b == 12 || b == 16)) || (a == 2 && (b == 2 || b == 6 || b == 14 || b == 18))) { //bloc piégé
                tab[a][b] = 6;
            } else if ((a == 6 && b >= 14 && b <= 20)|| (a == 9 && b >= 1 && b <= 6) || (a == 3 && b >= 1 && b <= 9) || (a == 3 && b >= 11 && b <= 20) || (a == 9 && b >= 16 && b <= 20)) { // blocs incassables
                tab[a][b] = 7;
            }else {
                tab[a][b] = 0;  // l'intérieur
            }
        }
    }
    while (vie > 0) {
        // Initialisation des données pour le thread du timer
        struct TimerData timerData;
        timerData.temps = 120;

        // Création du thread du timer
        pthread_t timerThreadId;
        if (pthread_create(&timerThreadId, NULL, timerThread, (void *) &timerData) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread du timer.\n");
        }

        // Boucle principale
        while (timerData.temps > 0) {
            system("cls");  // Efface l'écran

            // Affichage du nombre de vies et d'oiseaux
            printf("Vies restantes : %d\n", vie);
            printf("nombres d'oiseaux restants %d\n", oiseauxRestant);


            // Affichage du plateau avec le personnage
            printf("Plateau du niveau :\n");
            for (int a = 0; a < 12; a++) {
                for (int b = 0; b < 22; b++) {
                    if (a == y && b == x) {
                        printf("♂");
                    } else {
                        if (tab[a][b] == 1) {
                            printf("-");
                        } else if (tab[a][b] == 2) {
                            printf("|");
                        } else if (tab[a][b] == 3) {
                            printf("♫");
                        } else if (tab[a][b] == 4) {
                            printf("↑");
                        } else if (tab[a][b] == 10) {
                            printf("↓");
                        } else if (tab[a][b] == 11) {
                            printf("←");
                        } else if (tab[a][b] == 12) {
                            printf("→");
                        } else if (tab[a][b] == 5) {
                            printf("♠");
                        } else if (tab[a][b] == 6) {
                            printf("♣");
                        }else if (tab[a][b] == 7) {
                            printf("▬");
                        } else {
                            printf(" ");
                        }
                    }
                }
                printf("\n");
            }



            // le joueur perd une vie si le temps est écoulé ou si le personnage touche un bloc piégé
            if (timerData.temps == 0 || tab[y][x] == 6) {
                vie--;
                printf("\nVous avez perdu une vie ! Vies restantes : %d\n", vie);
                sleep(1);  // faire une pause avant de reprendre
            } else if (vie == 0) {
                pthread_join(timerThreadId,NULL);
                EffacerEcran();
                if (ChoixBip == 1) {
                    pthread_join(timerThreadId,NULL);
                    Beep(600, 500);
                    usleep(100000);
                    Beep(500, 500);
                    usleep(100000);
                    Beep(400, 500);
                    usleep(100000);
                    Beep(300, 4000);


                }

                break;
            }



            // Code pour déplacer le personnage
            char key = getch();
            if (key == 'z' && y > 1 && tab[y - 1][x] != 7) {
                // Vérifiez si la case de destination n'est pas un bloc poussable
                if (tab[y - 1][x] != 4 && tab[y - 1][x] != 10 && tab[y - 1][x] != 11 && tab[y - 1][x] != 12 && tab[y - 1][x] != 7) {
                    if (tab[y - 1][x] == 5) {
                        tab[y - 1][x] = 0;// Fait disparaître le bloc cassable
                        printf(" ");
                    }else if (tab[y-1][x] == 3){
                        tab[y - 1][x] = 0;
                        printf(" ");// Fait disparaître l'oiseau
                        oiseauxRestant--;
                    }
                } else if (tab[y - 1][x] == 4) {
                    tab[y - 1][x] = 0;
                    tab[y - 2][x] = 4; // Déplace le bloc une case aprés dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 4) {
                        printf("↑");
                    }
                }
                y--;
            } else if (key == 's' && y < 10 && tab[y + 1][x] != 7) {
                // Vérifiez si la case de destination n'est pas un bloc poussable
                if (tab[y + 1][x] != 4 && tab[y + 1][x] != 10 && tab[y + 1][x] != 11 && tab[y + 1][x] != 12 && tab[y + 1][x] != 7) {
                    if (tab[y + 1][x] == 5) {
                        tab[y + 1][x] = 0;// Fait disparaître le bloc cassable
                        printf(" ");
                    }else if (tab[y+1][x] == 3){
                        tab[y + 1][x] = 0;
                        printf(" ");// Fait disparaître l'oiseau
                        oiseauxRestant--;
                    }

                } else if (tab[y + 1][x] == 10) {
                    tab[y + 1][x] = 0;
                    tab[y + 2][x] = 10; // Déplace le bloc une case après dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 10) {
                        printf("↓");
                    }
                }
                y++;
            } else if (key == 'q' && x > 1 && tab[y][x - 1] != 7) {
                // Vérifiez si la case de destination n'est pas un bloc poussable
                if (tab[y][x - 1] != 4 && tab[y][x - 1] != 10 && tab[y][x - 1] != 11 && tab[y][x - 1] != 12 && tab[y][x - 1] != 7) {
                    if (tab[y][x - 1] == 5) {
                        tab[y][x - 1] = 0; // Fait disparaître le bloc cassable
                        printf(" ");
                    }else if (tab[y][x - 1] == 3){
                        tab[y][x - 1] = 0;
                        printf(" ");// Fait disparaître l'oiseau
                        oiseauxRestant--;

                    }
                } else if (tab[y][x - 1] == 11) {
                    tab[y][x - 1] = 0;
                    tab[y][x - 2] = 11; // Déplace le bloc une case après dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 11) {
                        printf("←");
                    }
                }
                x--;

            } else if (key == 'd' && x < 20 && tab[y][x + 1] != 7) {
                // Vérifiez si la case de destination n'est pas un bloc poussable
                if (tab[y][x + 1] != 4 && tab[y][x + 1] != 10 && tab[y][x + 1] != 11 && tab[y][x + 1] != 12 && tab[y][x + 1] != 7) {
                    if (tab[y][x + 1] == 5) {
                        tab[y][x + 1] = 0; // Fait disparaître le bloc cassable
                        printf(" ");
                    }else if (tab[y][x + 1] == 3){
                        tab[y][x + 1] = 0;
                        printf(" ");// Fait disparaître l'oiseau
                        oiseauxRestant--;

                    }
                } else if (tab[y][x + 1] == 12) {
                    tab[y][x + 1] = 0;
                    tab[y][x + 2] = 12; // Déplace le bloc une case après dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 12) {
                        printf("→");
                    }
                }
                x++;
            }
            if(oiseauxRestant==0){
                pthread_join(timerThreadId,NULL);
                win();

            }
        }
        sleep(1200);
        pthread_join(timerThreadId, NULL);

    }



}
