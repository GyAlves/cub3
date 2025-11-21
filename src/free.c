/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:55:51 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/30 22:39:15 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

/**
 * @brief Frees a string if it is not NULL.
 * @param str Pointer to the string to be freed.
 */
void	ft_free_str(char *str)
{
	if (str)
		free(str);
}

/**
 * @brief Frees texture file paths allocated during parsing.
 * @param textures Array of texture structures.
 */
void	ft_free_tex(t_texture *textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i].addr != NULL)
			free(textures[i].addr);
		i++;
	}
}

/**
 * @brief Frees the map grid and width array.
 * @param game Pointer to the game structure.
 */
void	ft_free_grid(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (i < game->map.height)
		{
			if (game->map.grid[i])
			{
				free(game->map.grid[i]);
				game->map.grid[i] = NULL;
			}
			i++;
		}
	}
	if (game->map.width != NULL)
	{
		free(game->map.width);
		game->map.width = NULL;
	}
	if (game->map.grid != NULL)
	{
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

/**
 * @brief Frees all allocated resources of the game.
 * @param game Pointer to the game structure.
 * 
 * Destroys MLX images, window, and display.
 * Frees map grid and texture paths.
 * Does not free the game struct itself.
 */
void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	while (i < 4)
	{
		if (game->mlx && game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	ft_free_grid(game);
#ifdef __linux__
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
#endif
	ft_free_tex(game->textures);
}
