/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pazarand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:40:36 by pazarand          #+#    #+#             */
/*   Updated: 2024/03/05 17:53:13 by pazarand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13

# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*append_char_to_string(char *str, char c);
int		process_buffer(char *buffer, int *buffer_index, char **line);
ssize_t	try_read_from_file(int fd, char *buffer, int *buffer_index);
char	*finalize_and_return_line(ssize_t bytes_read, char **line);

#endif
