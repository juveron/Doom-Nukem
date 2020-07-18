/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:41:49 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 13:08:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	putstr_buffer_2(t_printf *pf, char *str, size_t n)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	while (str[i] && i < n)
	{
		if (str[i] == '{' && (tmp = ft_color(pf, str, i)))
			i += tmp;
		else
		{
			put_buffer(pf, str[i]);
			i++;
		}
	}
}

void	putstr_buffer(t_printf *pf, char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n)
	{
		put_buffer(pf, str[i]);
		i++;
	}
}
