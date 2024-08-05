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

// Helper function to skip delimiters
void skipDelimiters(const char** ptr, const char* delimiters) {
    while (**ptr && strchr(delimiters, **ptr)) {
        (*ptr)++;
    }
}

// Helper function to check if the current character is a valid digit or delimiter
int isValidCharacter(const char* ptr, const char* delimiters) {
    return strchr(delimiters, *ptr) || (*ptr >= '0' && *ptr <= '9');
}

// Helper function to extract the next number from the string
int getNextNumber(const char** ptr, const char* delimiters) {
    skipDelimiters(ptr, delimiters);
    int number = strtol(*ptr, (char**)ptr, 10);
    skipDelimiters(ptr, delimiters);
    return number;
}

// Helper function to add a number to the sum
void addToSum(int number, int* sum) {
    if (number <= 1000) {
        *sum += number;
    }
}

// Helper function to track a negative number
void trackNegative(int number, int negatives[], int* negCount) {
    negatives[(*negCount)++] = number;
}

// Helper function to process each number
void processNumber(int number, int* sum, int negatives[], int* negCount) {
    if (number < 0) {
        trackNegative(number, negatives, negCount);
    } else {
        addToSum(number, sum);
    }
}

// Helper function to sum the numbers and track negatives
int sumNumbers(const char* ptr, const char* delimiters, int negatives[], int* negCount) {
    int sum = 0;
    while (*ptr) {
        if (!isValidCharacter(ptr, delimiters)) {
            ptr++;
            continue;
        }
        int number = getNextNumber(&ptr, delimiters);
        processNumber(number, &sum, negatives, negCount);
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

int main() {
    const char* input = "1/2";
    printf("Result: %d\n", add(input));
    return 0;
}
