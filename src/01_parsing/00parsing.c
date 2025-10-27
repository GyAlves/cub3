/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:38:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/27 18:54:07 by jucoelho         ###   ########.fr       */
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
		//	printf("entrou no while cut map->grid[%d][%d] == %d\n", i, j, (int)map->grid[i][j]);
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



int	ft_compact_map2(t_game *game)
{
	int	i;
	int	j;
	
	printf("entrou no compact map 2\n\n");
	i = game->map.height - 1;
	while (game->map.grid[i] > 0)
	{
		if (game->map.grid[i][0] == '\0')
		{
			printf("entrou no 1º game->map.grid[%d][0] == vazio \n", i);
			game->map.grid[i] = NULL;
			game->map.width[i] = -1;
			game->map.height -= 1;
			i++;
		}
		else if (game->map.grid[i][0] == ' ')
		{
			j = 0;
			printf("entrou no 2º game->map.grid[%d][0] == vazio\n", i);
			while (game->map.grid[i][j] == ' ' && j < game->map.width[i])
			{
				printf("entrou no WHILE Game->map.grid[%d][%d] == ' ' %c && %d < game->map.width %d\n", i, j, game->map.grid[i][j], j, game->map.width[i]);
				j++;
			}
			if (game->map.grid[i][j] == '\0')
			{
				printf("entrou no IF Game->map.grid[%d][%d] == ' ' %c && %d < game->map.width %d\n", i, j, game->map.grid[i][j], j, game->map.width[i]);
				game->map.grid[i] = NULL;
				game->map.width[i] = -1;
				game->map.height -= 1;
				i++;
			}
		}
		else
		{
			printf("entrou no else\n");
			break;
		}
	}
	return (1);
}

/*int	ft_compact_map(t_game *game, int start)
{
	int	z = 0;

	while (z + start < game->map.height)// 0 +start menor altura do mapa 
	{
		game->map.grid[z] = game->map.grid[z + start]; 
		game->map.width[z] = game->map.width[z + start];
		z++;
	}
	while (z < game->map.height)
	{
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z++;
	}
	game->map.height -= start;
	return (1);
}*/

int	ft_parse_file(char *filename, t_game *game)
{
	if (!ft_val_extension(filename))
		return (0);
	if (!ft_read_map(&game->map, filename))
		return (0);
	ft_printf("Após read map\n\n");
	ft_debug_map(&game->map);
	for (int i = 0; i < 4; ft_debug_textures(&game->textures[i++]));
	if (!ft_lexer(game))
		return (0);
	ft_printf("Após lexer\n\n");
	ft_debug_map(&game->map);
	for (int i = 0; i < 4; ft_debug_textures(&game->textures[i++]));
	if(!ft_verifytexcolor(game))
		return (0);
	ft_elimine_space(&game->map);
	//ft_debug_map(&game->map);
	//ft_debug_textures(&game->textures);
	//ft_compact_map2(game);
	//ft_debug_map(&game->map);
	//ft_debug_textures(&game->textures);
	if (!ft_val_elem(&game->map))
		return (0);
	return (1);
}