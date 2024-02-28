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
ssize_t read_to_buffer(int fd, char *buffer, int *buffer_index);
int process_buffer(char *buffer, int *buffer_index, char **line);
ssize_t try_read_into_buffer(int fd, char *buffer, int *buffer_index, char **line);
char *handle_read_result(ssize_t bytes_read, char *buffer, char **line);
int handle_eof_or_buffer(char *buffer, int *buffer_index, char **line);


#endif

