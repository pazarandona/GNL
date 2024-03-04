#ifndef GET_NEXT_LINE2_H
 #define GET_NEXT_LINE2_H
 #ifndef BUFFER_SIZE
 #define BUFFER_SIZE 42

 #endif

 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <stdio.h>

char *get_next_line(int fd);
char *append_char_to_string(char *str, char c);
int process_buffer(char *buffer, int *buffer_index, char **line);
ssize_t try_read_from_file(int fd, char *buffer, int *buffer_index);
char *finalize_and_return_line(ssize_t bytes_read, char **line);

#endif

