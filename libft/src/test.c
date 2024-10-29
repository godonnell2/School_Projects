#include <stdio.h>

#include "libft.h"  // Include your library header


void test_ft_isalnum() {

    int test_cases[] = {

        'a', 'Z', '0',  // Valid alphanumeric characters

        '!', '@', '#',  // Invalid characters

        'z', 'A', '9',  // Edge cases

        127, -1         // Non-printable and negative values

    };


    int expected_results[] = {

        1, 1, 1,  // 'a', 'Z', '0' should return 1

        0, 0, 0,  // '!', '@', '#' should return 0

        1, 1, 1,  // 'z', 'A', '9' should return 1

        0, 0       // 127 and -1 should return 0

    };


    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    int passed = 1;  // Flag to check if all tests pass


    for (int i = 0; i < num_tests; i++) {

        int result = ft_isalnum(test_cases[i]);

        if (result == expected_results[i]) {

            printf("Test %d: ft_isalnum(%d) = %d - Passed\n", i + 1, test_cases[i], result);

        } else {

            printf("Test %d: ft_isalnum(%d) = %d - Failed (Expected %d)\n", i + 1, test_cases[i], result, expected_results[i]);

            passed = 0;  // Set passed to false if any test fails

        }

    }


    if (passed) {

        printf("All tests passed!\n");

    } else {

        printf("Some tests failed.\n");

    }

}


int main() {

    test_ft_isalnum();  // Run the test function

    return 0;

}
