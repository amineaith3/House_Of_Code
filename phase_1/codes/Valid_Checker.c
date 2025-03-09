#include <stdio.h>

#define MAX_STACK_SIZE 6000  // idk what to put here, but it should be a big number, to use a stack

/**
 * isValid - Function to check if a string of brackets is balanced
 * @str: The input string containing brackets
 * Return: 1 if the string is valid, 0 otherwise
 */
int isValid(const char *str)
{
    char stack[MAX_STACK_SIZE];  // Stack to store opening brackets
    int top = -1;  // Stack pointer

    // Iterate through the string
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];

        // Push opening brackets onto the stack
        if (c == '(' || c == '{' || c == '[')
        {
            if (top >= MAX_STACK_SIZE - 1)
                return 0;  // Stack overflow (invalid case)

            stack[++top] = c;
        }
        else if (c == ')' || c == '}' || c == ']')  // If closing bracket
        {
            if (top == -1)
                return 0;  // No matching opening bracket

            char topChar = stack[top--];  // Pop from stack

            // Check if brackets match
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '['))
            {
                return 0;  // Mismatched brackets
            }
        }
    }

    return (top == -1);  // Valid if stack is empty at the end
}

int main(void)
{
    const char *test1 = "(){}[]";
    const char *test2 = "{[()]}";
    const char *test3 = "{[(])}";
    const char *test4 = "({[)]}";
    const char *test5 = "{[}";
    const char *test6 = "";

    printf("Test 1: %s => %s\n", test1, isValid(test1) ? "Valid" : "Invalid");
    printf("Test 2: %s => %s\n", test2, isValid(test2) ? "Valid" : "Invalid");
    printf("Test 3: %s => %s\n", test3, isValid(test3) ? "Valid" : "Invalid");
    printf("Test 4: %s => %s\n", test4, isValid(test4) ? "Valid" : "Invalid");
    printf("Test 5: %s => %s\n", test5, isValid(test5) ? "Valid" : "Invalid");
    printf("Test 6: %s => %s\n", test6, isValid(test6) ? "Valid" : "Invalid");

    return 0;
}

// IA-E Succ.
