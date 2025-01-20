#include "user.h"

void welcome() {
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("|  Spiral Matrix Generator  |\n");
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
}

int getNum(int lower, int upper, const char* message1, const char* message2) {
    int choice;
    int rv;
    while (1) {
        printf("%s", message1);
        rv = scanf("%d", &choice);
        if (rv == EOF) {
            printf("\n");
            return -1;
        }
        else if (rv != 1 || choice < lower || choice > upper) {
            printf("%s", message2);
            int c;
            while ((c = getchar()) != EOF && (c != '\n'));
        }
        else {
            break;
        }
    }
    return choice;
}

char getChar(const char* correctChars, const char* message1, const char* message2) {
    char choice;
    int rv;
    while (1) {
        printf("%s", message1);
        rv = scanf("%c", &choice);
        if (rv == EOF) {
            printf("\n");
            return '\0';
        }
        else {
            int isInCorrectChars = 0;
            int i = 0;
            while (!isInCorrectChars && correctChars[i] != '\0') {
                if (correctChars[i] == choice) {
                    isInCorrectChars = 1;
                }
                else {
                    i++;
                }
            }
            if (rv != 1 || !isInCorrectChars) {
                printf("%s", message2);
                int c;
                while ((c = getchar()) != EOF && (c != '\n'));
            }
            else {
                break;
            }
        }
    }
    return choice;
}

int choice() {
    printf(" =-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    printf("0 - Hasznalati utmutato\n");
    printf("1 - Matrix generalasa\n");
    printf("2 - Matrix mentese\n");
    printf("3 - Matrix betoltese\n");
    printf("4 - Matrix kiirasa\n");
    printf("5 - Kilepes\n");
    printf("\n =-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    return getNum(0,5,"Valasztas >> ", "Nincs ilyen menupont. Valassz ervenyes menupontot!\n");
}

void userGuide() {
    printf("Ez egy spiral matrixokat generalo program.\n\n");
    printf("Hasznalati utmutato:\n");
    printf("\tMenupont valasztasa:\n");
    printf("\t\tValasztani a 0-5 gombok megnyomasaval tudsz.\n");
    printf("\tHasznalati utmutato:\n");
    printf("\t\tA menuben a '0' gomb megnyomasaval lehet elerni.\n");
    printf("\tMatrix generalasa:\n");
    printf("\t\tA menuben az '1' gomb megnyomasaval lehet elerni.\n");
    printf("\t\tAdd meg a matrix meretet! (1-20)\n");
    printf("\t\tAdd meg, hogy milyen iranyba induljon el a spiral! ('f' - fel | 'j' - jobbra | 'l' - le | 'b' - balra)\n");
    printf("\t\tAdd meg, hogy milyen legyen a forgasi irany! ('c' - oramutato jarasaval megegyezo | 'a' - oramutato jarasaval ellentetes)\n");
    printf("\tMatrix mentese:\n");
    printf("\t\tA menuben a '2' gomb megnyomasaval lehet elerni.\n");
    printf("\t\tAz aktualisan betoltott matrix kiirasra kerul egy kulso file-ba.\n");
    printf("\tMatrix betoltese:\n");
    printf("\t\tA menuben a '3' gomb megnyomasaval lehet elerni.\n");
    printf("\t\tAdd meg a file nevet, ahonnan szeretnel egy matrixot betolteni!\n");
    printf("\tMatrix kiirasa:\n");
    printf("\t\tA menuben a '4' gomb megnyomasaval lehet elerni.\n");
    printf("\t\tAz akutalisan betoltott matrix kiirodik a kepernyore.\n");
    printf("\tKilepes:\n");
    printf("\t\tA menuben az '5' gomb megnyomasaval lehet elerni.\n");
    printf("\t\tKilep a programbol. A betoltott, de nem mentett matrix elveszik.\n\n");
}

void menu() {
    int size;
    char orientation;
    char rotation;
    int rv;
    char fileName[50];
    SpiralMatrix* spiralMatrix = NULL;
    while (1) {
        int n = choice();
        printf("\n");
        switch (n) {
            case 0:
                userGuide();
                break;
            case 1:
                spiralMatrix = freeMatrix(spiralMatrix);
                size = getNum(1,20,"Meret: ", "Nem megfelelo meret!\n");
                getchar();
                orientation = getChar("fjlb","Indulasi irany: ", "Nem megfelelo irany!\n");
                getchar();
                rotation = getChar("ca", "Forgasi irany: ", "Nem megfelelo forgasi irany!\n");
                if (size == -1 || orientation == '\0' || rotation == '\0') {
                    exit(1);
                }
                spiralMatrix = generateMatrix(size, orientationCharToInt(orientation), rotationCharToInt(rotation));
                fillMatrix(spiralMatrix);
                if (spiralMatrix == NULL) {
                    printf("Nem sikerult legeneralni a matrixot!\n");
                }
                else {
                    printf("A matrix sikeresen le lett generalva!\n");
                }
                printf("\n");
                break;
            case 2:
                rv = saveMatrix(spiralMatrix);
                if (!rv) {
                    printf("Nem lehet menteni, mert nincsen betoltott matrix!\n");
                }
                else {
                    printf("A matrix sikeresen el lett mentve!\n");
                }
                printf("\n");
                break;
            case 3:
                printf("File neve: ");
                rv = scanf("%s", fileName);
                if (rv == EOF) {
                    printf("\n");
                    exit(1);
                }
                FILE* file = fopen(fileName, "r");
                if (file == NULL) {
                    printf("A file nem talalhato!\n");
                }
                else {
                    spiralMatrix = freeMatrix(spiralMatrix);
                    spiralMatrix = loadMatrix(fileName);
                    printf("A matrix sikeresen be lett toltve!\n");
                    fclose(file);
                }
                printf("\n");
                break;
            case 4:
                rv = printMatrix(spiralMatrix, stdout);
                if (!rv) {
                    printf("Nem lehet kiirni, mert nincsen betoltott matrix!\n");
                }
                printf("\n");
                break;
            case 5:
                freeMatrix(spiralMatrix);
                exit(0);
                break;
            default:
                exit(1);
        }
    } 
}