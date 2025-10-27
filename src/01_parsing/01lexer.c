/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/27 19:49:05 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_process_line(t_game *game, int *i, int *j)
{
	int		z;
	char	*possib_char;

	z = 0;
	possib_char = "NSWEFC";
	while(*i < game->map.height && game->map.grid[*i][*j] == '\0')
		(*i)++;
	while (*j < game->map.width[*i] && game->map.grid[*i][*j] == ' ')
		(*j)++;
	if (*j >= game->map.width[*i])
	{
		*i = game->map.height;
		return (ft_printf("Error: Unexpected content between elements; only empty lines are allowed.\n"), 0);
	}
	while (possib_char[z] != '\0' && game->map.grid[*i][*j] != possib_char[z])
		z++;
	if (game->map.grid[*i][*j] == possib_char[z])
	{
		if (ft_valid_token(game, *i, *j, possib_char[z]))
		{
			(*i)++;
			*j = 0;
			return (0);
		}
	}
	return (1);
}

int	ft_compact_map(t_game *game, int start)
{
	int	z;

	z = 0;
	while (z < start)
	{
		if (game->map.width[z] >= 0)
			free(game->map.grid[z]);
		z++;
	}
	z = 0;
	while (z + start < game->map.height)
	{
		game->map.grid[z] = game->map.grid[z + start];
		game->map.width[z] = game->map.width[z + start];
		z++;
	}
	game->map.height -= start;
	return (1);
}

int	ft_lexer(t_game *game)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = game->map.height - 1;
	ft_printf("entrou no lexer i %d, j %d, z %d\n", i, j, z);
	while (game->map.grid[z][0] == '\0' && z > 0)
	{
		free(game->map.grid[z]);
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z--;
	}
	if (z == 0)
	{
		ft_printf("Error: empty map\n");
		return (0);
	}
	game->map.height = z + 1;
	ft_printf("map.height = %d\n", z + 1);
	while (i < game->map.height)
	{
		if(ft_process_line(game, &i, &j))
		{
			if (game->map.grid[i][j] == '\0')
			{
				while (game->map.grid[i][j] == '\0')
					i++;
			}
			else
				return (ft_compact_map(game, i));
		}
	}
	ft_printf("return 0\n");
	return (0);
}
