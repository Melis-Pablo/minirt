/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:40:03 by grbuchne          #+#    #+#             */
/*   Updated: 2024/10/18 16:56:36 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	read_to_buffer(int fd, char *buffer, char **scanner, char **line)
{
	int	read_bytes;

	read_bytes = read(fd, buffer + 1, BUFFER_SIZE);
	if (read_bytes <= 0)
	{
		*scanner = "x";
		if (read_bytes < 0)
		{
			free(*line);
			*line = NULL;
		}
		return (0);
	}
	buffer[read_bytes + 1] = (char)((read_bytes - BUFFER_SIZE) >> 31);
	buffer[0] = '\n';
	*scanner = buffer;
	return (1);
}

static void	scan_buffer(char **scanner)
{
	(*scanner)++;
	while ((*scanner)[0] != '\n' && !((*scanner)[1] <= '\0'))
	{
		(*scanner)++;
	}
}

static void	make_new_line(char *scanner, char *old_l, char *new_l, char *pos)
{
	if (old_l)
	{
		while (*old_l)
		{
			*new_l++ = *old_l++;
		}
	}
	while (pos <= scanner)
	{
		*new_l++ = *pos++;
	}
	*new_l = '\0';
}

int	append_line(char **scanner, char **line, int old_length)
{
	int		new_length;
	char	*new_line;
	char	*position;

	position = (*scanner) + 1;
	scan_buffer(scanner);
	new_length = old_length + (*scanner) + 1 - position;
	new_line = malloc(new_length + 1);
	if (!new_line)
	{
		*scanner = "x";
		free(*line);
		return (-1);
	}
	make_new_line(*scanner, *line, new_line, position);
	free(*line);
	*line = new_line;
	return (new_length);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 2];
	static char	*scanner = "x";
	char		*line;
	int			length;

	line = NULL;
	length = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || scanner[1] == -1)
	{
		scanner = "x";
		return (NULL);
	}
	while ((scanner[0] != '\n' && scanner[1] == '\0') || !length)
	{
		if (scanner[1] == '\0')
		{
			if (!read_to_buffer(fd, buffer, &scanner, &line))
				return (line);
		}
		length = append_line(&scanner, &line, length);
		if (length == -1)
			return (NULL);
	}
	return (line);
}
