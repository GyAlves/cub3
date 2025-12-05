/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:37:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/12/05 19:58:20 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if ((x < 0 || x >= WIDTH_SIZE) || (y < 0 || y >= HIGHT_SIZE))
		return ;
	pixel = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(int *)pixel = color;
}
