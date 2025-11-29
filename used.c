/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   used.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:40:09 by jucoelho          #+#    #+#             */
/*   Updated: 2025/11/29 19:54:29 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:03:34 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/13 23:51:20 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}	
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:32:39 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/13 23:51:25 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;
	size_t	len_s1;
	size_t	len_trim;
	size_t	first;
	size_t	last;

	first = 0;
	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	last = len_s1 - 1;
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (s1[last] && ft_strchr(set, s1[last]) && last > first)
		last--;
	len_trim = last - first + 1;
	s1_trim = (char *)malloc(sizeof(char) * (len_trim + 1));
	if (!s1_trim)
		return (NULL);
	ft_strlcpy(s1_trim, &s1[first], len_trim + 1);
	return (s1_trim);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:56:34 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/24 22:08:28 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*allocate_word(const char *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static int	free_split(char **split, int i)
{
	while (i > 0)
		free(split[--i]);
	free(split);
	return (0);
}

static int	fill_split(char **split, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			split[i] = allocate_word(s, c);
			if (!split[i])
				return (free_split(split, i));
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	if (!fill_split(split, s, c))
		return (NULL);
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:02:44 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/24 22:12:35 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			j = j * -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		k = k * 10 + (nptr[i] - '0');
		i++;
	}
	return (k * j);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:19:31 by jucoelho          #+#    #+#             */
/*   Updated: 2024/11/14 00:01:50 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (!s || start >= len_s || len == 0)
	{
		substr = (char *)malloc ((sizeof(char)) * 1);
		substr[0] = '\0';
		return (substr);
	}
	if (len > len_s - start)
		len = len_s - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
