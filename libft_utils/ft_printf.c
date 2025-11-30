/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

int	ft_function_type(const char *s, va_list ap)
{
	int	type_count;

	type_count = 0;
	if (*s == '%')
		type_count += write(1, "%", 1);
	if (*s == 'c')
		type_count += ft_print_c(va_arg(ap, int));
	if (*s == 's')
		type_count += ft_print_s(va_arg(ap, char *));
	if (*s == 'p')
		type_count += ft_print_mem(va_arg(ap, unsigned long));
	if ((*s == 'd') || (*s == 'i'))
		type_count += ft_print_nbr(va_arg(ap, int));
	if ((*s == 'u'))
		type_count += ft_print_unbr(va_arg(ap, unsigned int));
	if (*s == 'x')
		type_count += ft_print_hex_lower(va_arg(ap, unsigned int));
	if (*s == 'X')
		type_count += ft_print_hex_upper(va_arg(ap, unsigned int));
	return (type_count);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(ap, s);
	while (s[i] != '\0')
	{
		if (s[i] != '%')
		{
			count += write(1, &s[i], 1);
			i++;
		}
		else if (s[i] == '%')
		{
			i++;
			if (ft_strchr("%cspdiuxX", s[i]))
				count += ft_function_type(&s[i], ap);
			i++;
		}
	}
	va_end(ap);
	return (count);
}
