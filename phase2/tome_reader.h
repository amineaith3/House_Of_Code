#ifndef TOME_READER_H
#define TOME_READER_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 30
#endif

// Function prototypes
char *str_join(char *s1, char *s2);
char *extract_line(char **storage);
char *tome_reader(int fd, off_t *offset, char *filename);
off_t read_saved_offset(const char *filename);
void save_offset(const char *filename, off_t offset);
int my_lseek(int fd, off_t target_offset);
char *remove_extension(const char *filename);

#endif // TOME_READER_H
