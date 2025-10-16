/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bola_quadrada.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:33:34 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/16 15:44:47 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOLA_QUADRADA_H
# define BOLA_QUADRADA_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include "parsing.h"

// Structs
typedef struct s_map {
    char    **grid;         // mapa 2D
    int     *width;
    int     height;
    int     floor_color;    // cor do chão (RGB)
    int     ceiling_color;  // cor do teto (RGB)
    int     player_x;       // posição inicialDay 0 — agree scene contract & get one sample scene file from parser.
    int     player_y;
    char    player_dir;     // N, S, E, W
}   t_map;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
}   t_texture;

typedef struct s_player {
    double  pos_x;
    double  pos_y;
    double  dir_x;      // vetor direção
    double  dir_y;
    double  plane_x;    // plano da câmera
    double  plane_y;
}   t_player;

typedef struct s_game {
    void        *mlx;
    void        *win;
    t_map       map;
    t_player    player;
    t_texture   textures[4];  // N, S, E, W
}   t_game;

int		main(int argc, char **argv);
void	ft_debug_map(t_map *map);
void	ft_debug_textures(t_texture *textures);
void	ft_free_game(t_game *game);

#endif  