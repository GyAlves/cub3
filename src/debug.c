/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:57:29 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/30 22:39:06 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

void	ft_debug_map(t_map *map)
{
	int	i;

	i = 0;
	ft_printf("\033[1;44mEntrou no Debug_map\033[0m\n");
	if (!map)
	{
		ft_printf("\033[1;41mErro: map é NULL\033[0m\n");
		return ;
	}
	if (map->grid && map->grid[0])
	{
		while (i < map->height)
		{
			printf("\033[94mmap->grid[%2d][width %2d] = %s\n", i, map->width[i], map->grid[i]);
			i++;
		}
	}
	if (map->height != -1)
		printf("\033[1;37m map->height = %d\033[0m\n", map->height);
	if (map->floor_color != -1)
		printf("\033[0;34m map->floor_color = %d\033[0m\n", map->floor_color);
	if (map->ceiling_color != -1)
		printf("\033[0;34m map->ceiling_color = %d\033[0m\n", map->ceiling_color);
	if (map->player_x != -1)
		printf("\033[94mmap->player_x = %d\n", map->player_x);
	if (map->player_y != -1)
		printf("map->player_y = %d\n", map->player_y);
	if (map->player_dir != '\0')
		printf("\033[0;34m map->player_dir = %c\033[0m\n", map->player_dir);
}

void	ft_debug_textures(t_texture *textures)
{
	if (textures->img != NULL)
		ft_printf("\033[32mimg = %s\033[0m\n", textures->img);
	if (textures->addr != NULL)
		ft_printf("\033[33maddr = %s\033[0m\n", textures->addr);
	if (textures->data != NULL)
		ft_printf("\033[33mdata = %s\033[0m\n", textures->data);
	if (textures->width != -1)
		ft_printf("\033[33mwidth = %d\033[0m\n", textures->width);
	if (textures->height != -1)
		ft_printf("\033[33mheight = %d\033[0m\n", textures->height);
}