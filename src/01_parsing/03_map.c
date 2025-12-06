/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:38:02 by jucoelho          #+#    #+#             */
/*   Updated: 2025/12/06 19:33:03 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			return (ft_printf("Error:\nMap line %d is NULL\n", i), 0);
		j = 0;
		while (map->grid[i][j] != '\0')
		{
			z = 0;
			while ((z < 7) && (map->grid[i][j] != possib_char[z]))
				z++;
			if (possib_char[z] == '\0')
				return (ft_printf("Error:\nUnrecognized character found\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Counts player start positions and records the first one found.
 *
 * Searches map for player characters (N, S, E, W), stores position and
 * direction of the first occurrence, returns total count minus one.
 *
 * @param map Pointer to the map structure (updated with player data).
 * @return Count of player positions minus one (0 if exactly one player).
 */
int	ft_mapposition(t_map *map, char *position)
{
	int		i;
	int		z;
	int		count;
	char	*ptr;

	i = -1;
	count = -1;
	while (++i < map->height)
	{
		z = -1;
		while (position[++z] != '\0')
		{
			ptr = ft_strchr(map->grid[i], position[z]);
			while (ptr)
			{
				map->player_dir = position[z];
				map->player_x = ptr - map->grid[i];
				map->player_y = i;
				count++;
				ptr = ft_strchr(++ptr, position[z]);
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

	message = "Invalid map — empty space inside playable area";
	while (j < map->width[i])
	{
		while (map->grid[i][j] != ' ' && j < map->width[i])
			j++;
		if (j == map->width[i])
			return (1);
		if (map->grid[i][j -1] != '1' && map->grid[i][j -1] != ' ')
		{
			ft_printf("Error\n");
			return (ft_printf("%s\n", message), 0);
		}
		if (map->width[i - 1] > j)
		{
			if (map->grid[i - 1][j] != ' ' && map->grid[i - 1][j] != '1')
			{
				ft_printf("Error\n");
				return (ft_printf("%s\n", message), 0);
			}
		}
		j++;
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
	int	width;

	i = 1;
	while (i < map->height -1)
	{
		j = 0;
		while (map->grid[i][j] == ' ')
			j++;
		width = map->width[i] - 1;
		if (map->grid[i][j] != '1' || map->grid[i][width] != '1')
			return (ft_printf("Error:\nSide wall not closed\n"), 0);
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
/*int	ft_mapwall(t_map *map)
{
	int		j;
	int		height;
	char	*message;
	char	*botton_message;
	int		i;

	message = "Error:\ninvalid map — top wall is not closed";
	botton_message = "Error:\ninvalid map — bottom wall is not closed";
	j = 0;
	i = 1;
	height = map->height -1;
	while (j < map->width[0] && map->grid[0][j] != '\0')
	{
		if (map->grid[0][j] != '1' && map->grid[0][j]
			!= ' ' && map->grid[0][j] != '\0')
			return (ft_printf("%s\n", message), 0);
		if (map->grid[i][j] == ' ')
		{
			while (i < map->height && map->grid[i][j] == ' ')
				i++;
			if (i < map->height && map->grid[i][j] != '1' 
				&& map->grid[i][j] != '\0')
				return (ft_printf("Error:\ninvalid map — top wall is not closed\n"), 0);
		}
		else if (map->grid[0][j] != '1')
			return (ft_printf("Error:\ninvalid map — top wall is not closed\n"), 0);
		j++;
	}
	j = 0;
	while (j < map->width[height])
	{
		if (map->grid[height][j] != '1' && map->grid[height][j]
			!= ' ' && map->grid[height][j] != '\0')
			return (ft_printf("%s\n", botton_message), 0);
		if (map->grid[height][j] == ' ')
		{
			while (map->grid[height] && map->grid[height][j] == ' ')
			{
				height--;
				if (map->grid[height][j] != ' ' && map->grid[height][j] != '1')
					return (ft_printf("%s\n", message), 0);
			}
			i = 0;
		}
		j++;
	}
	return (1);
}*/

int	ft_mapwall(t_map *map)
{
	int		j;
	int		height;
	int		i;

	height = map->height - 1;
	
	// Verificar parede superior
	j = 0;
	while (j < map->width[0] && map->grid[0][j] != '\0')
	{
		if (map->grid[0][j] == ' ')
		{
			// Verificar se existe '1' abaixo antes de qualquer outro caractere
			i = 1;
			while (i < map->height && map->grid[i][j] == ' ')
				i++;
			if (i < map->height && map->grid[i][j] != '1' 
				&& map->grid[i][j] != '\0')
				return (ft_printf("Error:\ninvalid map — top wall is not closed\n"), 0);
		}
		else if (map->grid[0][j] != '1')
			return (ft_printf("Error:\ninvalid map — top wall is not closed\n"), 0);
		j++;
	}
	
	// Verificar parede inferior
	j = 0;
	while (j < map->width[height] && map->grid[height][j] != '\0')
	{
		if (map->grid[height][j] == ' ')
		{
			// Verificar se existe '1' acima antes de qualquer outro caractere
			i = height - 1;
			while (i >= 0 && map->grid[i][j] == ' ')
				i--;
			if (i >= 0 && map->grid[i][j] != '1' && map->grid[i][j] != '\0')
				return (ft_printf("Error:\ninvalid map — bottom wall is not closed\n"), 0);
		}
		else if (map->grid[height][j] != '1')
			return (ft_printf("Error:\ninvalid map — bottom wall is not closed\n"), 0);
		j++;
	}
	
	return (1);
}
