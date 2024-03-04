/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:38:32 by pazarand          #+#    #+#             */
/*   Updated: 2024/03/04 20:23:37 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *append_char_to_string(char *str, char c) {
    int length = 0;
    if (str != NULL) {
        while (str[length]) {
            length++;
        }
}
    char *new_str = malloc(sizeof(char) * (length + 2));
    if (!new_str){
        return NULL;
    }

    int i = 0;
    while (i < length) {
        new_str[i] = str[i];
        i++;
    }
    new_str[length] = c;
    new_str[length + 1] = '\0';

    if (str != NULL) {
        free(str);
    }

    return new_str;
}


// Retorna 1 si se completó una línea, 0 si se necesita más lectura, o -1 si hay un error.
int process_buffer(char *buffer, int *buffer_index, char **line) {
    int i = *buffer_index;
    int line_completed = 0;

    while (buffer[i] != '\0') {
        char *temp_line = append_char_to_string(*line, buffer[i]);
        if (!temp_line) return -1; // Error en append_char_to_string
        *line = temp_line;
        if (buffer[i++] == '\n') {
            line_completed = 1; // Línea completada
            break;
        }
    }
    if (buffer[i] == '\0') {
    *buffer_index = 0;
} else {
    *buffer_index = i;
}

    return line_completed;
}

// Intenta leer del archivo y manejar errores o EOF.
// Retorna -1 para error, 0 para EOF, y el número de bytes leídos para una lectura exitosa.
ssize_t try_read_from_file(int fd, char *buffer, int *buffer_index) {
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) {
        buffer[0] = '\0';
        *buffer_index = 0;
        return bytes_read; // -1 para error, 0 para EOF
    }
    buffer[bytes_read] = '\0';
    return bytes_read;
}

// Maneja la decisión de qué retornar (la línea, NULL, o manejo de error).
char *finalize_and_return_line(ssize_t bytes_read, char **line) {
    if (bytes_read == -1 || (bytes_read == 0 && (*line == NULL || **line == '\0'))) {
        if (*line != NULL) free(*line);
        return NULL;
    }
    return *line;
}

