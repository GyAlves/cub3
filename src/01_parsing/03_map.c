/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:38:02 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/24 20:23:54 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Counts player start positions and records the first one found.
 *
 * Searches map for player characters (N, S, E, W), stores position and
 * direction of the first occurrence, returns total count minus one.
 *
 * @param map Pointer to the map structure (updated with player data).
 * @return Count of player positions minus one (0 if exactly one player).
 */
int	ft_mapposition(t_map *map)
{
	int		i;
	int		z;
	int		count;
	char	*position;
	char	*ptr;

	i = -1;
	count = -1;
	position = "NSEW";
	while (map->grid[++i] != NULL)
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

/**
 * @brief Validates empty spaces don't border non-wall characters.
 *
 * Checks upward and leftward from space position to ensure only walls ('1')
 * are adjacent, preventing spaces inside playable areas.
 *
 * @param map Pointer to the map structure.
 * @param i Row index of space.
 * @param j Column index of space.
 * @return 1 if valid, 0 if space borders invalid area.
 */
static int	ft_mapemptyspace(t_map *map, int i, int j)
{
	char	*message;

	message = "Error invalid map — empty space inside playable area";
	while (j < map->width[i])
	{
		while(map->grid[i][j] != ' ' && j < map->width[i])
			j++;
		if (j == map->width[i])
			return (1);
		if (map->grid[i][j -1] != '1' && map->grid[i][j -1] != ' ')
		{
			return (ft_printf("%s 1) i = %d, j = %d\n", message, i, j), 0);
		}
		if (map->width[i - 1] >= j)
		{
			if (map->grid[i - 1][j] != ' ' && map->grid[i - 1][j] != '1')
				return (ft_printf("message\n"), 0);
			j++;
		}
	}
	return (1);
}

/**
 * @brief Validates side walls and interior spaces are properly closed.
 *
 * Checks left/right walls are '1', validates empty spaces don't border
 * invalid areas, and verifies all non-wall characters are valid.
 *
 * @param map Pointer to the map structure.
 * @return 1 if valid, 0 if walls or interior invalid.
 */
int	ft_map_sidewall(t_map *map)
{
	int	i;
	int	j;
	int width;

	i = 1;
	while (i < map->height -1)
	{
		j = 0;
		while (map->grid[i][j] == ' ')
			j++;
		width = map->width[i] - 1;
		printf("width = %d\n", width);
		if (map->grid[i][j] != '1' || map->grid[i][width] != '1')
		{
			printf("map->grid[%d][%d] != 1(%c) || map->grid[%d][%d] != 1(%c) \n", i, j, map->grid[i][j], i, width, map->grid[i][width]);
			return (ft_printf("Error: side wall not closed %d, %d\n", i, j), 0);
		}
		if (!ft_mapemptyspace(map, i, j))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates top and bottom walls are closed (only '1' or spaces).
 *
 * @param map Pointer to the map structure.
 * @return 1 if valid, 0 if walls are open.
 */
int	ft_mapwall1(t_map *map)
{
	int		j;
	int		height;
	char	*message;
	char	*botton_message;

	message = "Error: invalid map — top wall is not closed";
	botton_message = "Error: invalid map — bottom wall is not closed";
	j = 0;
	height = map->height -1;
	while (j < map->width[0])
	{
		if (map->grid[0][j] != '1' && map->grid[0][j]
			!= ' ' && map->grid[0][j] != '\0')
			return (ft_printf("%s\n", message), 0);
		j++;
	}
	j = 0;
	while (j < map->width[height])
	{
		if (map->grid[height][j] != '1' && map->grid[height][j]
			!= ' ' && map->grid[height][j] != '\0')
			return (ft_printf("%s\n", botton_message), 0);
		j++;
	}
	return (1);
}
