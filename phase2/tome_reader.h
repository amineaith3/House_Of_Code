#ifndef TOME_READER_H
#define TOME_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Default buffer size for reading data
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 30
#endif

/**
 * Function prototypes:
 * These functions provide functionalities for reading and manipulating text files.
 * The file operations include joining strings, extracting lines, managing offsets,
 * and reading or saving data to a file.
 */

/**
 * str_join - Concatenates two strings and returns a new string.
 * @s1: The first string to concatenate.
 * @s2: The second string to concatenate.
 *
 * Return: A new string containing the concatenation of `s1` and `s2`, or 
 *         NULL if memory allocation fails.
 */
char *str_join(char *s1, char *s2);

/**
 * extract_line - Extracts a line from the storage string, up to the newline character.
 * @storage: A pointer to the string containing the content to extract the line from.
 *
 * Return: A dynamically allocated string containing the extracted line, or 
 *         NULL if memory allocation fails.
 */
char *extract_line(char **storage);

/**
 * tome_reader - Reads content from a file and returns a line, updating the offset.
 * @fd: The file descriptor for the file to read from.
 * @offset: A pointer to the current offset in the file.
 * @filename: The name of the file to use for saving the offset.
 *
 * Return: A string containing the extracted line, or NULL if an error occurs.
 */
char *tome_reader(int fd, off_t *offset, char *filename);

/**
 * read_saved_offset - Reads the saved offset from a file corresponding to the given filename.
 * @filename: The name of the file for which the offset is saved.
 *
 * Return: The saved offset as a type `off_t`, or 0 if the file doesn't exist or an error occurs.
 */
off_t read_saved_offset(const char *filename);

/**
 * save_offset - Saves the current offset to a file corresponding to the given filename.
 * @filename: The name of the file for which the offset should be saved.
 * @offset: The current offset to save.
 *
 * Return: None.
 */
void save_offset(const char *filename, off_t offset);

/**
 * my_lseek - Custom implementation of the lseek function to set the file offset.
 * @fd: The file descriptor of the file.
 * @target_offset: The target offset to set.
 *
 * Return: 0 on success, or -1 if an error occurs.
 */
int my_lseek(int fd, off_t target_offset);

/**
 * remove_extension - Removes the file extension from a filename.
 * @filename: The filename from which the extension should be removed.
 *
 * Return: A new string containing the base name of the file (without extension),
 *         or NULL if memory allocation fails.
 */
char *remove_extension(const char *filename);

#endif // TOME_READER_H
