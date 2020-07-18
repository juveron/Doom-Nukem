/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:31:15 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/15 13:12:22 by kguibout         ###   ########.fr       */
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

static void	set_str(t_printf *pf, size_t length_str, wchar_t *str)
{
	if (pf->has_precision && (size_t)pf->precision < length_str)
		putnwstr(pf, str, (size_t)pf->precision);
	else
		putnwstr(pf, str, length_str);
	if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width
		&& pf->has_precision && (size_t)pf->precision < length_str)
		padded(pf, pf->width - pf->precision, ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& (size_t)pf->width > length_str)
		padded(pf, pf->width - length_str, ' ');
}

void		func_wstr(t_printf *pf)
{
	wchar_t	*str;
	size_t	length_str;

	str = va_arg(pf->arg, wchar_t *);
	if (str == NULL)
		str = L"(null)";
	length_str = wstrlen(str);
	set_width(pf, length_str);
	set_str(pf, length_str, str);
}
