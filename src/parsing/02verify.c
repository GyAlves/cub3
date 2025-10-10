/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02verify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:55 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/09 18:48:47 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int	ft_verify_map(t_map *map)
{
	if (!ft_mapcontent(map))
		exit(EXIT_FAILURE);
	if (!ft_mapposition(map))
		exit(EXIT_FAILURE);
	return (1);
}

int	ft_verify(char *cub, t_map *map)
{
	if (!ft_read_map(&map, cub[1]))
	{
		ft_printf("Error:\nInvalid map.\n");
		return (0);
	}	
	if (!ft_verify_map(&map))
	{
		return (0);
	}
	if (!ft_new_window(&map))
	{
		ft_printf("Error:\niniciating window.\n");
		return (0);
	}
	return (1);
}

