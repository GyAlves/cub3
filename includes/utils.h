/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:34:09 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/12/05 20:10:32 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "bola_quadrada.h"

void	put_pixel(t_game *game, int x, int y, int color);

// Signal handling
void	setup_signal_handlers(t_game *game);

#endif