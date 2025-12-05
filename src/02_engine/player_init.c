/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:30:00 by galves-a          #+#    #+#             */
/*   Updated: 2025/12/05 19:54:00 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"

static void	set_direction(t_player *p, t_dir_params params)
{
	p->dir_x = params.dx;
	p->dir_y = params.dy;
	p->plane_x = params.px;
	p->plane_y = params.py;
}

/**
 * Sets the player's direction and camera plane vectors based on orientation
 * N: dir(0, -1), plane(0.66, 0)
 * S: dir(0, 1), plane(-0.66, 0)
 * E: dir(1, 0), plane(0, 0.66)
 * W: dir(-1, 0), plane(0, -0.66)
 */
static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
		set_direction(player, (t_dir_params){0, -1, 0.66, 0});
	else if (dir == 'S')
		set_direction(player, (t_dir_params){0, 1, -0.66, 0});
	else if (dir == 'E')
		set_direction(player, (t_dir_params){1, 0, 0, 0.66});
	else if (dir == 'W')
		set_direction(player, (t_dir_params){-1, 0, 0, -0.66});
}

/**
 * Initializes the player position and direction from map data
 * Converts grid coordinates to world coordinates
 */
void	init_player(t_game *game)
{
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	set_player_direction(&game->player, game->map.player_dir);
}
