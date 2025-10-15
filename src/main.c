/* ************************************************************************** */
/*	                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:01:01 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/06 19:43:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

/**
 * Initializes a texture struct.
 * Sets img and addr to NULL, width and height to -1.
 */
static void	ft_init_texture(t_texture *textures)
{
	textures->img = NULL;
	textures->addr = NULL;
	textures->width = -1;
	textures->height = -1;
}

/**
 * Initializes a map struct.
 * Sets pointers to NULL, size and colors to -1,
 * and player_dir to '\0'.
 */
static void	ft_init_map(t_map *map)
{
	map->grid = NULL;
	map->width = NULL;
	map->height = -1;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
}

/**
 * Initializes a player struct.
 * Sets position and direction vectors to -1.
 */
static void	ft_init_player(t_player *player)
{
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_x = -1;
	player->dir_y = -1;
	player->plane_x = -1;
	player->plane_y = -1;
}

/**
 * Initializes the game struct.
 * Calls init functions for map, player, and textures,
 * and sets mlx and win pointers to NULL.
 */
static void	ft_init_game(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = NULL;
	game->win = NULL;
	ft_init_map(&game->map);
	ft_init_player(&game->player);
	while (i < 4)
	{
		ft_init_texture(&game->textures[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !argv[1])
	{
		ft_printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	ft_init_game(&game);
	// jucoelho
	if (ft_parse_file(argv[1], &game) != 1)
	{
		ft_free_game(&game);
		return (1);
	}
/*
	// galves
	if (init_engine(&game) != 0)
		return (error_exit());

	// galves
	game_loop(&game);

	// galves
	cleanup_engine(&game);

	// ??
	free_game_data(&game);
*/
	ft_debug_map(&game.map);
	ft_printf("\033[1;45mEntrou no Debug_textures\033[0m\n");
	for (int i = 0; i < 4; i++)
	{
		char	tex[] = {'N', 'S', 'E', 'W'};
		printf("Texture %c\n", tex[i]);
		ft_debug_textures(&game.textures[i]);
	}
	ft_free_game(&game);
	return (0);
}
