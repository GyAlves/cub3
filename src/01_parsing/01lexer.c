/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/12/06 12:01:30 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Processes a single line to validate and parse map tokens.
 * @param game Pointer to the game structure.
 * @param i Pointer to the current line index.
 * @param j Pointer to the current column index.
 * @return 0 if a valid token is found and processed, 1 otherwise.
 */
int	ft_process_line(t_game *game, int *i, int *j)
{
	int		z;
	char	*possib_char;

	z = 0;
	possib_char = "NSWEFC";
	while (*i < game->map.height && game->map.grid[*i][*j] == '\0')
		(*i)++;
	while (*j < game->map.width[*i] && game->map.grid[*i][*j] == ' ')
		(*j)++;
	if (*j >= game->map.width[*i])
		return (*i = game->map.height, ft_printf(
				"Error:\nUnexpected content between elements\n"), 0);
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

/**
 * @brief Compacts the map by removing processed configuration lines.
 * @param game Pointer to the game structure.
 * @param start Index from which to start compacting the map.
 * @return 1 on success.
 */
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

/**
 * @brief Processes configuration lines and compacts the map.
 * @param game Pointer to the game structure.
 * @param i Pointer to the current line index.
 * @param j Pointer to the current column index.
 * @return Result of ft_compact_map or 0 if processing continues.
 */
static int	ft_lexer2(t_game *game, int *i, int *j)
{
	while (*i < game->map.height)
	{
		if (ft_process_line(game, i, j))
		{
			if (game->map.grid[*i][*j] == '\0')
			{
				while (game->map.grid[*i][*j] == '\0')
					(*i)++;
			}
			else
				return (ft_compact_map(game, *i));
		}
	}
	return (0);
}

/**
 * @brief Parses and validates map configuration tokens (textures and colors).
 * @param game Pointer to the game structure.
 * @return 1 if parsing is successful, 0 on error.
 * 
 * Removes trailing empty lines, 
 * processes configuration tokens (NO, SO, WE, EA, F, C),
 * and compacts the map by removing processed configuration lines.
 */
int	ft_lexer(t_game *game)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = game->map.height - 1;
	while (game->map.grid[z][0] == '\0' && z > 0)
	{
		free(game->map.grid[z]);
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z--;
	}
	if (z == 0)
	{
		ft_printf("Error:\nEmpty map\n");
		return (0);
	}
	game->map.height = z + 1;
	return (ft_lexer2(game, &i, &j));
}
