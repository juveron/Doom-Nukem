/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:06:10 by thboura           #+#    #+#             */
/*   Updated: 2019/08/02 14:05:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static void	set_width(t_printf *pf, size_t length_str)
{
	char	pad;

	pad = pf->flag & 1 << ZERO_FLAG ? '0' : ' ';
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
	{
		if (pf->has_precision && (size_t)pf->precision < length_str)
			padded(pf, pf->width - pf->precision, pad);
		else
			padded(pf, pf->width - length_str, pad);
	}
}

static void	set_str(t_printf *pf, size_t length_str, char *str)
{
	size_t	i;

	i = 0;
	if (pf->has_precision && (size_t)pf->precision < length_str)
		while (i < (size_t)pf->precision)
			put_buffer(pf, str[i++]);
	else
		while (i < length_str)
			put_buffer(pf, str[i++]);
	if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width
		&& pf->has_precision && (size_t)pf->precision < length_str)
		padded(pf, pf->width - pf->precision, ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& (size_t)pf->width > length_str)
		padded(pf, pf->width - length_str, ' ');
}

void		func_string(t_printf *pf)
{
	char	*str;
	size_t	length_str;

	if (pf->size == L)
	{
		func_wstr(pf);
		return ;
	}
	str = va_arg(pf->arg, char *);
	if (str == NULL)
		str = "(null)";
	length_str = (pf->has_precision && pf->precision == 0) ? 0 : ft_strlen(str);
	set_width(pf, length_str);
	set_str(pf, length_str, str);
}
