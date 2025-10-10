/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:38:44 by galves-a          #+#    #+#             */
/*   Updated: 2025/10/10 17:28:12 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	ft_init_tmap (t_map *map)
{
	map->grid = NULL;
	map->width = -1;
	map->height = -1;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = -1;
}


void	ft_add_texture(t_game *game, char *cub, int j, int start)
{
	if (game->map.grid[j] == "N" && game->map.grid[j + 1] == "O")
		game->textures[1].addr = ft_substr(cub, start, j -start);
	if (game->map.grid[j] == "S" && game->map.grid[j + 1] == "O")
		game->textures[2].addr = ft_substr(cub, start, j -start);
	if (game->map.grid[j] == "W" && game->map.grid[j + 1] == "E")
		game->textures[3].addr = ft_substr(cub, start, j -start);
	if (game->map.grid[j] == "E" && game->map.grid[j + 1] == "A")
		game->textures[4].addr = ft_substr(cub, start, j -start);
	if (game->map.grid[j] == "F")
		game->map.floor_color = ft_atoi(ft_substr(cub, start, j -start));
	if (game->map.grid[j] == "C")
		game->map.ceiling_color = ft_atoi(ft_substr(cub, start, j -start));
}

int	ft_val_elem(t_game *game)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j] && game->map.grid[i][j] == " ")
		{
			j++;
		}
		if (game->map.grid[i][j] == '\0')
			i++;
		else
		{
			while (game->map.grid[i][j] && game->map.grid[i][j] != " ")
				j++;
			ft_add_texture(&game, game->map.grid[i], j, start);
		}
	}
	return (i);
}

int	ft_read_map(t_map *map, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if (!ft_count_map_lines(map, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!ft_error_mem(&map->grid))
		return (0);
	map->grid[map->height] = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[i] = line;
		i++;
	}
	close(fd);
	return (1);
}

int	ft_val_extension(t_map *map, char *filename)
{
	int		fd;
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (!ft_error(fd))
		return (0);
}

int ft_parse_file(char *filename, t_game *game)
{
	t_map		map;

	if (!ft_verify(filename, &map))
		return (0);
	ft_val_extension(&map, filename);
	ft_read_map(&map, filename);
	ft_val_elem(game);
	
	return (0);
}