/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_elements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:06:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/30 22:41:28 by jucoelho         ###   ########.fr       */
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
			return (ft_printf("Error: Map texture incomplete %d\n", j), 0);
		j++;
	}
	j = 0;
	if (game->map.ceiling_color == -1 || game->map.floor_color == -1)
		return (ft_printf("Error: Map color incomplete\n"), 0);
	return (1);
}

/**
 * @brief Converts RGB values to a single 
 * integer and assigns to floor or ceiling.
 * @param map Pointer to the map structure.
 * @param rgb Array containing the RGB values [0-255].
 * @param color_type Character indicating 
 * color type ('F' for floor, 'C' for ceiling).
 * @return 1 if successful, 0 if color is duplicated or invalid.
 */
int	ft_rgb_to_int(t_map *map, int *rgb, char color_type)
{
	if (color_type == 'F')
	{
		if (map->floor_color != -1)
		{
			printf("Error: Map with repeated floor color");
			return (0);
		}
		return ((map->floor_color = (rgb[0] << 16)
				| (rgb[1] << 8) | rgb[3]), 1);
	}
	else if (color_type == 'C')
	{
		if (map->ceiling_color != -1)
		{
			printf("Error: Map with repeated ceiling color");
			return (0);
		}
		return ((map->ceiling_color = (rgb[0] << 16)
				| (rgb[1] << 8) | rgb[3]), 1);
	}
	else if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[3] < 0 || rgb[3] > 255)
		return (0);
	return (0);
}

/**
 * @brief Validates and parses a color token from the map configuration.
 * @param map Pointer to the map structure.
 * @param i Line index in the map grid.
 * @param color_type Character indicating color type ('F' or 'C').
 * @return 1 if the color token is valid, 0 otherwise.
 */
int	ft_valid_colortoken(t_map *map, int i, char color_type)
{
	char	*str;
	char	**color;
	int		rgb[3];
	int		z;

	z = 0;
	str = ft_strtrim(map->grid[i] + 1, " ");
	if (!str)
		return (0);
	color = ft_split(str, ',');
	if (!color)
		return (free(str), 0);
	while (color[z])
		z++;
	if (z != 3)
		return (ft_free_map(color), free(str), 0);
	z = -1;
	while (++z < 3)
	{
		rgb[z] = ft_atoi(color[z]);
		if (rgb[z] < 0 || rgb[z] > 255)
			return (ft_free_map(color), free(str), 0);
	}
	ft_rgb_to_int(map, rgb, color_type);
	return (free(str), ft_free_map(color), 1);
}

/**
 * @brief Validates and stores a texture token from the map configuration.
 * @param game Pointer to the game structure.
 * @param i Line index in the map grid.
 * @param j Column index in the map grid.
 * @param tex_type Texture type index (0=NO, 1=SO, 2=WE, 3=EA).
 * @return 1 if the texture token is valid, 0 otherwise.
 */
int	ft_valid_textoken(t_game *game, int i, int j, int tex_type)
{
	int		len;

	while (game->map.grid[i][j] == ' ')
		j++;
	len = game->map.width[i] - j;
	if (game->textures[tex_type].addr != NULL)
	{
		printf("Error: Map with repeated texture");
		return (0);
	}
	game->textures[tex_type].addr = ft_substr(game->map.grid[i], j, len);
	if (!game->textures[tex_type].addr)
		return (0);
	return (1);
}

/**
 * @brief Validates a token type and calls the appropriate validation function.
 * @param game Pointer to the game structure.
 * @param i Line index in the map grid.
 * @param j Column index in the map grid.
 * @param token_type Character representing the token type (N, S, W, E, F, C).
 * @return 1 if the token is valid, 0 otherwise.
 */
int	ft_valid_token(t_game *game, int i, int j, char token_type)
{
	if (game->map.grid[i][j] == 'N' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j + 2, 0));
	if (game->map.grid[i][j] == 'S' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j + 2, 1));
	if (game->map.grid[i][j] == 'W' && game->map.grid[i][j + 1] == 'E')
		return (ft_valid_textoken(game, i, j + 2, 2));
	if (game->map.grid[i][j] == 'E' && game->map.grid[i][j + 1] == 'A')
		return (ft_valid_textoken(game, i, j + 2, 3));
	if (game->map.grid[i][j] == 'F')
		return (ft_valid_colortoken(&game->map, i, 'F'));
	if (game->map.grid[i][j] == 'C')
		return (ft_valid_colortoken(&game->map, i, 'C'));
	return (0);
}
