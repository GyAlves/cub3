/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:54:14 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/12/06 14:48:48 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"
#include "../includes/utils.h"

static int	check_hit_condition(t_ray *ray, t_map *map)
{
	if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= map->height)
		return (1);
	if (ray->map_x >= map->width[ray->map_y])
		return (1);
	if (map->grid[ray->map_y][ray->map_x] == '1')
		return (1);
	if (map->grid[ray->map_y][ray->map_x] == ' ')
		return (1);
	return (0);
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	int	max_iterations;

	ray->hit = 0;
	max_iterations = 0;
	while (ray->hit == 0 && max_iterations < 10000)
	{
		max_iterations++;
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->hit = check_hit_condition(ray, map);
	}
}

static void	draw_vertical_line(t_game *game, t_ray *ray, int screen_column)
{
	t_draw_params	params;

	init_wall_drawing(ray, &params.line_height,
		&params.draw_start, &params.draw_end);
	params.screen_column = screen_column;
	params.tex_index = get_texture_index(ray);
	params.tex_x = calculate_wall_texture_x(game, ray, params.tex_index);
	draw_ceiling_floor(game, screen_column,
		params.draw_start, params.draw_end);
	draw_textured_wall(game, &params);
}

static void	process_ray(t_game *game, int screen_column)
{
	t_ray	ray;

	init_ray(&ray, &game->player, screen_column);
	setup_ray_step(&ray, &game->player);
	perform_dda(&ray, &game->map);
	calculate_perp_distance(&ray, &game->player);
	draw_vertical_line(game, &ray, screen_column);
}

void	cast_rays(t_game *game)
{
	int			screen_column;
	static int	printed = 0;

	if (!printed)
		printed = 1;
	clear_screen(game);
	screen_column = 0;
	while (screen_column < WIDTH_SIZE)
	{
		process_ray(game, screen_column);
		screen_column++;
	}
}
