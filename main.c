#include <stdio.h>
#include "playfair.h"

int main()
{
    char key[100];
    char text[200];
    char prepared[200];
    int choice;

    printf("Kulcs: ");
    scanf("%s",key);

    generateMatrix(key);

    printf("\nMatrix:\n");
    printMatrix();

    while(1)
    {
        printf("\n1 - Titkosit\n");
        printf("2 - Visszafejt\n");
        printf("3 - Kilep\n");

        printf("Valasztas: ");
        scanf("%d",&choice);

        if(choice==3)
            break;

        printf("Szoveg: ");
        scanf("%s",text);

        prepareText(text,prepared);

        if(choice==1)
        {
            printf("Titkositott szoveg: ");
            encryptText(prepared);
        }

        else if(choice==2)
        {
            printf("Visszafejtett szoveg: ");
            decryptText(prepared);
        }
    }

    return 0;
}
