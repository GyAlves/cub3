/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:39:42 by galves-a          #+#    #+#             */
/*   Updated: 2025/11/26 19:56:17 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"
#include "../includes/controls.h"

void    game_loop(t_game *game)
{
    mlx_loop_hook(game->mlx, render_frame, game);
    mlx_loop(game->mlx);
}

int init_engine(t_game *game)
{
    game->img = mlx_new_image(game->mlx, WIDTH_SIZE, HIGHT_SIZE);
    if (!game->img)
        return (1);
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
    if (!game->img_data)
        return (1);
    init_player(game);
    setup_controls(game);
    return (0);
}