/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:30:34 by thboura           #+#    #+#             */
/*   Updated: 2019/05/02 12:49:15 by kguibout         ###   ########.fr       */
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
			padded(pf, pf->width - length_nb
				- !!(pf->flag & 1 << PREFIX_FLAG), '0');
		else if (pf->has_precision && pf->precision == 0 && nb == 0)
			padded(pf, pf->width - !!(pf->flag & 1 << PREFIX_FLAG), ' ');
		else if (pf->has_precision && (size_t)pf->precision > length_nb
			+ !!(pf->flag & 1 << PREFIX_FLAG))
			padded(pf, pf->width - pf->precision, ' ');
		else
			padded(pf, pf->width - length_nb
				- !!(pf->flag & 1 << PREFIX_FLAG), ' ');
	}
}

static void			set_prefix(t_printf *pf)
{
	if (pf->flag & 1 << PREFIX_FLAG)
	{
		put_buffer(pf, '0');
	}
}

static void			set_number(t_printf *pf, size_t length_nb, uintmax_t nb)
{
	if (pf->has_precision && (size_t)pf->precision > length_nb
		+ !!(pf->flag & 1 << PREFIX_FLAG))
		padded(pf, pf->precision - length_nb - !!(pf->flag & 1 << PREFIX_FLAG),
			'0');
	if (pf->has_precision && pf->precision == 0 && nb == 0)
		;
	else
		putunbr_base(pf, nb, "01234567", 8);
	if (pf->flag & 1 << LEFT_FLAG && pf->has_precision && pf->precision == 0
		&& nb == 0)
		padded(pf, pf->width - !!(pf->flag & 1 << PREFIX_FLAG), ' ');
	else if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width && pf->has_precision
		&& (size_t)pf->precision > length_nb + !!(pf->flag & 1 << PREFIX_FLAG))
		padded(pf, pf->width - pf->precision, ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& (size_t)pf->width - !!(pf->flag & 1 << PREFIX_FLAG)
		> length_nb)
		padded(pf, pf->width - !!(pf->flag & 1 << PREFIX_FLAG)
			- length_nb, ' ');
}

void				func_octal(t_printf *pf)
{
	long	nb;
	size_t	length_nb;

	nb = set_size(pf);
	if (nb == 0 && (pf->flag & 1 << PREFIX_FLAG))
	{
		if ((pf->has_precision && pf->precision != 0) || !(pf->has_precision))
			pf->flag &= ~(1 << PREFIX_FLAG);
	}
	length_nb = length_unbr_base(nb, 8);
	set_width(pf, nb, length_nb);
	set_prefix(pf);
	set_number(pf, length_nb, nb);
}
