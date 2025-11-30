/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:54:14 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/27 00:32:02 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"
#include "../includes/utils.h"

static void	perform_dda(t_ray *ray, t_map *map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
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
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= map->height
			|| ray->map_x >= map->width[ray->map_y])
			ray->hit = 1;
		else if (map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_height(t_ray *ray, int *draw_start, int *draw_end)
{
	int	line_height;

	line_height = (int)(HIGHT_SIZE / ray->perp_wall_dist);
	*draw_start = -line_height / 2 + HIGHT_SIZE / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + HIGHT_SIZE / 2;
	if (*draw_end >= HIGHT_SIZE)
		*draw_end = HIGHT_SIZE - 1;
}

static void	draw_vertical_line(t_game *game, t_ray *ray, int screen_column)
{
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	calculate_wall_height(ray, &draw_start, &draw_end);
	y = draw_start;
	while (y < draw_end)
	{
		color = 0xFF0000;
		if (ray->side == 1)
			color = 0x990000;
		put_pixel(game, screen_column, y, color);
		y++;
	}
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
	int	screen_column;

	clear_screen(game);
	screen_column = 0;
	while (screen_column < WIDTH_SIZE)
	{
		process_ray(game, screen_column);
		screen_column++;
	}
}
