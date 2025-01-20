#include "conversion.h"

// f - 0 | j - 1 | l - 2 | b - 3
int orientationCharToInt(char c) {
    int rv;
    switch (c) {
        case 'f':
            rv = 0;
            break;
        case 'j':
            rv = 1;
            break;
        case 'l':
            rv = 2;
            break;
        case 'b':
            rv = 3;
            break;
    }

    return rv;
}

// c - 0 | a - 1
int rotationCharToInt(char c) {
    int rv;
    if (c == 'c') {
        rv = 0;
    }
    else {
        rv = 1;
    }
    return rv;
}

// f - 0 | j - 1 | l - 2 | b - 3
char orientationIntToChar(int n) {
    char rv;
    switch (n) {
        case 0:
            rv = 'f';
            break;
        case 1:
            rv = 'j';
            break;
        case 2:
            rv = 'l';
            break;
        case 3:
            rv = 'b';
            break;
    }
    return rv;
}

// c - 0 | a - 1
char rotationIntToChar(int n) {
    char rv;
    if (n == 0) {
        rv = 'c';
    }
    else {
        rv = 'a';
    }
    return rv;
}