/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-a <galves-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:50:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/12/05 19:52:50 by galves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"

int	render_frame(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
