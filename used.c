/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   used.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:55:54 by jucoelho          #+#    #+#             */
/*   Updated: 2025/11/29 20:04:55 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
int	ft_print_mem(unsigned long nbr)
{
	int		count;

	count = 0;
	if (nbr == 0)
		return (ft_print_s("(nil)"));
	write(1, "0x", 2);
	count += 2;
	count += ft_print_mem2(nbr);
	return (count);
}

int	ft_print_hex_lower(unsigned int nbr)
{
	char	*hex_chars_lower;
	int		count;

	count = 0;
	hex_chars_lower = "0123456789abcdef";
	if (nbr >= 16)
		count += ft_print_hex_lower(nbr / 16);
	count += write(1, &hex_chars_lower[nbr % 16], 1);
	return (count);
}

int	ft_print_hex_upper(unsigned int nbr)
{
	char	*hex_chars;
	int		count;

	count = 0;
	hex_chars = "0123456789ABCDEF";
	if (nbr >= 16)
		count += ft_print_hex_upper(nbr / 16);
	count += write(1, &hex_chars[nbr % 16], 1);
	return (count);
}