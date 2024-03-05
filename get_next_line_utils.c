/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:38:32 by pazarand          #+#    #+#             */
/*   Updated: 2024/03/05 14:34:16 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *append_char_to_string(char *str, char c)
{
    int     length;
    int     i;
    char    *new_str;

	length = 0;
	if (str != NULL)
    {
        while (str[length])
            length++;
    }
    new_str = malloc(sizeof(char) * (length + 2));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < length)
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[length] = c;
    new_str[length + 1] = '\0';
    if (str != NULL)
        free(str);
    return (new_str);
}


int process_buffer(char *buffer, int *buffer_index, char **line)
{
    int     i;
    int     line_completed;
    char    *temp_line;

    i = *buffer_index;
    line_completed = 0;
    while (buffer[i] != '\0')
    {
		temp_line = append_char_to_string(*line, buffer[i]);
        if (!temp_line)
            return (-1);
        *line = temp_line;
        if (buffer[i++] == '\n')
        {
            line_completed = 1;
            break;
        }
    }
    if (buffer[i] == '\0')
    {
        *buffer_index = 0;
    }
    else
        *buffer_index = i;
    return (line_completed);
}

ssize_t try_read_from_file(int fd, char *buffer, int *buffer_index)
{
    ssize_t bytes_read;

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0)
    {
        buffer[0] = '\0';
        *buffer_index = 0;
        return (bytes_read);
    }
    buffer[bytes_read] = '\0';
    return (bytes_read);
}

char    *finalize_and_return_line(ssize_t bytes_read, char **line)
{
    if (bytes_read == -1
        || (bytes_read == 0 && (*line == NULL || **line == '\0')))
    {
        if (*line != NULL)
            free(*line);
        return (NULL);
    }
    return (*line);
}
