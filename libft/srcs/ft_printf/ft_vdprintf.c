/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 08:48:27 by thboura           #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static void	reset_format(t_printf *pf)
{
	pf->flag = 0;
	pf->has_precision = false;
	pf->has_width = false;
	pf->size = NONE;
}

static void	get_format(t_printf *pf)
{
	int		size;

	pf->next = ft_strchrnull(pf->format, '%');
	size = pf->next - pf->format;
	putstr_buffer_2(pf, pf->format, size);
	pf->format += size;
	if (*pf->format == '%')
		pf->format++;
}

void		ft_vdprintf(t_printf *pf)
{
	get_format(pf);
	while (*pf->next != '\0')
	{
		get_flag(pf);
		get_width(pf);
		if (!get_precision(pf))
			return ;
		get_size(pf);
		if (ft_isascii(*pf->format))
		{
			if (pf->conv_func[(int)*pf->format])
				pf->conv_func[(int)*pf->format](pf);
			else
			{
				pf->ret = -1;
				return ;
			}
			pf->format++;
		}
		if (pf->sn && pf->sn_no_space)
			break ;
		reset_format(pf);
		get_format(pf);
	}
	ft_flush(pf);
}
