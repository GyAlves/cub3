/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bola_quadrada.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:33:34 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/06 20:05:12 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOLA_QUADRADA_H
# define BOLA_QUADRADA_H

// Structs
typedef struct s_map {
    int     **grid;         // mapa 2D
    int     width;
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

#endif