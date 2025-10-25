/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/24 19:47:51 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_rgb_to_int(t_map *map, int *rgb, char color_type)
{
	if (color_type == 'F')
		return ((map->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[3]), 1);
	else if (color_type == 'C')
		return ((map->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[3]), 1);
	else if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[3] < 0 || rgb[3] > 255)
		return (0);
	return (0);
}

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
	z = 0;
	while (z < 3)
	{
		rgb[z] = ft_atoi(color[z]);
		if (rgb[z] < 0 || rgb[z] > 255)
			return (ft_free_map(color), free(str), 0);
		z++;
	}
	ft_rgb_to_int(map, rgb, color_type);
	free(str);
	ft_free_map(color);
	return (1);
}

int	ft_valid_textoken(t_game *game, int i, int j, int tex_type)
{
	int		len;

	j += 3;
	len = ft_strlen(game->map.grid[i]);
	if (game->textures[tex_type].addr != NULL)
	{
		printf("Error: Map with repeated texture");
		return (0);
	}
	game->textures[tex_type].addr = ft_substr(game->map.grid[i], j, len);
	if (!game->textures[tex_type].addr)
		return (0);
	return (len);
}

int	ft_valid_token(t_game *game, int i, int j, char token_type)
{
	if (game->map.grid[i][j] == 'N' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j, 0));
	if (game->map.grid[i][j] == 'S' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j, 1));
	if (game->map.grid[i][j] == 'W' && game->map.grid[i][j + 1] == 'E')
		return (ft_valid_textoken(game, i, j ,2));
	if (game->map.grid[i][j] == 'E' && game->map.grid[i][j + 1] == 'A')
		return (ft_valid_textoken(game, i, j, 3));
	if (game->map.grid[i][j] == 'F')
		return (ft_valid_colortoken(&game->map, i, 'F'));
	if (game->map.grid[i][j] == 'C')
		return (ft_valid_colortoken(&game->map, i, 'C'));
	return (1);
}
int	ft_verifytexcolor(t_game *game)
{
	int	j;
	j = 0;
	while(j < 4)
	{
		if (game->textures[j].addr == NULL)
			return(ft_printf("Error: Map texture incomplete %d\n", j), 0);
		j++;
	}
	j = 0;
	if (game->map.ceiling_color == -1 || game->map.floor_color == -1)
		return(ft_printf("Error: Map color incomplete\n"), 0);
	return (1);
}

int	ft_process_line(t_game *game, int *i, int *j)
{
	int		z = 0;
	char	*possib_char = "NSWEFC";

	while (game->map.grid[*i][*j] == '\0')
		(*i)++;
	if (game->map.grid[*i][*j] == ' ')
	{
		(*j)++;
		return (0);
	}
	while (possib_char[z] != '\0' && game->map.grid[*i][*j] != possib_char[z])
		z++;
	if (game->map.grid[*i][*j] == possib_char[z])
	{
		if (ft_valid_token(game, *i, *j, possib_char[z]))
		{
			free(game->map.grid[*i]);
			(*i)++;
			*j = 0;
			return (0);
		}
	}
	return (-1);
}

int	ft_compact_map(t_game *game, int start)
{
	int	z = 0;

	while (z + start < game->map.height)
	{
		game->map.grid[z] = game->map.grid[z + start];
		game->map.width[z] = game->map.width[z + start];
		z++;
	}
	while (z < game->map.height)
	{
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z++;
	}
	game->map.height -= start;
	return (1);
}

int	ft_lexer(t_game *game)
{
	int	i = 0;
	int	j = 0;
	int	result = 0;

	while (i < game->map.height)
	{
		result = ft_process_line(game, &i, &j);
		if (result == -1)
		{
			if (game->map.grid[i][j] == '\0')
			{
				while (game->map.grid[i][j] == '\0')
					i++;
			}
			else
				return (ft_compact_map(game, i));
		}
	}
	return (0);
}
