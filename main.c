
#include "bibl.h"
#include <stdio.h>
int main() {
    int ChoixBip = 2;

    do {
        printf("Voulez-vous du son ? \n");
        printf("\n0 = muet    1 = son active \n");
        scanf("%d", &ChoixBip);
        EffacerEcran();
    } while (ChoixBip != 0 && ChoixBip != 1);
    snoopy(ChoixBip);
    menu(ChoixBip);
}
