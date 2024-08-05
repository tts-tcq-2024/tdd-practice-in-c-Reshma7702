#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_is_empty_string() {
    assert(is_empty_string("") == true);
    assert(is_empty_string(NULL) == true);
    assert(is_empty_string("non-empty") == false);
}

void test_extract_custom_delimiter() {
    char delimiter[20];
    extract_custom_delimiter("//;\n1;2", delimiter);
    assert(strcmp(delimiter, ";") == 0);

    extract_custom_delimiter("//[***]\n1***2***3", delimiter);
    assert(strcmp(delimiter, "[***]") == 0);
}

void test_has_custom_delimiter() {
    char delimiter[20];
    has_custom_delimiter("//;\n1;2", delimiter);
    assert(strcmp(delimiter, ";") == 0);

    has_custom_delimiter("1,2\n3", delimiter);
    assert(strcmp(delimiter, ",\n") == 0);
}

void test_value_less_than_thousand() {
    assert(value_less_than_thousand(999) == 999);
    assert(value_less_than_thousand(1000) == 0);
    assert(value_less_than_thousand(1001) == 0);
}

void test_check_negative_values() {
    if (fork() == 0) {
        check_negative_values(-1);
        exit(EXIT_SUCCESS);
    } else {
        int status;
        wait(&status);
        assert(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE);
    }

    check_negative_values(1);
}

void test_process_input() {
    assert(process_input("1,2,3", ",\n") == 6);
    assert(process_input("2\n3,4", ",\n") == 9);

    if (fork() == 0) {
        process_input("-1,2,3", ",\n");
        exit(EXIT_SUCCESS);
    } else {
        int status;
        wait(&status);
        assert(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE);
    }
}

void test_add() {
    assert(add("") == 0);
    assert(add("1,2,3") == 6);
    assert(add("2\n3,4") == 9);
    assert(add("//;\n1;2") == 3);

    if (fork() == 0) {
        add("-1,2,3");
        exit(EXIT_SUCCESS);
    } else {
        int status;
        wait(&status);
        assert(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE);
    }

    assert(add("1000,1001,2") == 2);
}

int main() {
    test_is_empty_string();
    test_extract_custom_delimiter();
    test_has_custom_delimiter();
    test_value_less_than_thousand();
    test_check_negative_values();
    test_process_input();
    test_add();

    printf("All tests passed!\n");
    return 0;
}
