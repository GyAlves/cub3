/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:34:09 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/26 19:41:55 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "bola_quadrada.h"

// Functions
void    put_pixel(t_game *game, int x, int y, int color);

// Signal handling
void	setup_signal_handlers(t_game *game);

#endif