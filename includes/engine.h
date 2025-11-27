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
void    cast_rays(t_game *game);

#endif