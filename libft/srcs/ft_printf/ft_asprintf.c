/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 11:35:36 by thboura           #+#    #+#             */
/*   Updated: 2020/01/22 09:48:05 by kguibout         ###   ########.fr       */
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
	pf->size_out = 0;
	pf->pos_buff = 0;
	pf->format = (char *)format;
	pf->conv_func = static_fun();
	pf->fd = 0;
	pf->ret = 0;
	pf->as = true;
	pf->sn = false;
}

int			ft_asprintf(char **ret, const char *format, ...)
{
	t_printf	pf;

	if (ret == NULL)
		return (-1);
	set_struct(&pf, format);
	va_start(pf.arg, format);
	ft_vdprintf(&pf);
	va_end(pf.arg);
	*ret = (pf.out);
	return (pf.ret);
}
