#include "tome_reader.h"

/**
 * str_join - Concatenates two strings and returns a new string.
 * @s1: The first string to concatenate.
 * @s2: The second string to concatenate.
 *
 * This function allocates memory for a new string and copies the contents of 
 * both input strings, `s1` and `s2`, into it. The memory for `s1` is freed 
 * after concatenation. If memory allocation fails, NULL is returned.
 *
 * Return: A new string containing the concatenation of `s1` and `s2`, or 
 *         NULL if memory allocation fails.
 */
char *str_join(char *s1, char *s2) {
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *new_str = malloc(len1 + len2 + 1);  // Allocate memory for the new string

    if (!new_str)
        return NULL;  // Return NULL if memory allocation fails

    if (s1)
        strcpy(new_str, s1);  // Copy the first string into the new string
    strcat(new_str, s2);  // Concatenate the second string to the new string

    free(s1);  // Free the memory of the first string
    return new_str;  // Return the concatenated string
}

/**
 * extract_line - Extracts a line from a string up to the newline character.
 * @storage: A pointer to the string containing the content to extract the line from.
 *
 * This function extracts a line from the `storage` string, up to and including
 * the first newline character ('\n'). If no newline is found, the entire string
 * is returned. The extracted line is dynamically allocated, and the original 
 * string is updated to point to the remaining content.
 *
 * Return: A dynamically allocated string containing the extracted line, or 
 *         NULL if memory allocation fails.
 */
char *extract_line(char **storage) {
    char *newline_pos = strchr(*storage, '\n');  // Find the position of the newline
    size_t len = newline_pos ? (size_t)(newline_pos - *storage + 1) : strlen(*storage);  // Calculate length of the line
    char *line = malloc(len + 1);  // Allocate memory for the line

    if (!line)
        return NULL;  // Return NULL if memory allocation fails

    strncpy(line, *storage, len);  // Copy the line into the new string
    line[len] = '\0';  // Null-terminate the line

    // Create a new string for the remaining content after the newline
    char *remaining = newline_pos ? strdup(newline_pos + 1) : NULL;  
    free(*storage);  // Free the memory of the original storage string
    *storage = remaining;  // Update the storage pointer to the remaining content

    return line;  // Return the extracted line
}

/**
 * remove_extension - Removes the file extension from a filename.
 * @filename: The filename from which the extension should be removed.
 *
 * This function locates the last occurrence of the dot ('.') character in 
 * the filename and creates a new string containing only the base name (without
 * the extension). Memory is allocated for the new string, which should be 
 * freed by the caller after use.
 *
 * Return: A new string containing the base name of the file (without extension),
 *         or NULL if memory allocation fails.
 */
char *remove_extension(const char *filename) {
    char *dot = strrchr(filename, '.');  // Find the last dot in the filename
    size_t len = dot ? (size_t)(dot - filename) : strlen(filename);  // Calculate the length of the base name
    char *basename = malloc(len + 1);  // Allocate memory for the base name

    if (!basename)
        return NULL;  // Return NULL if memory allocation fails

    strncpy(basename, filename, len);  // Copy the base name into the new string
    basename[len] = '\0';  // Null-terminate the base name
    return basename;  // Return the base name
}

/**
 * read_saved_offset - Reads the saved offset from a file based on the filename.
 * @filename: The name of the file for which the offset is saved.
 *
 * This function removes the file extension from the given filename and constructs
 * a new filename with the "_offset.txt" suffix. It attempts to open this file 
 * and reads the saved offset. If the file does not exist or there is an error, 
 * it returns 0.
 *
 * Return: The saved offset as a type `off_t`, or 0 if the file doesn't exist 
 *         or an error occurs.
 */
off_t read_saved_offset(const char *filename) {
    char *position_filename = remove_extension(filename);  // Remove the extension from the filename
    if (!position_filename)
        return 0;  // Return 0 if memory allocation fails for position_filename

    // Create the position filename with '_offset' suffix
    char path[256];
    snprintf(path, sizeof(path), "%s_offset.txt", position_filename);  // e.g., A_offset.txt
    free(position_filename);

    FILE *file = fopen(path, "r");  // Open the file for reading
    off_t offset = 0;

    if (file) {
        fscanf(file, "%ld", &offset);  // Read the saved offset from the file
        fclose(file);  // Close the file
    }
    return offset;  // Return the saved offset (or 0 if not found)
}

/**
 * save_offset - Saves the current offset to a file based on the filename.
 * @filename: The name of the file for which the offset should be saved.
 * @offset: The current offset to save.
 *
 * This function removes the file extension from the given filename and constructs
 * a new filename with the "_offset.txt" suffix. It then attempts to open this 
 * file and writes the provided offset to it. If the file cannot be opened, it 
 * does nothing.
 *
 * Return: None.
 */
void save_offset(const char *filename, off_t offset) {
    char *position_filename = remove_extension(filename);  // Remove the extension from the filename
    if (!position_filename)
        return;  // If memory allocation fails, return

    // Create the position filename with '_offset' suffix
    char path[256];
    snprintf(path, sizeof(path), "%s_offset.txt", position_filename);  // e.g., A_offset.txt
    free(position_filename);

    FILE *file = fopen(path, "w");  // Open the file for writing
    if (file) {
        fprintf(file, "%ld", offset);  // Save the current offset to the file
        fclose(file);  // Close the file
    }
}
