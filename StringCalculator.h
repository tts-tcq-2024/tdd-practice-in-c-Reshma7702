#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

int add(const char* numbers);

#endif // STRINGCALCULATOR_H

#include "StringCalculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int parseDelimiter(const char* numbers, char* delimiter) {
    if (numbers[0] == '/' && numbers[1] == '/') {
        const char* endOfLine = strchr(numbers, '\n');
        if (endOfLine) {
            strncpy(delimiter, numbers + 2, endOfLine - numbers - 2);
            delimiter[endOfLine - numbers - 2] = '\0';
            return endOfLine - numbers + 1;
        }
    }
    strcpy(delimiter, ",");
    return 0;
}

static int getNextNumber(const char** str, const char* delimiters) {
    char numStr[50];
    int numIndex = 0;
    while (**str && !strchr(delimiters, **str)) {
        if (isdigit(**str) || **str == '-') {
            numStr[numIndex++] = **str;
        }
        (*str)++;
    }
    if (**str) (*str)++;
    numStr[numIndex] = '\0';
    return atoi(numStr);
}

int add(const char* numbers) {
    if (numbers == NULL || strlen(numbers) == 0) {
        return 0;
    }

    char delimiter[50];
    int offset = parseDelimiter(numbers, delimiter);

    const char* ptr = numbers + offset;
    char delimiters[100] = ",\n";
    strcat(delimiters, delimiter);

    int sum = 0;
    int negatives[100];
    int negCount = 0;

    while (*ptr) {
        int number = getNextNumber(&ptr, delimiters);
        if (number < 0) {
            negatives[negCount++] = number;
        } else if (number <= 1000) {
            sum += number;
        }
    }

    if (negCount > 0) {
        printf("negatives not allowed:");
        for (int i = 0; i < negCount; ++i) {
            printf(" %d", negatives[i]);
        }
        printf("\n");
        return -1;
    }

    return sum;
}

