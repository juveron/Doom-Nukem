/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:33:24 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/15 13:12:56 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	putnwstr(t_printf *pf, wchar_t *str, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((j += wcharlen(str[i])) > n)
			break ;
		putwchar(pf, str[i]);
		i++;
	}
}
