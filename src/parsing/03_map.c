/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:38:02 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/09 19:28:42 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int	ft_mapposition(t_map *map)
{
	int		i;
	int		z;
	int		count;
	char	*position;
	char	*ptr;

	i = -1;
	count = 0;
	position = "NSEW";
	while (map->grid[++i] != '\0')
	{
		z = -1;
		while (position[++z] != '\0')
		{
			ptr = ft_strrchr(map->grid[i], position[z]);
			if (ptr)
			{
				map->player_dir = position[z];
				map->player_x = i;
				map->player_y = ptr - map->grid[i];
				count++;
			}
		}
	}
	return (count);
}

int	ft_mapcontent(t_map *map)
{
	int		i;
	int		j;
	int		z;
	char	*possib_char;

	i = 0;
	j = 0;
	z = 0;
	possib_char = "01NSEW";
	while (i <= 3)
	{
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			z = 0;
			while (possib_char[z] != '\0' && map->grid[i][j] != possib_char[z])
				z++;
			if (possib_char[z] == '\0')
				return (printf("error\n"), 0);
			j++;
		}
		i++;
	}
	return (printf("valid map"), 1);
}

int	ft_count_map_lines(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		count;
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->height = count;
	return (1);
}

int	ft_read_map(t_map *map, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if (!ft_count_map_lines(map, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!ft_error_mem(&map->grid))
		return (0);
	map->grid[map->height] = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[i] = line;
		i++;
	}
	close(fd);
	return (1);
}
