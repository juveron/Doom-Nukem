/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:36:13 by thboura           #+#    #+#             */
/*   Updated: 2020/01/22 09:47:39 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static	int	ft_hextorgb(char *format, size_t pos)
{
	int		nb;
	size_t	i;

	nb = 0;
	i = 0 + pos;
	while (i < 2 + pos)
	{
		if (format[i] >= 'A' && format[i] <= 'F')
			nb = nb * 16 + (format[i] - 'A' + 10);
		else if (format[i] >= 'a' && format[i] <= 'f')
			nb = nb * 16 + (format[i] - 'a' + 10);
		else if (format[i] >= '0' && format[i] <= '9')
			nb = nb * 16 + (format[i] - '0');
		else
			return (0);
		i++;
	}
	return (nb);
}

static bool	color_hex_to_rgb(t_printf *pf, char *format, size_t max)
{
	int		red;
	int		green;
	int		blue;

	if (format[0] == '0' && format[1] == '}')
	{
		putstr_buffer(pf, "\033[0m", 4);
		return (1);
	}
	else if (max != 6)
		return (0);
	putstr_buffer(pf, "\033[38;2;", 7);
	putnbr_buffer(pf, (red = ft_hextorgb(format, 0)));
	put_buffer(pf, ';');
	putnbr_buffer(pf, (green = ft_hextorgb(format, 2)));
	put_buffer(pf, ';');
	putnbr_buffer(pf, (blue = ft_hextorgb(format, 4)));
	put_buffer(pf, 'm');
	return (1);
}

static bool	apply_color(t_printf *pf, char *format, size_t max)
{
	if (!(ft_strncmp(format, "end", max)))
		putstr_buffer(pf, "\033[0m", 4);
	else if (!(ft_strncmp(format, "red", max)))
		putstr_buffer(pf, "\033[38;2;255;0;0m", 15);
	else if (!(ft_strncmp(format, "green", max)))
		putstr_buffer(pf, "\033[38;2;0;255;0m", 15);
	else if (!(ft_strncmp(format, "blue", max)))
		putstr_buffer(pf, "\033[38;2;0;0;255m", 15);
	else if (!(ft_strncmp(format, "magenta", max)))
		putstr_buffer(pf, "\033[38;2;255;0;255m", 17);
	else if (!(ft_strncmp(format, "yellow", max)))
		putstr_buffer(pf, "\033[38;2;255;255;0m", 17);
	else if (!(ft_strncmp(format, "aqua", max))
		|| !(ft_strncmp(format, "cyan", max)))
		putstr_buffer(pf, "\033[38;2;0;255;255m", 17);
	else if (!(ft_strncmp(format, "white", max)))
		putstr_buffer(pf, "\033[38;2;255;255;255m", 19);
	else if (!(ft_strncmp(format, "dark", max)))
		putstr_buffer(pf, "\033[38;2;0;0;0m", 13);
	else if (!(ft_strncmp(format, "gray", max))
		|| !(ft_strncmp(format, "grey", max)))
		putstr_buffer(pf, "\033[38;2;128;128;128m", 19);
	else
		return (0);
	return (1);
}

static int	valid_bracket(t_printf *pf, char *format, size_t max)
{
	if (format[0] == '0' && (format[1] == 'X' || format[1] == 'x'))
		return (color_hex_to_rgb(pf, format + 2, max - 2));
	else if (format[0] == '#')
		return (color_hex_to_rgb(pf, format + 1, max - 1));
	return (apply_color(pf, format, max));
}

size_t		ft_color(t_printf *pf, char *str, size_t pos)
{
	size_t	i;

	i = 0 + pos;
	while (str[i + 1] && str[i + 1] != '}')
	{
		if (i - pos > 8)
			break ;
		i++;
	}
	if (str[i + 1] != '}' || (i - pos < 2 || i - pos > 8))
		return (0);
	if (valid_bracket(pf, str + pos + 1, i - pos))
		return (i - pos + 2);
	return (0);
}
