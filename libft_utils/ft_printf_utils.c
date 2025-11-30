/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

int	ft_print_c(int letter)
{
	return (write(1, &letter, 1));
}

int	ft_print_s(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_print_s("(null)"));
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
		count++;
	}
	return (count);
}

int	ft_print_nbr(int n)
{
	char	nb;
	int		count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		count++;
	}
	if (n >= 10)
		count += ft_print_nbr(n / 10);
	nb = (n % 10) + '0';
	count += write(1, &nb, 1);
	return (count);
}

int	ft_print_unbr(unsigned int n)
{
	char	nb;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_print_unbr(n / 10);
	nb = (n % 10) + '0';
	count += write(1, &nb, 1);
	return (count);
}
