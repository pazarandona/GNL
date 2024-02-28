/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:45 by pazarand          #+#    #+#             */
/*   Updated: 2024/02/28 18:03:42 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	 *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_index = 0;
    char *line = NULL;

    if (fd < 0)
	return NULL;
	while (1)
	{
		if (buffer_index == 0)
		{
            ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read == -1)
			{
                buffer[0] = '\0';
                buffer_index = 0;
                return (free(line), NULL);
            } 
			else if (bytes_read == 0)
			{
                if (line != NULL && *line)
                    return line;
				else
                    return NULL;
            } 
			else
                buffer[bytes_read] = '\0';
        }

        int result = process_buffer(buffer, &buffer_index, &line);
        if (result == -1)
            return (free(line), NULL);
		else if (result == 1)
            return line;
    }
}*/

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
	static int buffer_index = 0;
	char *line = NULL;
	if (fd < 0) return NULL;

    while (1)
	{
        if (buffer_index == 0) {
            ssize_t bytes_read = try_read_into_buffer(fd, buffer, &buffer_index, &line);
            if (bytes_read == -1) return NULL; // Error de lectura manejado en try_read_into_buffer.

            char *eof_result = handle_read_result(bytes_read, buffer, &line);
            if (eof_result != NULL || bytes_read == 0) return eof_result;
            // No se necesita un else aquí, ya que el retorno en la línea anterior manejará los casos necesarios.
        }

        int result = process_buffer(buffer, &buffer_index, &line);
        if (result != 0) {
            // Si process_buffer indica que se ha completado una línea o hay un error.
            if (result == -1 && line != NULL) {
                free(line);
                return NULL;
            }
            return line;
        }
        // Continuar el bucle si result == 0, indicando que el buffer se ha procesado completamente pero no se ha completado una línea.
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
