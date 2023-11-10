#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>


int main () {
    int tab[12][22];



    // Initialisation de la matrice
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22; b++) {
            if (a == 0 || a == 11) {
                tab[a][b] = 1;  //  les bordures du toit et du plancher
            } else if (b == 0 || b == 21) {
                tab[a][b] = 2; // les bordures des murs
            } else if (a == 1 && b == 1 || a == 10 && b == 1 || a == 1 && b == 20 || a == 10 && b == 20) {
                tab[a][b] = 3;
            } else if (a == 2 && b == 4 || a == 2 && b == 5 || a == 2 && b == 6 || a == 2 && b == 6) { // bloc poussable
                tab[a][b] = 4;
            } else if (a == 6 && b == 11 || a == 7 && b == 11 || a == 8 && b == 11 ||
                       a == 8 && b == 11) { //bloc cassable
                tab[a][b] = 5;
            } else if (a == 8 && b == 12 || a == 9 && b == 12 || a == 5 && b == 4 || a == 5 && b == 5) { //bloc cassable
                tab[a][b] = 6;
            } else {
                tab[a][b] = 0;  // l'intérieur
            }
        }
    }

    char character = 'P';
    int x = 10, y = 5; // Position de départ du personnage
    while (1) {
        system("cls");  // Efface l'écran

        // Affichage de la matrice avec le personnage
        printf("plateau du niveau :\n");
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


        // code pour deplacer le personnage
        char key = getch();

        if (key == 'z' && y > 1) {
            if (tab[y - 1][x] == 3) {
                tab[y - 1][x] = 0; // Fait disparaître le "A" si le personnage passe dessus
                if (tab[x][y] == 0) {
                    printf(" ");
                }
            }
            y--;
        } else if (key == 's' && y < 10) {
            if (tab[y + 1][x] == 3) {
                tab[y + 1][x] = 0; // Fait disparaître le "A" si le personnage passe dessus
                if (tab[x][y] == 0) {
                    printf(" ");
                }
            }
            y++;
        } else if (key == 'q' && x > 1) {
            if (tab[y][x - 1] == 3) {
                tab[y][x - 1] = 0; // Fait disparaître le "A" si le personnage passe dessus
                if (tab[x][y - 1] == 0) {
                    printf(" ");
                }
            }
            x--;
        } else if (key == 'd' && x < 20) {
            if (tab[y][x + 1] == 3) {
                tab[y][x + 1] = 0; // Fait disparaître le "A" si le personnage passe dessus
                if (tab[x][y] == 0) {
                    printf(" ");
                }
            }
            x++;
        }

    }
}
