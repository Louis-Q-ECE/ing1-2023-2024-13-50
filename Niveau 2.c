#include "bibl.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>

struct TimerData {
    int temps;
    int *stopTimerPtr;
    time_t startTime;
};

void nv2 (int ChoixBip) {
    int stopTimer = 0;
    int oiseauxRestant=4;
    struct Balle balle = {14, 8, 1, 1};
    time_t startTime = time(NULL);
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
            } else if (a == 1 && b == 1 || a == 10 && b == 1 || a == 1 && b == 20 || a == 10 && b == 20) {
                tab[a][b] = 3;
            }  else if (a == 1 && b == 1 || a == 10 && b == 1 || a == 1 && b == 20 || a == 10 && b == 20) {
                tab[a][b] = 3;
            } else if (a == 4 && b == 18) { // bloc poussable vers le haut
                tab[a][b] = 4;
            }else if (a == 8 && b == 8) { // bloc poussable vers le bas
                tab[a][b] = 10;
            } else if (a == 2 && b == 18) { // bloc poussable vers la droite
                tab[a][b] = 12;
            } else if (a==10 && b==7 ) { // bloc cassable
                tab[a][b] = 5;
            } else if (a == 9 && (b >= 1 && b <= 7) || (b == 1 && (a == 2 || a == 6 )) || a == 4 && b == 2 || (b == 19 && (a >= 5 && a <= 10))|| a == 1 && b == 17) { // bloc piégé
                tab[a][b] = 6;
            } else if ((b == 3 && (a >= 1 && a <= 7)) || (b == 5 && (a >= 2 && a <= 8)) || (b == 7 && (a >= 1 && a <= 7)) || (a == 3 && (b == 20 || b == 19 ))) { // blocs incassables
                tab[a][b] = 7;
            }else if (a == 7 && b == 3) { // bloc vie en plus
                tab[a][b] = 8;
            } else {
                tab[a][b] = 0;  // l'intérieur
            }
        }
    }
    while (vie > 0) {
        // Initialisation des données pour le thread du timer
        struct TimerData timerData;
        timerData.temps = 120;
        timerData.startTime = time(NULL);  // Initialisation ici

        // Création du thread du timer
        pthread_t timerThreadId;
        if (pthread_create(&timerThreadId, NULL, timerThread, (void *) &timerData) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread du timer.\n");
        }
        time_t currentTime = time(NULL);
        int elapsedSeconds = difftime(currentTime, startTime);


        // Boucle principale
        while (timerData.temps > 0 && !stopTimer) {
            system("cls");  // Efface l'écran
            currentTime = time(NULL);
            elapsedSeconds = difftime(currentTime, startTime);
            updateBalle(&balle);

            // Affichage du nombre de vies et d'oiseaux
            printf("Vies restantes : %d\n", vie);
            printf("nombres d'oiseaux restants %d\n", oiseauxRestant);
            printf("Temps restant : %02d:%02d\n", (timerData.temps - elapsedSeconds) / 60,
                   (timerData.temps - elapsedSeconds) % 60);
            int score = (120 - elapsedSeconds) * 100;


            // Affichage du plateau avec le personnage
            printf("Plateau du niveau :\n");
            for (int a = 0; a < 12; a++) {
                for (int b = 0; b < 22; b++) {
                    if (a == y && b == x) {
                        printf("♂");
                    } else {
                        if (a == balle.y && b == balle.x) {
                            printf("☺"); // Vous pouvez utiliser un autre caractère pour représenter la balle
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
                            } else if (tab[a][b] == 7) {
                                printf("☼");
                            } else if (tab[a][b] == 8) {
                                printf("♥");
                            } else {
                                printf(" ");
                            }
                        }
                    }

                }
                printf("\n");
            }



            // le joueur perd une vie si le temps est écoulé ou si le personnage touche un bloc piégé
            if (timerData.temps <= 0 || tab[y][x] == 6 || tab[x] == balle.x && tab[y] == balle.y) {
                vie--;
                printf("\nVous avez perdu une vie ! Vies restantes : %d\n", vie);
                sleep(1);  // faire une pause avant de reprendre
            } else if (vie == 0) {
                stopTimer = 1;
                pthread_join(timerThreadId, NULL);  // Attendre la fin du thread du timer
                EffacerEcran();
                GameOver();
                if (ChoixBip == 1) {
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
            char key;
            if (kbhit()) {
                key = getch();
            } else {
                sleep(1);
            }
            if (key == 'e') {
                pause();
            } else if (key == 'z' && y > 1 && tab[y - 1][x] != 7) {
                // Vérifiez si la case de destination n'est pas un bloc poussable
                if (tab[y - 1][x] != 4 && tab[y - 1][x] != 10 && tab[y - 1][x] != 11 && tab[y - 1][x] != 12) {
                    if (tab[y - 1][x] == 5) {
                        tab[y - 1][x] = 0;// Fait disparaître le bloc cassable
                        printf(" ");
                    } else if (tab[y - 1][x] == 3) {
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
                if (tab[y + 1][x] != 4 && tab[y + 1][x] != 10 && tab[y + 1][x] != 11 && tab[y + 1][x] != 12) {
                    if (tab[y + 1][x] == 5) {
                        tab[y + 1][x] = 0;// Fait disparaître le bloc cassable
                        printf(" ");
                    } else if (tab[y + 1][x] == 3) {
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
                if (tab[y][x - 1] != 4 && tab[y][x - 1] != 10 && tab[y][x - 1] != 11 && tab[y][x - 1] != 12) {
                    if (tab[y][x - 1] == 5) {
                        tab[y][x - 1] = 0; // Fait disparaître le bloc cassable
                        printf(" ");
                    } else if (tab[y][x - 1] == 3) {
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
                if (tab[y][x + 1] != 4 && tab[y][x + 1] != 10 && tab[y][x + 1] != 11 && tab[y][x + 1] != 12) {
                    if (tab[y][x + 1] == 5) {
                        tab[y][x + 1] = 0; // Fait disparaître le bloc cassable
                        printf(" ");
                    } else if (tab[y][x + 1] == 3) {
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
            if (oiseauxRestant == 0) {
                stopTimer = 1;
                pthread_join(timerThreadId, NULL);  // Attendre la fin du thread du timer

                char O, N;
                // lorsque le joueur ramasse tous les oiseaux
                printf("Vous avez gagné ! Vous allez accéder au niveau suivant.\n");
                printf("score est %d", score);

                pthread_join(timerThreadId, NULL);
                EffacerEcran();
                do {
                    printf("voulez-vous continuer ? O/N\n");
                    scanf(" %c", &O);
                    if (toupper(O) == 'O') {
                        EffacerEcran();
                        printf("vous accedez au niveau 2 !\n");
                        nv2(ChoixBip);
                    } else if (toupper(O) == 'N') {
                        menu(ChoixBip);
                    }
                } while (toupper(O) != 'N' && toupper(O) != 'O');
            }
        }

        sleep(1200);
        pthread_join(timerThreadId, NULL);

    }



}
