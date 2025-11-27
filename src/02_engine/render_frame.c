/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:50:44 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/26 22:56:52 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/engine.h"

int render_frame(t_game *game)
{
    static int frame_count = 0;

    if (frame_count == 0)
    {
        printf("DEBUG: render_frame called (first time)\n");
        printf("DEBUG: img = %p\n", game->img);
        printf("DEBUG: img_data = %p\n", game->img_data);
        printf("DEBUG: bpp = %d\n", game->bpp);
        printf("DEBUG: line_len = %d\n", game->line_len);
    }

    if (frame_count < 5)
        printf("DEBUG: render_frame #%d - about to call cast_rays\n", frame_count);

    cast_rays(game);

    if (frame_count < 5)
        printf("DEBUG: render_frame #%d - about to call mlx_put_image_to_window\n", frame_count);

    // Test: Draw directly to window with mlx_pixel_put
    if (frame_count < 2)
    {
        printf("DEBUG: Testing mlx_pixel_put...\n");
        int y = 0;
        while (y < 100)
        {
            int x = 0;
            while (x < 100)
            {
                mlx_pixel_put(game->mlx, game->win, x, y, 0x00FF00);  // Green square
                x++;
            }
            y++;
        }
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    if (frame_count < 5)
        printf("DEBUG: render_frame #%d - completed\n", frame_count);

    frame_count++;
    return (0);
}