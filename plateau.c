#include <stdio.h>
#include <conio.h>
#include <windows.h>

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
    }retun 0;
}
int main() {
    int bx = 0; // Position en x du point
    int by = 0; // Position en y du point

    while (1) {
        system("cls"); // Effacer l'écran sur Windows

        // Afficher le point à la position actuelle
        for (int i = 0; i < by; i++) {
            printf("\n");
        }
        for (int i = 0; i < bx; i++) {
            printf(" ");
        }
        printf("o\n");

        if (_kbhit()) {

            char touche = _getch(); // Récupérer la touche enfoncée

            // Déplacer le point en fonction de la touche
            switch (touche) {
                case 'w':
                    by--;
                    break;
                case 's':
                    by++;
                    break;
                case 'a':
                    bx--;
                    break;
                case 'd':
                    bx++;
                    break;
                case 'q':
                    return 0; // Quitter le programme si 'q' est enfoncé
            }
        }
    }

    return 0;
}



            
        }
        printf("\n");
    }

    return 0;
}





