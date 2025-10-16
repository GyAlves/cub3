/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:42:31 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/16 17:17:47 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_h
# define PARSING_h

# include "bola_quadrada.h"

typedef struct s_map t_map;
typedef struct s_texture t_texture;
typedef struct s_player t_player;
typedef struct s_game t_game;

//00 parsing
int		ft_val_elem(t_map *map);
int		ft_read_map(t_map *map, char *filename);
int		ft_val_extension(char *filename);
int		ft_parse_file(char *filename, t_game *game);
int		ft_lexer(t_game *game);

//01 error
int		ft_error(int i);
int		ft_error_mem(void *ptr);
int		ft_error_ptrptr(char **ptr);
char	**ft_free_map(char **ptr);

//02 aux
int		ft_mapcontent(t_map *map);
int		ft_count_map_lines(t_map *map, char *filename);

//03 map
int		ft_map_sidewall(t_map *map);
int		ft_mapwall1(t_map *map);

#endif