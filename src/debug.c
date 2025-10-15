/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:57:29 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/14 16:27:06 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bola_quadrada.h"

void	ft_debug_map(t_map *map)
{
	int	i;

	i = 0;
	ft_printf("\033[1;45mEntrou no Debug_map\033[0m\n");
	if (!map)
	{
		ft_printf("\033[1;41mErro: map é NULL\033[0m\n");
		return ;
	}
	if (map->grid && map->grid[0])
	{
		while (i < map->height)
		{
			ft_printf("map->grid[%d] = %s\n", i, map->grid[i]);
			i++;
		}
	}
	i = 0;
	while (i < map->height)
	{
		ft_printf("map->width = %d\n", map->width[i]);
		i++;
	}
	if (map->height != -1)
		ft_printf("map->height = %d\n", map->height);
	if (map->floor_color != -1)
		ft_printf("map->floor_color = %d\n", map->floor_color);
	if (map->ceiling_color != -1)
		ft_printf("map->ceiling_color = %d\n", map->ceiling_color);
	if (map->player_x != -1)
		ft_printf("map->player_x = %d\n", map->player_x);
	if (map->player_y != -1)
		ft_printf("map->player_y = %d\n", map->player_y);
	if (map->player_dir != '\0')
		ft_printf("map->player_dir = %c\n", map->player_dir);
}

void	ft_debug_textures(t_texture *textures)
{
	if (textures->img != NULL)
		ft_printf("textures->img = %s", textures->img);
	if (textures->addr != NULL)
		ft_printf("textures->addr = %s", textures->addr);
	if (textures->width != -1)
		ft_printf("textures->addr = %d", textures->width);
	if (textures->height != -1)
		ft_printf("textures->addr = %d", textures->height);
}