
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>

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


int main() {
    SetConsoleOutputCP(65001);
    int tab[12][22];
    char character = 'S';
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
            } else if (a == 2 && b == 4 || a == 2 && b == 5 || a == 2 && b == 6 || a == 2 && b == 6) { // bloc poussable
                tab[a][b] = 4;
            } else if (a == 6 && b == 11 || a == 7 && b == 11 || a == 8 && b == 11 || a == 8 && b == 11) { // bloc cassable
                tab[a][b] = 5;
            } else if (a == 8 && b == 12 || a == 9 && b == 12 || a == 5 && b == 4 || a == 5 && b == 5) { // bloc piégé
                tab[a][b] = 6;
            } else {
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

            // Affichage du nombre de vies
            printf("Vies restantes : %d\n", vie);


            // Affichage du plateau avec le personnage
            printf("Plateau du niveau :\n");
            for (int a = 0; a < 12; a++) {
                for (int b = 0; b < 22; b++) {
                    if (a == y && b == x) {
                        printf("%c", character);
                    } else {
                        if (tab[a][b] == 1) {
                            printf("-");
                        } else if (tab[a][b] == 2) {
                            printf("|");
                        } else if (tab[a][b] == 3) {
                            printf("A");
                        } else if (tab[a][b] == 4) {
                            printf("#");
                        } else if (tab[a][b] == 5) {
                            printf("0");
                        } else if (tab[a][b] == 6) {
                            printf("&");
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
            }else if (vie == 0) {   // le joueur a perdu si il n'aplus de vie
                printf("\ngame over\n");
                break;
            }


            // Code pour déplacer le personnage
            char key = getch();
            if (key == 'z' && y > 1) {
                if (tab[y - 1][x] == 3 || tab[y - 1][x] == 5) {
                    tab[y - 1][x] = 0; // Fait disparaître le "A" et le bloc cassable
                    if (tab[x][y] == 0) {
                        printf(" ");
                    }
                } else if (tab[y - 1][x] == 4) {
                    tab[y - 1][x] = 0; // Fait disparaître le bloc "#"
                    tab[y - 2][x] = 4; // Déplace le bloc "#" une case avant dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 4) {
                        printf("#");
                    }
                }
                y--;
            } else if (key == 's' && y < 10) {
                if (tab[y + 1][x] == 3 || tab[y + 1][x] == 5) {
                    tab[y + 1][x] = 0; // Fait disparaître le "A" et le bloc cassable
                    if (tab[x][y] == 0) {
                        printf(" ");
                    }
                } else if (tab[y + 1][x] == 4) {
                    tab[y + 1][x] = 0; // Fait disparaître le bloc "#"
                    tab[y + 2][x] = 4; // Déplace le bloc "#" une case après dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 4) {
                        printf("#");
                    }
                }
                y++;
            } else if (key == 'q' && x > 1) {
                if (tab[y][x - 1] == 3 || tab[y][x - 1] == 5) {
                    tab[y][x - 1] = 0; // Fait disparaître le "A" et le bloc cassable
                    if (tab[x][y - 1] == 0) {
                        printf(" ");
                    }
                } else if (tab[y][x - 1] == 4) {
                    tab[y][x - 1] = 0; // Fait disparaître le bloc "#"
                    tab[y][x - 2] = 4; // Déplace le bloc "#" une case avant dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 4) {
                        printf("#");
                    }
                }
                x--;
            } else if (key == 'd' && x < 20) {
                if (tab[y][x + 1] == 3 || tab[y][x + 1] == 5) {
                    tab[y][x + 1] = 0; // Fait disparaître le "A" et le bloc cassable
                    if (tab[x][y] == 0) {
                        printf(" ");
                    }
                } else if (tab[y][x + 1] == 4) {
                    tab[y][x + 1] = 0; // Fait disparaître le bloc "#"
                    tab[y][x + 2] = 4; // Déplace le bloc "#" une case après dans la direction du déplacement
                    if (tab[x][y] == 0) {
                        printf(" ");
                    } else if (tab[x][y] == 4) {
                        printf("#");
                    }
                }
                x++;
            }
        }
        pthread_join(timerThreadId, NULL);

    }
}
