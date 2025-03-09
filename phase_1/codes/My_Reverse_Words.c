#include <stdio.h>

/**
 * my_strlen - Custom function to count the number of characters in a string
 * @str: The input string
 * Return: The length of the string excluding the null terminator
 */
int my_strlen(const char *str)
{
    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }
    return count;
}

/**
 * reverse_string - Function to reverse a given string
 * @str: The string to be reversed (modified in-place)
 */
void reverse_string(char *str)
{
    int length = my_strlen(str);
    int left = 0, right = length - 1;
    
    while (left < right)
    {
        // Swap characters
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        
        left++;
        right--;
    }
}

/**
 * reverse_words - Function to reverse the order of words in a string
 * @str: The string to be modified in-place
 */
void reverse_words(char *str)
{
    int length = my_strlen(str);
    if (length == 0)
        return;

    // Step 1: Reverse the entire string
    reverse_string(str);

    // Step 2: Reverse each word in place
    int start = 0, end = 0;
    while (str[end] != '\0')
    {
        // Find the start of a word
        while (str[start] == ' ' && str[start] != '\0')
            start++;
        
        end = start;
        
        // Find the end of the word
        while (str[end] != ' ' && str[end] != '\0')
            end++;

        // Reverse the word using reverse_string on the slice
        if (start < end)
        {
            char temp = str[end];
            str[end] = '\0';  // Temporarily terminate the word string
            reverse_string(str + start);  // Reverse the word in place
            str[end] = temp;  // Restore the original string
        }

        start = end;
    }
}

int main(void)
{
    char test1[] = "Valoria Kingdom";
    char test2[] = "Hidden truths revealed";
    char test3[] = "Ancient whisper";
    char test4[] = "SingleWord";
    char test5[] = "  Extra  Spaces   ";

    printf("Before: \"%s\"\n", test1);
    reverse_words(test1);
    printf("After:  \"%s\"\n\n", test1);

    printf("Before: \"%s\"\n", test2);
    reverse_words(test2);
    printf("After:  \"%s\"\n\n", test2);

    printf("Before: \"%s\"\n", test3);
    reverse_words(test3);
    printf("After:  \"%s\"\n\n", test3);

    printf("Before: \"%s\"\n", test4);
    reverse_words(test4);
    printf("After:  \"%s\"\n\n", test4);

    printf("Before: \"%s\"\n", test5);
    reverse_words(test5);
    printf("After:  \"%s\"\n\n", test5);

    return 0;
}

// IA-E Succ.
