#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include "spiralmatrix.h"
#include "conversion.h"

void welcome();
int getNum(int lower, int upper, const char* message1, const char* message2);
char getChar(const char* correctChars, const char* message1, const char* message2);
int choice();
void userGuide();
void menu();

#endif