/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02aux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:55 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/30 22:35:52 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Removes the last line of the map if it contains only spaces.
 * @param map Pointer to the map structure.
 */
void	ft_elimine_space(t_map *map)
{
	int	i;
	int	j;

	i = map->height - 1;
	j = 0;
	if (i >= 0)
	{
		while (map->grid[i][j] == ' ')
			j++;
		if (map->grid[i][j] == '\0')
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
			map->height -= 1;
		}
	}
	ft_trim_trailing_spaces(map);
}

/**
 * @brief Removes trailing spaces from each line of the map.
 * @param map Pointer to the map structure.
 */
void	ft_trim_trailing_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = (map->width[i]) - 1;
		while (j >= 0 && map->grid[i][j] == ' ')
		{
			map->grid[i][j] = '\0';
			j--;
		}
		map->width[i] = j + 1;
		i++;
	}
}

/**
 * @brief Validates map grid contains only 
 * valid characters (' ', 0, 1, N, S, E, W).
 *
 * @param map Pointer to the map structure.
 * @return 1 if valid, 0 if invalid character found.
 */
int	ft_mapcontent(t_map *map)
{
	int		i;
	int		j;
	int		z;
	char	*possib_char;

	i = 0;
	possib_char = " 01NSEW";
	while (i < map->height)
	{	
		if (!map->grid[i])
			return (ft_printf("Error: map line %d is NULL\n", i), 0);
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			z = 0;
			while ((z < 7) && (map->grid[i][j] != possib_char[z]))
				z++;
			if (possib_char[z] == '\0')
				return (ft_printf("Error: unrecognized character found\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Count the number of lines in a file and store it in struct
 *
 * @param map Pointer to the map structure where the height will be stored.
 * @param filename File name to read.
 * @return int 1 if successful, 0 otherwise.
 */
int	ft_count_map_lines(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	gnl_cleanup();
	if (count == 0)
	{
		ft_printf("Error: map incomplete\n");
		return (0);
	}
	map->height = count;
	return (1);
}
