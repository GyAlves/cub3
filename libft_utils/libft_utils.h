/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasminalves <gyasminalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:00:00 by gyasminalve       #+#    #+#             */
/*   Updated: 2025/11/29 00:00:00 by gyasminalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// String utility functions
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// File reading
char	*get_next_line(int fd);
void	gnl_cleanup(void);

// Conversion functions
int		ft_atoi(const char *str);

// Printf functions
int		ft_printf(const char *format, ...);
int		ft_function_type(const char *s, va_list ap);
int		ft_print_c(int letter);
int		ft_print_s(char *str);
int		ft_print_nbr(int n);
int		ft_print_unbr(unsigned int n);
int		ft_print_hex_lower(unsigned int nbr);
int		ft_print_hex_upper(unsigned int nbr);
int		ft_print_mem(unsigned long nbr);
int		ft_print_mem2(unsigned long nbr);

#endif
