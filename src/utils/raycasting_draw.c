/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/30 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"
#include "../includes/utils.h"

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_direction_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->ray_direction_y > 0)
			return (1);
		else
			return (0);
	}
}

int	calculate_wall_texture_x(t_game *game, t_ray *ray, int tex_index)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist
			* ray->ray_direction_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist
			* ray->ray_direction_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)game->textures[tex_index].width);
	if ((ray->side == 0 && ray->ray_direction_x > 0)
		|| (ray->side == 1 && ray->ray_direction_y < 0))
		tex_x = game->textures[tex_index].width - tex_x - 1;
	return (tex_x);
}

void	init_wall_drawing(t_ray *ray, int *line_height,
		int *draw_start, int *draw_end)
{
	*line_height = (int)(HIGHT_SIZE / ray->perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HIGHT_SIZE / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + HIGHT_SIZE / 2;
	if (*draw_end >= HIGHT_SIZE)
		*draw_end = HIGHT_SIZE - 1;
}

void	draw_textured_wall(t_game *game, t_draw_params *params)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		*texture_data;
	int		color;
	int		y;

	step = 1.0 * game->textures[params->tex_index].height / params->line_height;
	tex_pos = (params->draw_start - HIGHT_SIZE / 2
			+ params->line_height / 2) * step;
	texture_data = (int *)game->textures[params->tex_index].data;
	y = params->draw_start;
	while (y < params->draw_end)
	{
		tex_y = (int)tex_pos & (game->textures[params->tex_index].height - 1);
		tex_pos += step;
		color = texture_data[tex_y * game->textures[params->tex_index].width
			+ params->tex_x];
		put_pixel(game, params->screen_column, y, color);
		y++;
	}
}

void	draw_ceiling_floor(t_game *game, int screen_column,
		int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(game, screen_column, y, game->map.ceiling_color);
		y++;
	}
	y = draw_end;
	while (y < HIGHT_SIZE)
	{
		put_pixel(game, screen_column, y, game->map.floor_color);
		y++;
	}
}
