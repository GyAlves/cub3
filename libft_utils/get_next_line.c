/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

static char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}

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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (fd == -42 && buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	bytes = 1;
	while (!gnl_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(tmp), free(buffer), buffer = NULL, NULL);
		tmp[bytes] = '\0';
		buffer = gnl_strjoin(buffer, tmp);
	}
	free(tmp);
	line = get_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

void	gnl_cleanup(void)
{
	get_next_line(-42);
}
