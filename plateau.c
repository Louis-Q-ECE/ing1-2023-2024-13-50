#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>zdsdz
#include <math.h>
#include <conio.h>


int main (){
    int matrice[12][22];

    // Initialisation de la matrice
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22; b++) {
            if (a == 0 || a == 11) {
                matrice[a][b] = 1;  //  les bordures du toit et du plancher
            }else if (b == 0 || b == 21) {
                matrice[a][b] = 2; // les bordures des murs
            }else if (a==1 && b==1 || a==10 && b==1 || a==1 && b==20 || a==10 && b==20){
                matrice[a][b] = 3;
            }
            else {
                matrice[a][b] = 0;  // l'intérieur
            }
        }
    }// affichage de la matrice

    char character = 'P';
    int x = 10, y = 5; // Position de départ du personnage

    printf("plateau du niveau :\n");
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22 ;b++) {
            if (matrice[a][b] == 1) {
                printf("-");
            }else if (matrice[a][b] == 2){
                printf("|");

            }else if (matrice[a][b] == 3){
                printf("A");
            }else {
                printf(" ");
            }
        }
        printf("\n");
    }
    while (1) {
        system("cls");  // Efface l'écran (pour Windows)

        // Affichage de la matrice avec le personnage
        printf("plateau du niveau :\n");
        for (int a = 0; a < 12; a++) {
            for (int b = 0; b < 22; b++) {
                if (a == y && b == x) {
                    printf("%c", character);
                } else {
                    if (matrice[a][b] == 1) {
                        printf("-");
                    } else if (matrice[a][b] == 2) {
                        printf("|");
                    } else if (matrice[a][b] == 3) {
                        printf("A");
                    } else {
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }

        char key = getch();

        if (key == 'z' && y > 1) {
            y--;
        } else if (key == 's' && y < 10) {
            y++;
        } else if (key == 'q' && x > 1) {
            x--;
        } else if (key == 'd' && x < 20) {
            x++;
        }
    }
}








