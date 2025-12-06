/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:50:15 by jucoelho          #+#    #+#             */
/*   Updated: 2025/12/06 12:58:38 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks for error condition and exits if error is found.
 * @param i Integer value to check (exits if -1).
 * @return 1 if no error, otherwise exits the program.
 */
int	ft_error(int i)
{
	if (i == -1)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

/**
 * @brief Checks if memory allocation succeeded and exits on failure.
 * @param ptr Pointer to check for NULL.
 * @return 1 if pointer is valid, otherwise exits the program.
 */
int	ft_error_mem(void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf("Error:\nMemory allocating\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 * @param ptr Double pointer to the array of strings to free.
 * @return NULL after freeing all memory.
 */
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
