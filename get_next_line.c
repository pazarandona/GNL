/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:45 by pazarand          #+#    #+#             */
/*   Updated: 2024/02/20 15:26:56 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	 *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_index = 0;
    char *line = NULL;

    if (fd < 0) {
        return NULL;
    }

    while (1) {
        if (buffer_index == 0) {
            ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read == -1) {
                buffer[0] = '\0';
                buffer_index = 0;
                if (line != NULL) {
                    free(line);
                }
                return NULL;
            } else if (bytes_read == 0) {
                // Manejo de EOF
                if (line != NULL && *line) {
                    return line;
                } else {
                    return NULL;
                }
            } else {
                buffer[bytes_read] = '\0';
            }
        }

        int result = process_buffer(buffer, &buffer_index, &line);
        if (result == -1) {
            if (line != NULL) {
                free(line); 
            }
            return NULL;
        } else if (result == 1) {
            return line;
        }
    }
}

/*int main() {
    int fd = open("test.txt", O_RDONLY); // Cambia 'test.txt' por la ruta de tu archivo
    if (fd == -1) {
        printf("Error al abrir el archivo\n");
        return (0);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    system("leaks a.out");
    return 0;
}*/
