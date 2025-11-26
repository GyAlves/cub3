/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:37:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/26 19:43:05 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void    put_pixel(t_game *game, int x, int y, int color)
{
    char    *pixel;

    if ((x < 0 || x >= WIDTH_SIZE) || (y < 0 || y >= HIGHT_SIZE))
        return;
    
    pixel = game->img_data + (y * game->line_len + x * (game->bpp/8));
    *(int *)pixel = color;
}