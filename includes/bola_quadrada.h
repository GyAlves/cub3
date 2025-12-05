/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bola_quadrada.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:33:34 by galves-a          #+#    #+#             */
/*   Updated: 2025/12/05 19:52:50 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOLA_QUADRADA_H
# define BOLA_QUADRADA_H

//# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
#  define WIDTH_SIZE 800
#  define HIGHT_SIZE 600
//# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "libft_utils.h"

# include "parsing.h"

// Structs

typedef struct s_map {
	char		**grid;	 // mapa 2D
	int			*width;
	int			height;
	int			floor_color;	// cor do chão (RGB)
	int			ceiling_color;  // cor do teto (RGB)
	int			player_x;	   // posição inicial
	int			player_y;
	char		player_dir;	 // N, S, E, W
}	t_map;

typedef struct s_texture {
	void		*img;
	char		*addr;
	char		*data;
	int			width;
	int			height;
	int			line_len;
	int			bpp;
}	t_texture;

typedef struct s_player {
	double		pos_x;
	double		pos_y;
	double		dir_x;		// vetor direção
	double		dir_y;
	double		plane_x;	// plano da câmera
	double		plane_y;
}	t_player;

typedef struct s_game {
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	t_map		map;
	t_player	player;
	t_texture	textures[4];  // N, S, E, W
	int			bpp;
	int			line_len;
	int			endian;
}	t_game;

typedef struct s_ray {
	double	camera_x;
	double	ray_direction_x;
	double	ray_direction_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
} t_ray;

typedef struct s_draw_params {
	int		screen_column;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_index;
	int		tex_x;
}	t_draw_params;

typedef struct s_dir_params
{
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_dir_params;

int		main(int argc, char **argv);
void	ft_debug_map(t_map *map);
void	ft_debug_textures(t_texture *textures);
void	ft_free_game(t_game *game);

#endif