/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_elements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:06:48 by jucoelho          #+#    #+#             */
/*   Updated: 2025/12/05 21:08:01 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			printf("Error:\nMap with repeated floor color\n");
			return (0);
		}
		return ((map->floor_color = (rgb[0] << 16)
				| (rgb[1] << 8) | rgb[2]), 1);
	}
	else if (color_type == 'C')
	{
		if (map->ceiling_color != -1)
		{
			printf("Error:\nMap with repeated ceiling color\n");
			return (0);
		}
		return ((map->ceiling_color = (rgb[0] << 16)
				| (rgb[1] << 8) | rgb[2]), 1);
	}
	else if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		return (0);
	return (0);
}

static	int	ft_is_valid_rgbtoken(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
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
	if (!color[0] || !color[1] || !color[2] || color[3])
		return (ft_free_map(color), free(str), 0);
	z = -1;
	while (++z < 3)
	{
		rgb[z] = ft_atoi(color[z]);
		if (!ft_is_valid_rgbtoken(color[z]) || rgb[z] < 0 || rgb[z] > 255)
			return (ft_free_map(color), free(str), 0);
	}
	if (!ft_rgb_to_int(map, rgb, color_type))
		return (((free(str)), (ft_free_map(color))), 0);
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
	int		end_space;

	while (game->map.grid[i][j] == ' ')
		j++;
	end_space = game->map.width[i] - 1;
	while (game->map.grid[i][end_space] == ' ')
		end_space--;
	len = (end_space - j) + 1;
	if (game->textures[tex_type].addr != NULL)
	{
		printf("Error: Map with repeated texture\n");
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
	(void)token_type;
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
