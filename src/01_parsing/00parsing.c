/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:38:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/24 21:03:09 by jucoelho         ###   ########.fr       */
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
	int	player;

	player = 0;
	if (!ft_mapcontent(map))
		return (0);
	if (!ft_mapwall1(map))
		return (0);
	if (!ft_map_sidewall(map))
		return (0);
	player = ft_mapposition(map);
	if (player < 0)
		return (ft_printf("Error: No player in the map\n"), 0);
	if (player > 0)
		return (ft_printf("Error: %d players in the map\n", player + 1), 0);
	return (1);
}

void	ft_elimine_space(t_map *map)
{
	int	i;
	int	j;

	i = map->height - 1;
	j = 0;
	if (i >= 0)
	{
		while (map->grid[i][j] == ' ')
			j++;
		if (map->grid[i][j] == '\0')
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
			map->height -= 1;
			i++;
		}
		else
		{
			j = 0;
		}
	}
	i = 0;
	while (i < map->height)
	{
		//printf("width %d\n", map->width[i]);
		j = (map->width[i]) - 1;
		//printf("j entrou no while map->grid[%d][%d] == %c\n", i, j, map->grid[i][j]);
		while(j >= 0 && map->grid[i][j] == ' ')
		{
			printf("entrou no while cut map->grid[%d][%d] == %d\n", i, j, (int)map->grid[i][j]);
			map->grid[i][j] = '\0';
			j--;
		}
		map->width[i] = j + 1;
		i++;
	}
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
	if (!ft_lexer(game))
		return (0);
	if(!ft_verifytexcolor(game))
		return (0);
	ft_debug_map(&game->map);
	ft_printf("\033[1;45mEntrou no Debug_textures\033[0m\n");
	for (int i = 0; i < 4; i++)
	{
		char	tex[] = {'N', 'S', 'E', 'W'};
		printf("Texture %c\n", tex[i]);
		ft_debug_textures(&game->textures[i]);
	}
	ft_elimine_space(&game->map);
	ft_debug_map(&game->map);
	ft_printf("\033[1;45mEntrou no Debug_textures\033[0m\n");
	for (int i = 0; i < 4; i++)
	{
		char	tex[] = {'N', 'S', 'E', 'W'};
		printf("Texture %c\n", tex[i]);
		ft_debug_textures(&game->textures[i]);
	}
	if (!ft_val_elem(&game->map))
		return (0);
	return (1);
}
