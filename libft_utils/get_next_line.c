/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/12/05 20:16:45 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*read_and_join(char *buffer, int fd)
{
	char	*tmp;
	int		bytes;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	bytes = 1;
	while (!gnl_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(tmp), free(buffer), NULL);
		tmp[bytes] = '\0';
		buffer = gnl_strjoin(buffer, tmp);
	}
	free(tmp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (fd == -42 && buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = read_and_join(buffer, fd);
	line = get_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

void	gnl_cleanup(void)
{
	get_next_line(-42);
}
