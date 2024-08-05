#include <gtest/gtest.h>
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const char* input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char* input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char* input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    const char* input = "1,1001";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const char* input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, CustomDelimiterNotPresent) {
    int expectedresult = 6;
    const char* input = "1,2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter_EmptyString) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, HandleNegativeNumbers) {
    const char* input = "-1,2";
    testing::internal::CaptureStdout();
    int result = add(input);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(result, -1);
    ASSERT_EQ(output, "Negatives not allowed: -1 \n");
}

// Additional Tests for Edge Cases

TEST(StringCalculatorAddTests, MultipleCustomDelimiters) {
    int expectedresult = 6;
    const char* input = "//[*][%]\n1*2%3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, SingleNumberWithoutDelimiters) {
    int expectedresult = 5;
    const char* input = "5";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, MultipleNumbersWithVaryingLengths) {
    int expectedresult = 1236;
    const char* input = "123,456,789";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, NumbersWithOnlyNewlines) {
    int expectedresult = 10;
    const char* input = "1\n2\n3\n4";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, CustomDelimiterDifferentLength) {
    int expectedresult = 6;
    const char* input = "//[***]\n1***2***3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
