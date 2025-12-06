/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:38:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/12/06 13:00:18 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Verifies if all textures and colors are properly loaded.
 * @param game Pointer to the game structure.
 * @return 1 if all textures and colors are valid, 0 otherwise.
 */
int	ft_verifytexcolor(t_game *game)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		if (game->textures[j].addr == NULL)
			return (ft_printf("Error:\nMap texture\n"), 0);
		j++;
	}
	j = 0;
	if (game->map.ceiling_color == -1 || game->map.floor_color == -1)
		return (ft_printf("Error:\nMap color\n"), 0);
	return (1);
}

/**
 * @brief Validates map content, walls, and boundaries.
 *
 * @param map Pointer to the map structure.
 * @return 1 if valid, 0 otherwise.
 */
int	ft_val_elem(t_map *map)
{
	int	player;

	player = 0;
	if (!ft_mapcontent(map))
		return (0);
	if (!ft_mapwall(map))
		return (0);
	if (!ft_map_sidewall(map))
		return (0);
	player = ft_mapposition(map, "NSEW");
	if (player < 0)
		return (ft_printf("Error:\nNo player in the map\n"), 0);
	if (player > 0)
		return (ft_printf("Error:\n%d players in the map\n", player + 1), 0);
	return (1);
}

/**
 * @brief Reads the map from a file and stores it in map->grid.
 * @param map Pointer to the t_map structure where the map will be stored.
 * @param filename Path to the file containing the map.
 * @return 1 on success, 0 on error.
 */
int	ft_read_map(t_map *map, char *filename)
{
	int	fd;

	if (!ft_count_map_lines(map, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	map->width = malloc(sizeof(int) * (map->height));
	if (!ft_error_mem(&map->grid) || !ft_error_mem(&map->width))
		return (0);
	if (!ft_read_grid_lines(map, fd))
		return (0);
	close(fd);
	gnl_cleanup();
	return (1);
}

/**
 * @brief Check if the file has a ".cub" extension and can be opened.
 *
 * @param filename File name to check.
 * @return int 1 if valid, 0 otherwise.
 */
int	ft_val_extension(char *filename)
{
	int		fd;
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		ft_printf("Error:\nInvalid file extension.\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error:\nFile open failed\n");
		return (0);
	}
	close(fd);
	return (1);
}

/**
 * @brief Parses and validates the .cub configuration file.
 * @param filename Path to the .cub file.
 * @param game Pointer to the game structure.
 * @return 1 if parsing is successful, 0 on error.
 * 
 * Validates file extension, reads the map, parses configuration tokens,
 * verifies textures and colors, removes unnecessary spaces, validates
 * map elements and boundaries, and initializes the game window.
 */
int	ft_parse_file(char *filename, t_game *game)
{
	if (!ft_val_extension(filename))
		return (0);
	if (!ft_read_map(&game->map, filename))
		return (0);
	if (!ft_lexer(game))
		return (0);
	if (!ft_verifytexcolor(game))
		return (0);
	ft_elimine_space(&game->map);
	if (!ft_val_elem(&game->map))
		return (0);
	if (!ft_new_window(game))
		return (0);
	return (1);
}
