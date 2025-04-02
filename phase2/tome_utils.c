#include "tome_reader.h"

char *str_join(char *s1, char *s2) {
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *new_str = malloc(len1 + len2 + 1);

    if (!new_str)
        return NULL;

    if (s1)
        strcpy(new_str, s1);
    strcat(new_str, s2);

    free(s1);
    return new_str;
}

char *extract_line(char **storage) {
    char *newline_pos = strchr(*storage, '\n');
    size_t len = newline_pos ? (size_t)(newline_pos - *storage + 1) : strlen(*storage);
    char *line = malloc(len + 1);

    if (!line)
        return NULL;

    strncpy(line, *storage, len);
    line[len] = '\0';

    char *remaining = newline_pos ? strdup(newline_pos + 1) : NULL;
    free(*storage);
    *storage = remaining;

    return line;
}

char *remove_extension(const char *filename) {
    char *dot = strrchr(filename, '.');
    size_t len = dot ? (size_t)(dot - filename) : strlen(filename);
    char *basename = malloc(len + 1);
    
    if (!basename)
        return NULL;

    strncpy(basename, filename, len);
    basename[len] = '\0';
    return basename;
}

off_t read_saved_offset(const char *filename) {
    char *position_filename = remove_extension(filename);  // Remove the extension from the filename
    if (!position_filename)
        return 0;  // Return 0 if memory allocation fails for position_filename

    // Create the position filename with '_offset' suffix
    char path[256];
    snprintf(path, sizeof(path), "%s_offset.txt", position_filename);  // e.g., A_offset.txt
    free(position_filename);

    FILE *file = fopen(path, "r");
    off_t offset = 0;

    if (file) {
        fscanf(file, "%ld", &offset);  // Read the saved offset
        fclose(file);
    }
    return offset;  // Return the saved offset (or 0 if not found)
}

void save_offset(const char *filename, off_t offset) {
    char *position_filename = remove_extension(filename);  // Remove the extension from the filename
    if (!position_filename)
        return;  // If memory allocation fails, return
    // Create the position filename with '_offset' suffix
    char path[256];
    snprintf(path, sizeof(path), "%s_offset.txt", position_filename);  // e.g., A_offset.txt
    free(position_filename);

    FILE *file = fopen(path, "w");
    if (file) {
        fprintf(file, "%ld", offset);  // Save the current offset
        fclose(file);
    }
}
