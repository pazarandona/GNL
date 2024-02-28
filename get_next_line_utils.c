/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:38:32 by pazarand          #+#    #+#             */
/*   Updated: 2024/02/22 18:06:19 by pazarand         ###   ########.fr       */
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


ssize_t read_to_buffer(int fd, char *buffer, int *buffer_index)
{
	ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*buffer_index = 0;
	}
	return bytes_read;
}

// Procesa el buffer para construir la línea.
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

ssize_t try_read_into_buffer(int fd, char *buffer, int *buffer_index, char **line) {
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        buffer[0] = '\0'; // Limpia el buffer.
        *buffer_index = 0; // Resetea el índice del buffer.
        if (*line != NULL) {
            free(*line); // Libera la línea si no es NULL.
            *line = NULL; // Evita el uso de un puntero libre.
        }
        return -1; // Indica un error de lectura.
    }
    return bytes_read; // Retorna el número de bytes leídos.
}

char *handle_read_result(ssize_t bytes_read, char *buffer, char **line) {
    if (bytes_read == 0) {
        // Manejo de EOF
        if (*line != NULL && **line) {
            return *line; // Devuelve la línea si contiene algo.
        } else {
            // Si la línea está vacía o no se ha asignado, devuelve NULL.
            if (*line != NULL) {
                free(*line);
                *line = NULL; // Asegura que el puntero no apunte a memoria liberada.
            }
            return NULL;
        }
    } else {
        // Prepara el buffer para su procesamiento posterior.
        buffer[bytes_read] = '\0';
        return NULL; // Retorna NULL para indicar que no se ha completado la operación.
    }
}


