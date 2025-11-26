/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:50:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/26 19:56:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"

int render_frame(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}