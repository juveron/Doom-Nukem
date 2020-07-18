/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:55:15 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/20 00:36:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static uintmax_t	set_size(t_printf *pf)
{
	uintmax_t	nb;

	if (pf->size == HH)
		nb = (unsigned char)va_arg(pf->arg, unsigned int);
	else if (pf->size == H)
		nb = (unsigned short)va_arg(pf->arg, unsigned int);
	else if (pf->size == LL)
		nb = va_arg(pf->arg, unsigned long long);
	else if (pf->size == L)
		nb = va_arg(pf->arg, unsigned long);
	else if (pf->size == J)
		nb = va_arg(pf->arg, size_t);
	else if (pf->size == Z)
		nb = va_arg(pf->arg, uintmax_t);
	else
		nb = (unsigned int)va_arg(pf->arg, unsigned int);
	return (nb);
}

static void			set_width(t_printf *pf, uintmax_t nb, size_t length_nb)
{
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
	{
		if (pf->flag & 1 << ZERO_FLAG && !(pf->has_precision))
			padded(pf, pf->width - length_nb, '0');
		else if (pf->has_precision && pf->precision == 0 && nb == 0)
			padded(pf, pf->width, ' ');
		else if (pf->has_precision && (size_t)pf->precision > length_nb)
			padded(pf, pf->width - pf->precision, ' ');
		else
			padded(pf, pf->width - length_nb, ' ');
	}
}

static void			set_number(t_printf *pf, size_t length_nb, uintmax_t nb)
{
	if (pf->has_precision && (size_t)pf->precision > length_nb)
		padded(pf, pf->precision - length_nb, '0');
	if (pf->has_precision && pf->precision == 0 && nb == 0)
		;
	else
		putunbr_base(pf, nb, "01", 2);
	if (pf->flag & 1 << LEFT_FLAG && pf->has_width && pf->has_precision
		&& pf->precision == 0 && nb == 0)
		padded(pf, pf->width, ' ');
	else if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width && pf->has_precision
		&& (size_t)pf->precision > length_nb)
		padded(pf, pf->width - pf->precision, ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& (size_t)pf->width > length_nb)
		padded(pf, pf->width - length_nb, ' ');
}

void				func_binary(t_printf *pf)
{
	long	nb;
	size_t	length_nb;

	nb = set_size(pf);
	length_nb = length_unbr_base(nb, 2);
	set_width(pf, nb, length_nb);
	set_number(pf, length_nb, nb);
}
