#include <stdio.h>

/* 
 * Function: my_strlen
 * -------------------
 * Computes the length of a given string.
 *
 * str: A pointer to a null-terminated string.
 *
 * Returns: The length of the string (excluding the null character).
 */
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

/* 
 * Function: reverse_string
 * ------------------------
 * Reverses a given string in place without using built-in functions.
 *
 * str: A pointer to a null-terminated string.
 *
 * Returns: Nothing (modifies the string in place).
 */
void reverse_string(char *str) {
    int length, left, right;
    char temp;

    /* Get the length of the string using my_strlen */
    length = my_strlen(str);
    left = 0;
    right = length - 1;

    /* Swap characters from both ends */
    while (left < right) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

/* 
 * Function: main
 * --------------
 * Tests the reverse_string function with different test cases.
 *
 * Returns: 0 (indicating successful execution).
 */
int main(void) {
    /* Test cases */
    char test1[] = "edoc fo esuoH oT emocleW";
    char test2[] = "uoy pleh lliw ti ;3 melborp ni noitcnuf siht esU";
    char test3[] = "Hello World";
    char test4[] = "G";

    /* Print and reverse each string */
    printf("Before: %s\n", test1);
    reverse_string(test1);
    printf("After: %s\n\n", test1);

    printf("Before: %s\n", test2);
    reverse_string(test2);
    printf("After: %s\n\n", test2);

    printf("Before: %s\n", test3);
    reverse_string(test3);
    printf("After: %s\n\n", test3);

    printf("Before: %s\n", test4);
    reverse_string(test4);
    printf("After: %s\n\n", test4);

    return 0;
}
