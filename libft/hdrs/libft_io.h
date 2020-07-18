/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:05:19 by kguibout          #+#    #+#             */
/*   Updated: 2019/01/07 15:42:55 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include "libft.h"

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putendl(const char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
size_t	ft_putnwstr_fd(wchar_t *str, size_t n, int fd);
size_t	ft_putnwstr(wchar_t *str, size_t n);
void	ft_putnstr_fd(char *s, size_t n, int fd);
void	ft_putnstr(char *s, size_t n);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putstr(const char *s);
size_t	ft_putwchar_fd(wchar_t c, int fd);
size_t	ft_putwchar(wchar_t c);
size_t	ft_putwstr_fd(wchar_t *str, int fd);
size_t	ft_putwstr(wchar_t *str);

#endif
