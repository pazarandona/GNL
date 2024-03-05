/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:14:45 by pazarand          #+#    #+#             */
/*   Updated: 2024/03/04 21:04:53 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	buffer_index;
	char		*line;
	ssize_t		bytes_read;
	int			result;

	line = NULL;
	while (1)
	{
		if (buffer_index == 0)
		{
			bytes_read = try_read_from_file(fd, buffer, &buffer_index);
			if (bytes_read <= 0)
				return (finalize_and_return_line(bytes_read, &line));
		}
		result = process_buffer(buffer, &buffer_index, &line);
		if (result != 0)
		{
			if (result == -1)
				return (free(line), NULL);
			return (line);
		}
	}
}
/*int main() {
    int fd = open("test.txt", O_RDONLY);
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
//    system("leaks a.out");
    return 0;
}*/
