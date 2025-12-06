/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:52:55 by jucoelho          #+#    #+#             */
/*   Updated: 2025/12/06 14:17:53 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Loads all textures from XPM files into memory.
 * @param game Pointer to the game structure.
 * @return 1 on success, 0 on error.
 * 
 * Loads 4 textures (NO, SO, WE, EA) using mlx_xpm_file_to_image,
 * validates dimensions, and retrieves data pointers for pixel access.
 */
int	ft_load_textures(t_game *game)
{
	int	i;
	int	endian;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image
			(game->mlx, game->textures[i].addr,
				&game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
			return ((ft_printf("Error loading texture: %s\n",
						game->textures[i].addr), 0));
		if (game->textures[i].width <= 0 || game->textures[i].height <= 0)
			return (ft_printf("Error: Invalid texture %d dimensions\n", i), 0);
		game->textures[i].data = mlx_get_data_addr(
				game->textures[i].img, &game->textures[i].bpp,
				&game->textures[i].line_len, &endian);
		if (!game->textures[i].data)
			return (ft_printf("Error getting texture data: %s\n",
					game->textures[i].addr), 0);
		i++;
	}
	return (1);
}

/**
 * @brief Initializes MLX, creates window, and loads textures.
 * @param game Pointer to the game structure.
 * @return 1 on success, 0 on error.
 * 
 * Sets up the graphical environment and prepares resources
 * for rendering the game.
 */
int	ft_new_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error initializing Minilibx.\n");
		return (0);
	}
	game->win = mlx_new_window
		(game->mlx, WIDTH_SIZE, HIGHT_SIZE, "Bola Quadrada");
	if (!game->win)
	{
		ft_printf("Error creating window.\n");
		return (0);
	}
	if (!ft_load_textures(game))
		return (0);
	return (1);
}
