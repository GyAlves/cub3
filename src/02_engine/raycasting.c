/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:54:14 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/27 00:32:02 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bola_quadrada.h"
#include "../includes/utils.h"

void    cast_rays(t_game *game)
{
    t_ray   ray;
    int     screen_column;
    int     line_height;
    int     draw_start;
    int     draw_end;
    static int call_count = 0;

    if (call_count == 0)
    {
        printf("DEBUG: cast_rays called\n");
        printf("DEBUG: WIDTH_SIZE = %d, HIGHT_SIZE = %d\n", WIDTH_SIZE, HIGHT_SIZE);
    }
    call_count++;

    // Debug: Clear screen to blue to test if rendering works - DIRECT WRITE
    int *buffer = (int *)game->img_data;
    int total_pixels = WIDTH_SIZE * HIGHT_SIZE;
    int i = 0;
    while (i < total_pixels)
    {
        buffer[i] = 0x0000FF;  // Blue
        i++;
    }

    if (call_count == 1)
        printf("DEBUG: Filled screen with blue (direct write)\n");

    screen_column = 0;
    while (screen_column < WIDTH_SIZE)
    {
        ray.camera_x = (2 * screen_column) / (double)WIDTH_SIZE - 1;
        ray.ray_direction_x = game->player.dir_x + game->player.plane_x * ray.camera_x;
        ray.ray_direction_y = game->player.dir_y + game->player.plane_y * ray.camera_x;

        ray.map_x = (int)game->player.pos_x;
        ray.map_y = (int)game->player.pos_y;

        ray.delta_dist_x = fabs(1 / ray.ray_direction_x);
        ray.delta_dist_y = fabs(1 / ray.ray_direction_y);

        if (ray.ray_direction_x < 0)
        {
            ray.step_x = -1;
            ray.side_dist_x = (game->player.pos_x - ray.map_x) * ray.delta_dist_x;
        }
        else
        {
            ray.step_x = 1;
            ray.side_dist_x = ((ray.map_x + 1.0 ) - game->player.pos_x) * ray.delta_dist_x;
        }

        if (ray.ray_direction_y < 0)
        {
            ray.step_y = -1;
            ray.side_dist_y = (game->player.pos_y - ray.map_y) * ray.delta_dist_y;
        }
        else
        {
            ray.step_y = 1;
            ray.side_dist_y = (ray.map_y + 1.0 - game->player.pos_y) * ray.delta_dist_y;
        }

        ray.hit = 0;
        while (ray.hit == 0)
        {
            if (ray.side_dist_x < ray.side_dist_y)
            {
                ray.side_dist_x += ray.delta_dist_x;
                ray.map_x += ray.step_x;
                ray.side = 0;
            }
            else
            {
                ray.side_dist_y += ray.delta_dist_y;
                ray.map_y += ray.step_y;
                ray.side = 1;
            }

            if (ray.map_x < 0 || ray.map_y < 0 || ray.map_y >= game->map.height
                || ray.map_x >= game->map.width[ray.map_y])
                ray.hit = 1;
            else if (game->map.grid[ray.map_y][ray.map_x] == '1')
                ray.hit = 1;
        }

        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - game->player.pos_x + (1 - ray.step_x) / 2) / ray.ray_direction_x;
        else
            ray.perp_wall_dist = (ray.map_y - game->player.pos_y + (1 - ray.step_y) / 2) / ray.ray_direction_y;
        
        line_height = (int)(HIGHT_SIZE / ray.perp_wall_dist);
        draw_start = -line_height / 2 + HIGHT_SIZE / 2;
        if (draw_start < 0)
            draw_start = 0;
        
        draw_end = line_height / 2 + HIGHT_SIZE / 2;
        if (draw_end >= HIGHT_SIZE)
            draw_end = HIGHT_SIZE - 1;
        
        int y = draw_start;
        while (y < draw_end)
        {
            int color =  0xFF0000;
            if (ray.side == 1)
                color = 0x990000;
            put_pixel(game, screen_column, y, color);
            y++;
        }

        screen_column++;
    }
}
  