#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Helper function to set default delimiters
void setDefaultDelimiters(char* delimiter) {
    strcpy(delimiter, ",\n");
}

// Helper function to check if custom delimiter is present
int hasCustomDelimiter(const char* numbers) {
    return numbers[0] == '/' && numbers[1] == '/';
}

// Helper function to extract custom delimiter
int extractCustomDelimiter(const char* numbers, char* delimiter) {
    const char* end = strchr(numbers, '\n');
    if (end != NULL) {
        strncpy(delimiter, numbers + 2, end - numbers - 2);
        delimiter[end - numbers - 2] = '\0';
        return end - numbers + 1;
    }
    return 0;
}

// Function to parse the delimiter
int parseDelimiter(const char* numbers, char* delimiter) {
    setDefaultDelimiters(delimiter);
    if (hasCustomDelimiter(numbers)) {
        return extractCustomDelimiter(numbers, delimiter);
    }
    return 0;
}

// Helper function to extract the next number from the string
int getNextNumber(const char** ptr, const char* delimiters) {
    int number = strtol(*ptr, (char**)ptr, 10);
    while (**ptr && strchr(delimiters, **ptr)) (*ptr)++;
    return number;
}

// Helper function to add a number to the sum or track it if it's negative
void addNumber(int number, int* sum, int negatives[], int* negCount) {
    if (number < 0) {
        negatives[(*negCount)++] = number;
    } else if (number <= 1000) {
        *sum += number;
    }
}

// Helper function to sum the numbers and track negatives
int sumNumbers(const char* ptr, const char* delimiters, int negatives[], int* negCount) {
    int sum = 0;
    while (*ptr) {
        int number = getNextNumber(&ptr, delimiters);
        addNumber(number, &sum, negatives, negCount);
    }
    return sum;
}

// Helper function to handle negative numbers
void handleNegativeNumbers(int negatives[], int negCount) {
    if (negCount > 0) {
        printf("Negatives not allowed: ");
        for (int i = 0; i < negCount; ++i) {
            printf("%d ", negatives[i]);
        }
        printf("\n");
    }
}

// Helper function to check for empty input
int isEmpty(const char* numbers) {
    return numbers == NULL || strlen(numbers) == 0;
}

// Main add function
int add(const char* numbers) {
    if (isEmpty(numbers)) {
        return 0;
    }

    char delimiter[100];
    int offset = parseDelimiter(numbers, delimiter);

    const char* ptr = numbers + offset;

    int negatives[100];
    int negCount = 0;
    int sum = sumNumbers(ptr, delimiter, negatives, &negCount);

    handleNegativeNumbers(negatives, negCount);

    return (negCount > 0) ? -1 : sum;
}
