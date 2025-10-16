/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:38:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/16 19:22:39 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Validates map content, walls, and boundaries.
 *
 * @param map Pointer to the map structure.
 * @return 1 if valid, 0 otherwise.
 */
int	ft_val_elem(t_map *map)
{
	if (!ft_mapcontent(map))
		return (0);
	if (!ft_mapwall1(map))
		return (0);
	if (!ft_map_sidewall(map))
		return (0);
	return (1);
}

/**
 * @brief Lê o mapa de um arquivo e armazena em map->grid.
 * 
 * @param map Ponteiro para a struct t_map onde o mapa será armazenado.
 * @param filename Caminho do arquivo que contém o mapa.
 * 
 * @return int Retorna 1 em sucesso, 0 em caso de erro.
 */
int	ft_read_map(t_map *map, char *filename)
{
	int		fd;
	int		i;

	i = 0;
	if (!ft_count_map_lines(map, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	map->width = malloc(sizeof(int) * (map->height));
	if (!ft_error_mem(&map->grid) || !ft_error_mem(&map->width))
		return (0);
	while ((map->grid[i] = get_next_line(fd)) != NULL)
	{
		if (map->grid[i][ft_strlen(map->grid[i]) - 1] == '\n')
			map->grid[i][ft_strlen(map->grid[i]) - 1] = '\0';
		map->width[i] = ft_strlen(map->grid[i]);
		i++;
	}
	map->grid[i] = NULL;
	close(fd);
	return (1);
}

/**
 * @brief Check if the file has a ".cub" extension and can be opened.
 *
 * @param filename File name to check.
 * @return int 1 if valid, 0 otherwise.
 */
int	ft_val_extension(char *filename)
{
	int		fd;
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		ft_printf("Error:\nInvalid file extension.\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (0);
	}
	close(fd);
	return (1);
}

int	ft_parse_file(char *filename, t_game *game)
{
	if (!ft_val_extension(filename))
		return (0);
	if (!ft_read_map(&game->map, filename))
		return (0);
	int j = 0;
	int i = 0;
	if (game->map.grid && game->map.grid[0])
	{
		while (i < game->map.height)
		{
			printf("\033[94mgame->map.grid[%2d][width %2d] = %s\n", i, game->map.width[i], game->map.grid[i]);
			i++;
		}
	}
	if (!ft_lexer(game))
		return (0);
	j = 0;
	i = 0;
	if (game->map.grid && game->map.grid[0])
	{
		while (i < game->map.height)
		{
			printf("\033[90mgame->map.grid[%2d][width %2d] = %s\n", i, game->map.width[i], game->map.grid[i]);
			i++;
		}
	}
	if (!ft_val_elem(&game->map))
		return (0);
	return (1);
}
