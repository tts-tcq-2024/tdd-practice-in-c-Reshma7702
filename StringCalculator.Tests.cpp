#include <gtest/gtest.h>
#include "StringCalculator.h"

// Test when the input is empty
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input is a single zero
TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const char* input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input is two numbers separated by comma
TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char* input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains newline as a delimiter
TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char* input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains numbers greater than 1000
TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    const char* input = "1,1001";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains a custom delimiter
TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const char* input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains a negative number
TEST(StringCalculatorAddTests, HandleNegativeNumbers) {
    const char* input = "-1,2";
    testing::internal::CaptureStdout();
    int result = add(input);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(result, -1);
    ASSERT_EQ(output, "Negatives not allowed: -1 \n");
}

// Test when the input contains multiple negative numbers
TEST(StringCalculatorAddTests, HandleMultipleNegativeNumbers) {
    const char* input = "-1,-2,3";
    testing::internal::CaptureStdout();
    int result = add(input);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(result, -1);
    ASSERT_EQ(output, "Negatives not allowed: -1 -2 \n");
}

// Test when the input contains custom delimiter with special regex characters
TEST(StringCalculatorAddTests, CustomDelimiterWithRegexCharacters) {
    int expectedresult = 6;
    const char* input = "//.\n1.2.3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains custom delimiter of length greater than 1
TEST(StringCalculatorAddTests, CustomDelimiterWithLongLength) {
    int expectedresult = 6;
    const char* input = "//[***]\n1***2***3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains multiple custom delimiters
TEST(StringCalculatorAddTests, MultipleCustomDelimiters) {
    int expectedresult = 6;
    const char* input = "//[*][%]\n1*2%3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains delimiters at the edge of the string
TEST(StringCalculatorAddTests, DelimitersAtEdgeOfString) {
    int expectedresult = 6;
    const char* input = ",1,2,3,";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains empty sections between delimiters
TEST(StringCalculatorAddTests, EmptySectionsBetweenDelimiters) {
    int expectedresult = 6;
    const char* input = "1,\n,2,\n,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test when the input contains maximum integer values
TEST(StringCalculatorAddTests, MaxIntValues) {
    int expectedresult = 2147483647 + 2147483647;
    char input[50];
    sprintf(input, "%d,%d", 2147483647, 2147483647);
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test for default delimiter branch coverage
TEST(StringCalculatorAddTests, DefaultDelimiterBranchCoverage) {
    const char* input = "1,2\n3";
    int expectedresult = 6;
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
