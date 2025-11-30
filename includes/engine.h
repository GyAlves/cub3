/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:55:09 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/26 22:56:03 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

#include "bola_quadrada.h"

int		init_engine(t_game *game);
int		render_frame(t_game *game);
void	game_loop(t_game *game);
void	init_player(t_game *game);
void	cast_rays(t_game *game);

/* Raycasting utilities */
void	clear_screen(t_game *game);
void	init_ray(t_ray *ray, t_player *player, int screen_column);
void	setup_ray_step(t_ray *ray, t_player *player);
void	calculate_perp_distance(t_ray *ray, t_player *player);

/* Drawing utilities */
int		get_texture_index(t_ray *ray);
int		calculate_wall_texture_x(t_game *game, t_ray *ray, int tex_index);
void	init_wall_drawing(t_ray *ray, int *line_height,
			int *draw_start, int *draw_end);
void	draw_textured_wall(t_game *game, t_draw_params *params);
void	draw_ceiling_floor(t_game *game, int screen_column,
			int draw_start, int draw_end);

#endif