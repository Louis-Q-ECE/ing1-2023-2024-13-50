#include <stdio.h>


    int main() {
        int matrice[22][12];

        // Initialisation de la matrice
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 12; j++) {
                matrice[i][j] = 0;
            }
        }


        // création du toit
        matrice[0][0]=1;
        matrice[0][1]=1;
        matrice[0][2]=1;
        matrice[0][3]=1;
        matrice[0][4]=1;
        matrice[0][5]=1;
        matrice[0][6]=1;
        matrice[0][7]=1;
        matrice[0][8]=1;
        matrice[0][9]=1;
        matrice[0][10]=1;
        matrice[0][11]=5;


        // création du plancher
        matrice[21][0]=4;
        matrice[21][1]=4;
        matrice[21][2]=4;
        matrice[21][3]=4;
        matrice[21][4]=4;
        matrice[21][5]=4;
        matrice[21][6]=4;
        matrice[21][7]=4;
        matrice[21][8]=4;
        matrice[21][9]=4;
        matrice[21][10]=4;
        matrice[21][11]=4;


        // création du mur gauche
        matrice[1][0]=2;
        matrice[2][0]=2;
        matrice[3][0]=2;
        matrice[4][0]=2;
        matrice[5][0]=2;
        matrice[6][0]=2;
        matrice[7][0]=2;
        matrice[8][0]=2;
        matrice[9][0]=2;
        matrice[10][0]=2;
        matrice[11][0]=2;
        matrice[12][0]=2;
        matrice[13][0]=2;
        matrice[14][0]=2;
        matrice[15][0]=2;
        matrice[16][0]=2;
        matrice[17][0]=2;
        matrice[18][0]=2;
        matrice[19][0]=2;
        matrice[20][0]=2;
        matrice[21][0]=2;

        // création du mur droit
        matrice[1][11]=3;
        matrice[2][11]=3;
        matrice[3][11]=3;
        matrice[4][11]=3;
        matrice[5][11]=3;
        matrice[6][11]=3;
        matrice[7][11]=3;
        matrice[8][11]=3;
        matrice[9][11]=3;
        matrice[10][11]=3;
        matrice[11][11]=3;
        matrice[12][11]=3;
        matrice[13][11]=3;
        matrice[14][11]=3;
        matrice[15][11]=3;
        matrice[16][11]=3;
        matrice[17][11]=3;
        matrice[18][11]=3;
        matrice[19][11]=3;
        matrice[20][11]=3;
        matrice[21][11]=3;




        // Affichage des bordures
        printf("niveau 1 :\n");
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 12; j++) {
                if (matrice[i][j] == 1) {
                    printf("-\t");
                }else if (matrice[i][j] == 3) {
                    printf("|\t\n");
                } else if (matrice[i][j] == 2) {
                    printf("|\t");
                } else if (matrice[i][j] == 4) {
                    printf("-\t");
                } else if (matrice[i][j] == 5) {
                    printf("-\n");
                }else {
                    printf("\t");
                }
            }
        }
        return 0;
    }
