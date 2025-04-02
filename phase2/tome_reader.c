#include "tome_reader.h"


//yarbi next session tji f w9t mnaseb bash n7der

/**
 * my_lseek - Custom implementation of the lseek system call.
 * @fd: The file descriptor from which to seek.
 * @target_offset: The target offset to move the file pointer to.
 *
 * This function moves the file pointer to the specified target offset
 * by reading one byte at a time until the desired offset is reached.
 * It returns 0 on success, or -1 if it encounters an error.
 *
 * Return: 0 on success, -1 on failure.
 */
int my_lseek(int fd, off_t target_offset) {
    char buf;
    off_t current_offset = 0;

    while (current_offset < target_offset) {
        if (read(fd, &buf, 1) != 1)
            return -1; // failed to read
        current_offset++;
    }
    return 0;  // Success
}

/**
 * tome_reader - Reads a line from a file starting from a given offset.
 * @fd: The file descriptor of the file to read from.
 * @offset: Pointer to the offset in the file to start reading from.
 * @filename: The name of the file, used to save the updated offset.
 *
 * This function attempts to read from the file starting at the given offset.
 * It reads the file in chunks of size defined by BUFFER_SIZE and stores the
 * content in a static buffer. Once a newline character is encountered, it stops
 * reading and returns the line up to that newline character.
 * The offset is updated, and the new position is saved in the corresponding file.
 *
 * Return: The next line read from the file or NULL if there is an error or the end of file is reached.
 */
char *tome_reader(int fd, off_t *offset, char *filename) {
    static char buffer[BUFFER_SIZE + 1];  // Buffer to hold data from the file
    static char *storage = NULL;  // Storage to accumulate data
    ssize_t bytes_read;  // Number of bytes read in each read operation
    char *line;  // Pointer to store the extracted line

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;  // Invalid file descriptor or buffer size

    // **Use our custom lseek**
    if (my_lseek(fd, *offset) == -1)
        return NULL;  // Failed to seek to the desired offset

    // Read data in chunks from the file
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer

        // Append the new data to storage
        if (storage)
            storage = str_join(storage, buffer);  // Join previous and new buffer content
        else
            storage = strdup(buffer);  // Allocate and copy the buffer content

        // Stop reading if a newline character is found
        if (strchr(storage, '\n'))  
            break;
    }

    // If no content is read or storage is empty, return NULL
    if (!storage || !*storage)
        return NULL;

    // Extract the line up to the first newline character
    line = extract_line(&storage);  

    // Update the offset with the length of the line
    *offset += strlen(line);

    // Save the updated offset to the file corresponding to the filename
    save_offset(filename, *offset);

    return line;  // Return the extracted line
}

/**
 * main - Entry point of the program. Reads and prints a line from a file.
 * @argc: The number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * This function opens the specified file and reads the next line starting from
 * the saved offset. It prints the line if available, or a message if the end
 * of the file is reached. The file offset is saved after reading each line.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;  // Print usage and exit if incorrect arguments are passed
    }

    // Read the saved offset from a file
    off_t offset = read_saved_offset(argv[1]);
    
    // Open the file for reading
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;  // Print error message and exit if file cannot be opened
    }

    // Read the next line from the file using tome_reader
    char *line = tome_reader(fd, &offset, argv[1]);

    if (line) {
        printf("%s", line);  // Print the read line
        free(line);  // Free the allocated memory for the line
    } else {
        printf("End of file reached.\n");  // Print end-of-file message if no line is read
    }

    // Close the file descriptor before exiting
    close(fd);
    return 0;
}
