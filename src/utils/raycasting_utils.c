/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 20:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/utils.h"

void	clear_screen(t_game *game)
{
	int	*buffer;
	int	total_pixels;
	int	i;

	buffer = (int *)game->img_data;
	total_pixels = WIDTH_SIZE * HIGHT_SIZE;
	i = 0;
	while (i < total_pixels)
	{
		buffer[i] = 0x0000FF;
		i++;
	}
}

void	init_ray(t_ray *ray, t_player *player, int screen_column)
{
	ray->camera_x = (2 * screen_column) / (double)WIDTH_SIZE - 1;
	ray->ray_direction_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_direction_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_direction_x);
	ray->delta_dist_y = fabs(1 / ray->ray_direction_y);
}

void	setup_ray_step(t_ray *ray, t_player *player)
{
	if (ray->ray_direction_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1.0) - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_direction_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	calculate_perp_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_direction_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_direction_y;
}
