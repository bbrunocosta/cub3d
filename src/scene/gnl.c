/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosta-b <bcosta-b@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 09:44:43 by bcosta-b          #+#    #+#             */
/*   Updated: 2026/11/25 09:44:43 by bcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <unistd.h>

static int	read_char(t_reader *reader)
{
	if (reader->pos == reader->end)
	{
		reader->end = read(reader->fd, reader->buffer, sizeof(reader->buffer));
		reader->pos = 0;
		if (reader->end < 0)
			return (-2);
		if (reader->end == 0)
			return (-1);
	}
	return ((unsigned char)reader->buffer[reader->pos++]);
}

static int	grow_line(char **line, size_t *capacity)
{
	char	*new_line;
	size_t	i;

	if (*capacity > INT_MAX / 2)
		return (1);
	new_line = malloc(*capacity * 2);
	if (!new_line)
		return (1);
	i = 0;
	while (i < *capacity - 1)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	free(*line);
	*line = new_line;
	*capacity *= 2;
	return (0);
}

static int	read_line(t_reader *reader, char **line)
{
	size_t	capacity;
	size_t	len;
	int		c;

	capacity = 64;
	*line = malloc(capacity);
	if (!*line)
		return (-1);
	len = 0;
	c = read_char(reader);
	while (c > 0 && c != '\n')
	{
		if (len + 1 == capacity && grow_line(line, &capacity))
			return (-1);
		(*line)[len++] = c;
		c = read_char(reader);
	}
	if (c == -2 || c == 0)
		return (-1);
	if (len && (*line)[len - 1] == '\r')
		len--;
	(*line)[len] = '\0';
	return (len != 0 || c == '\n');
}

int	get_next_line(t_reader *reader, char **line)
{
	int	status;

	status = read_line(reader, line);
	if (status <= 0)
	{
		free(*line);
		*line = NULL;
	}
	return (status);
}
