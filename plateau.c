#include <stdio.h>

int main() {
    int matrice[12][22];

    // Initialisation de la matrice
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22; b++) {
            if (a == 0 || a == 11) {
                matrice[a][b] = 1;  //  les bordures du toit et du plancher
            }else if (b == 0 || b == 21) {
                matrice[a][b] = 2; // les bordures des murs
            }else {
                matrice[a][b] = 0;  // l'intérieur
            }
        }
    }

    // Affichage de la matrice
    printf("plateau du niveau :\n");
    for (int a = 0; a < 12; a++) {
        for (int b = 0; b < 22 ;b++) {
            if (matrice[a][b] == 1) {
                printf("-");
            }else if (matrice[a][b] == 2){
                printf("|");

            }else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}





