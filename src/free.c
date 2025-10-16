/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:55:51 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/16 17:39:12 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

void	ft_free_str(char *str)
{
	free(str);
}

void	ft_free_tex(t_texture *textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i].img != NULL)
			free(textures[i].img);
		if (textures[i].addr != NULL)
			free(textures[i].addr);
		i++;
	}
}

/**
 * Frees all allocated resources of the game.
 * - Frees the map grid.
 * - Destroys MLX images and window.
 * Does not free the game struct itself.
 */
void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.width);
	free(game->map.grid);
	i = 0;
	while (i < 4)
	{
		if (game->mlx)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_free_tex(game->textures);
}
