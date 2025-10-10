/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:50:15 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/08 17:21:37 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

int	ft_error(int i)
{
	if (i == -1)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_error_mem(void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf("Error:\nMemory allocating");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_error_ptrptr(char **ptr)
{
	if (ptr == NULL)
	{
		ft_printf("Error\nMemory allocating");
		exit(EXIT_FAILURE);
	}
	return (1);
}

char	**ft_free_map(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}
