#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int isCustomDelimiter(const char* numbers) {
    return numbers[0] == '/' && numbers[1] == '/';
}

static int findEndOfLine(const char* str) {
    const char* endOfLine = strchr(str, '\n');
    return endOfLine ? endOfLine - str : -1;
}

static void extractCustomDelimiter(const char* numbers, int endOfLinePos, char* delimiter) {
    strncpy(delimiter, numbers + 2, endOfLinePos - 2);
    delimiter[endOfLinePos - 2] = '\0';
}

static int parseDelimiter(const char* numbers, char* delimiter) {
    if (isCustomDelimiter(numbers)) {
        int endOfLinePos = findEndOfLine(numbers);
        if (endOfLinePos != -1) {
            extractCustomDelimiter(numbers, endOfLinePos, delimiter);
            return endOfLinePos + 1;
        }
    }
    strcpy(delimiter, ",");
    return 0;
}

static void extractNumberString(const char** str, const char* delimiters, char* numStr) {
    int numIndex = 0;
    while (**str && !strchr(delimiters, **str)) {
        if (isdigit(**str) || **str == '-') {
            numStr[numIndex++] = **str;
        }
        (*str)++;
    }
    numStr[numIndex] = '\0';
}

static void skipDelimiter(const char** str) {
    if (**str) {
        (*str)++;
    }
}

static int getNextNumber(const char** str, const char* delimiters) {
    char numStr[50];
    extractNumberString(str, delimiters, numStr);
    skipDelimiter(str);
    return atoi(numStr);
}

int parseDelimiter(const char* numbers, char* delimiter) {
    // Your implementation of parseDelimiter
    // This function extracts the delimiter from the input string
    // and returns the offset to the start of the numbers
    // For simplicity, assuming a basic implementation here
    strcpy(delimiter, ";"); // Placeholder
    return 0; // Placeholder
}

int getNextNumber(const char** ptr, const char* delimiters) {
    // Your implementation of getNextNumber
    // This function extracts the next number from ptr
    // using the provided delimiters
    // For simplicity, assuming a basic implementation here
    int number = strtol(*ptr, (char**)ptr, 10);
    while (**ptr && strchr(delimiters, **ptr)) (*ptr)++;
    return number;
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

    return sum;
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

