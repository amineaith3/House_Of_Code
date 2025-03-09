#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_str - Splits a string into an array of substrings using a delimiter.
 * @str: The input string to split.
 * @delimiter: The character used to split the string.
 * 
 * Return: A dynamically allocated array of substrings (NULL-terminated).
 */
char **split_str(const char *str, char delimiter)
{
    if (str == NULL || *str == '\0')
    {
        // Return an empty array if the input string is empty
        char **empty_result = malloc(sizeof(char *));
        if (empty_result)
            empty_result[0] = NULL;
        return empty_result;
    }

    char **result = NULL;
    int count = 0;
    int length = strlen(str);
    int start = 0, end = 0;

    while (end <= length)
    {
        if (str[end] == delimiter || str[end] == '\0')  // Found delimiter or end of string
        {
            if (start != end)  // Avoid empty substrings from consecutive delimiters
            {
                int word_length = end - start;
                char *substring = (char *)malloc((word_length + 1) * sizeof(char));
                if (!substring)
                {
                    // Free previously allocated memory on failure
                    for (int i = 0; i < count; i++)
                        free(result[i]);
                    free(result);
                    return NULL;
                }

                strncpy(substring, str + start, word_length);
                substring[word_length] = '\0';

                // Expand result array to store the new substring
                char **temp = realloc(result, (count + 2) * sizeof(char *));
                if (!temp)
                {
                    free(substring);
                    for (int i = 0; i < count; i++)
                        free(result[i]);
                    free(result);
                    return NULL;
                }
                result = temp;
                result[count++] = substring;
            }
            start = end + 1;  // Move to the next word
        }
        end++;
    }

    // NULL-terminate the array
    if (result)
    {
        result[count] = NULL;
    }
    return result;
}

// Function to free the dynamically allocated memory
void free_split_str(char **array)
{
    if (array)
    {
        for (int i = 0; array[i] != NULL; i++)
            free(array[i]);
        free(array);
    }
}

int main(void)
{
    char test1[] = "apple,banana,grape";
    char test2[] = ",leading,comma";
    char test3[] = "trailing,comma,";
    char test4[] = ",,,multiple,,,delimiters,,";
    char test5[] = "singleword";
    char test6[] = "";

    char **result;

    result = split_str(test1, ',');
    printf("Test 1: %s\n", test1);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    result = split_str(test2, ',');
    printf("\nTest 2: %s\n", test2);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    result = split_str(test3, ',');
    printf("\nTest 3: %s\n", test3);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    result = split_str(test4, ',');
    printf("\nTest 4: %s\n", test4);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    result = split_str(test5, ',');
    printf("\nTest 5: %s\n", test5);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    result = split_str(test6, ',');
    printf("\nTest 6: %s\n", test6);
    for (int i = 0; result[i] != NULL; i++)
        printf("[%s]\n", result[i]);
    free_split_str(result);

    return 0;
}

