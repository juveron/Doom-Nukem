/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 09:22:50 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static void	set_struct(t_printf *pf, const char *format)
{
	pf->has_precision = 0;
	pf->has_width = 0;
	pf->out = NULL;
	pf->flag = 0;
	pf->size = NONE;
	pf->pos_buff = 0;
	pf->format = (char *)format;
	pf->conv_func = static_fun();
	pf->fd = 1;
	pf->ret = 0;
	pf->as = false;
	pf->sn = false;
}

int			ft_printf(const char *format, ...)
{
	t_printf	pf;

	set_struct(&pf, format);
	va_start(pf.arg, format);
	ft_vdprintf(&pf);
	va_end(pf.arg);
	return (pf.ret);
}
