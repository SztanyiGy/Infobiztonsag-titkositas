#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char *key) {
    int used[26] = {0};
    int row = 0, col = 0;
    used['J' - 'A'] = 1; // J = I, ezert J-t kihagyjuk

    for(int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if(!isalpha(c)) continue;
        if(c == 'J') c = 'I';
        if(!used[c - 'A']) {
            matrix[row][col++] = c;
            used[c - 'A'] = 1;
            if(col == 5) { col = 0; row++; }
        }
    }
    for(char c = 'A'; c <= 'Z'; c++) {
        if(!used[c - 'A']) {
            matrix[row][col++] = c;
            if(col == 5) { col = 0; row++; }
        }
    }
}

void findPosition(char c, int *row, int *col) {
    if(c == 'J') c = 'I';
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
}

// FIX 1: J -> I csere hozzaadva
// FIX 2: nagyobb output tomb (400) a biztonságos X-beillesztéshez
void prepareText(char *input, char *output) {
    int j = 0;
    for(int i = 0; input[i]; i++) {
        if(isalpha(input[i])) {
            char c = toupper(input[i]);
            if(c == 'J') c = 'I'; // FIX 1
            output[j++] = c;
        }
    }
    output[j] = '\0';

    // Azonos betûpár szétválasztása X-szel
    for(int i = 0; i < j; i += 2) {
        if(output[i] == output[i + 1]) {
            if(j >= 398) break; // FIX 2: határellenõrzés
            for(int k = j; k > i + 1; k--)
                output[k] = output[k - 1];
            output[i + 1] = 'X';
            j++;
        }
    }

    // Páratlan hossz esetén X hozzáadása
    if(j % 2 != 0) {
        output[j++] = 'X';
    }
    output[j] = '\0';
}

// FIX 3: pointer alapú kimenet printf helyett -> visszafejtéshez is használható
void processPair(char a, char b, char *out1, char *out2, int mode) {
    int r1, c1, r2, c2;
    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if(r1 == r2) {
        // Azonos sor: jobbra (titkositas) / balra (visszafejtes)
        *out1 = matrix[r1][(c1 + mode + 5) % 5];
        *out2 = matrix[r2][(c2 + mode + 5) % 5];
    }
    else if(c1 == c2) {
        // Azonos oszlop: le (titkositas) / fel (visszafejtes)
        *out1 = matrix[(r1 + mode + 5) % 5][c1];
        *out2 = matrix[(r2 + mode + 5) % 5][c2];
    }
    else {
        // Teglalap: sarokcsere (mindket iranyban ugyanaz)
        *out1 = matrix[r1][c2];
        *out2 = matrix[r2][c1];
    }
}

void encrypt(char *prepared, char *output) {
    int len = strlen(prepared);
    for(int i = 0; i < len; i += 2)
        processPair(prepared[i], prepared[i+1], &output[i], &output[i+1], 1);
    output[len] = '\0';
}

// FIX 4: visszafejtes hozzaadva (mode = -1, azaz +4 mod 5)
void decrypt(char *cipher, char *output) {
    int len = strlen(cipher);
    for(int i = 0; i < len; i += 2)
        processPair(cipher[i], cipher[i+1], &output[i], &output[i+1], -1);
    output[len] = '\0';
}

void printFormatted(char *s) {
    for(int i = 0; s[i]; i++) {
        if(i > 0 && i % 2 == 0) printf(" ");
        printf("%c", s[i]);
    }
    printf("\n");
}

int main() {
    char key[100];
    char text[200];
    char prepared[400]; // FIX 2: nagyobb tomb
    char encrypted[400];
    char decrypted[400];

    printf("Kulcs: ");
    scanf("%s", key);
    printf("Szoveg: ");
    scanf(" %[^\n]", text);

    generateMatrix(key);

    printf("\nMatrix:\n");
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    prepareText(text, prepared);
    printf("\nElokeszitett szoveg: ");
    printFormatted(prepared);

    encrypt(prepared, encrypted);
    printf("Titkositott szoveg: ");
    printFormatted(encrypted);

    decrypt(encrypted, decrypted);
    printf("Visszafejtett szoveg: ");
    printFormatted(decrypted);

    return 0;
}
