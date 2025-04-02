#include "tome_reader.h"

int my_lseek(int fd, off_t target_offset) {
    char buf;
    off_t current_offset = 0;

    while (current_offset < target_offset) {
        if (read(fd, &buf, 1) != 1)
            return -1; // failed
        current_offset++;
    }
    return 0;  // Success
}

char *tome_reader(int fd, off_t *offset, char *filename) {
    static char buffer[BUFFER_SIZE + 1];
    static char *storage = NULL;
    ssize_t bytes_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    // **Use our custom lseek**
    if (my_lseek(fd, *offset) == -1)
        return NULL;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';

        if (storage)
            storage = str_join(storage, buffer);
        else
            storage = strdup(buffer);

        if (strchr(storage, '\n')) // If we find a newline, we stop reading
            break;
    }

    if (!storage || !*storage)
        return NULL;

    line = extract_line(&storage);  // Extract the line up to the newline

    *offset += strlen(line);  // Update the offset with the length of the line

    // Save the updated offset to the position file for the specific file (e.g., A_offset.txt for A.txt)
    save_offset(filename, *offset);  // Use the actual filename here

    return line;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    off_t offset = read_saved_offset(argv[1]);
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char *line = tome_reader(fd, &offset, argv[1]);

    if (line) {
        printf("%s", line);
        free(line);
    } else {
        printf("End of file reached.\n");
    }

    close(fd);
    return 0;
}
