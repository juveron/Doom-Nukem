/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:59:46 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static void	set_struct(t_printf *pf, char *ret, size_t buff_size,
	const char *format)
{
	pf->has_precision = 0;
	pf->has_width = 0;
	pf->out = ret;
	pf->flag = 0;
	pf->size = NONE;
	pf->size_out = 0;
	pf->pos_buff = 0;
	pf->format = (char *)format;
	pf->conv_func = static_fun();
	pf->fd = 0;
	pf->ret = 0;
	pf->as = false;
	pf->sn = true;
	pf->size_max_sn = buff_size;
	pf->sn_no_space = 0;
}

int			ft_snprintf(char *ret, size_t size, const char *format, ...)
{
	t_printf	pf;

	if (ret == NULL)
		return (-1);
	set_struct(&pf, ret, size, format);
	va_start(pf.arg, format);
	ft_vdprintf(&pf);
	va_end(pf.arg);
	return (pf.ret);
}
