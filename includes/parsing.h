/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:42:31 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/30 22:40:42 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "bola_quadrada.h"

typedef struct s_map		t_map;
typedef struct s_texture	t_texture;
typedef struct s_player		t_player;
typedef struct s_game		t_game;

//00 parsing
int		ft_parse_file(char *filename, t_game *game);
int		ft_val_extension(char *filename);
int		ft_read_map(t_map *map, char *filename);
int		ft_val_elem(t_map *map);

//01 lexer
int		ft_lexer(t_game *game);
int		ft_compact_map(t_game *game, int start);
int		ft_process_line(t_game *game, int *i, int *j);

//02 aux
void	ft_elimine_space(t_map *map);
void	ft_trim_trailing_spaces(t_map *map);
int		ft_mapcontent(t_map *map);
int		ft_count_map_lines(t_map *map, char *filename);

//03 map
int		ft_mapposition(t_map *map);
int		ft_map_sidewall(t_map *map);
int		ft_mapwall1(t_map *map);

//04 elements
int		ft_valid_token(t_game *game, int i, int j, char token_type);
int		ft_valid_textoken(t_game *game, int i, int j, int tex_type);
int		ft_valid_colortoken(t_map *map, int i, char color_type);
int		ft_rgb_to_int(t_map *map, int *rgb, char color_type);
int		ft_verifytexcolor(t_game *game);

//05 read map
int		ft_new_window(t_game *game);
int		ft_load_textures(t_game *game);
//int		ft_render_map(t_game *game);
//int		ft_render_tile(t_game *game, int i, int j);
//int		ft_handle_key(int keycode, t_game *game);

//06 error
char	**ft_free_map(char **ptr);
int		ft_error_ptrptr(char **ptr);
int		ft_error_mem(void *ptr);
int		ft_error(int i);

#endif