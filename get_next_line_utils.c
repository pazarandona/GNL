/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:38:32 by pazarand          #+#    #+#             */
/*   Updated: 2024/02/20 15:23:49 by pazarand         ###   ########.fr       */
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

