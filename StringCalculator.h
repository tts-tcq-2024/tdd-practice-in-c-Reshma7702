#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parseDelimiter(const char* numbers, char* delimiter) {
    // Simplified implementation for demo purposes
    strcpy(delimiter, ";"); // Placeholder
    return 0; // Placeholder
}

int getNextNumber(const char** ptr, const char* delimiters) {
    // Simplified implementation for demo purposes
    int number = strtol(*ptr, (char**)ptr, 10);
    while (**ptr && strchr(delimiters, **ptr)) (*ptr)++;
    return number;
}

void handleNegativeNumbers(int negatives[], int negCount) {
    if (negCount > 0) {
        printf("Negatives not allowed: ");
        for (int i = 0; i < negCount; ++i) {
            printf("%d ", negatives[i]);
        }
        printf("\n");
    }
}

void updateSumAndNegatives(int number, int* sum, int negatives[], int* negCount) {
    if (number < 0) {
        negatives[(*negCount)++] = number;
    } else if (number <= 1000) {
        *sum += number;
    }
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
        updateSumAndNegatives(number, &sum, negatives, &negCount);
    }

    handleNegativeNumbers(negatives, negCount);

    return negCount > 0 ? -1 : sum;
}
