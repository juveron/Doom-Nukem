/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:40:19 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:33:39 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static long	set_size(t_printf *pf)
{
	intmax_t	nb;

	if (pf->size == HH)
		nb = (char)va_arg(pf->arg, int);
	else if (pf->size == H)
		nb = (short)va_arg(pf->arg, int);
	else if (pf->size == LL)
		nb = va_arg(pf->arg, long long);
	else if (pf->size == L)
		nb = va_arg(pf->arg, long);
	else if (pf->size == J)
		nb = va_arg(pf->arg, intmax_t);
	else if (pf->size == Z)
		nb = va_arg(pf->arg, ssize_t);
	else
		nb = (int)va_arg(pf->arg, int);
	return (nb);
}

static void	set_width(t_printf *pf, intmax_t nb, size_t length_nb)
{
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
	{
		if (pf->flag & 1 << ZERO_FLAG && !(pf->has_precision))
		{
			if (pf->flag & 1 << SIGN_FLAG && nb >= 0)
				padded(pf, 1, '+');
			else if (nb >= 0 && (pf->flag & 1 << SPACE_FLAG))
				padded(pf, 1, ' ');
			else if (nb < 0)
				padded(pf, 1, '-');
			padded(pf, pf->width - length_nb - !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), '0');
		}
		else if (pf->has_precision && pf->precision == 0 && nb == 0)
			padded(pf, pf->width - !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), ' ');
		else if (pf->has_precision && (size_t)pf->precision > length_nb)
			padded(pf, pf->width - pf->precision - !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), ' ');
		else
			padded(pf, pf->width - length_nb - !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), ' ');
	}
}

static void	set_prefix(t_printf *pf, intmax_t nb)
{
	if (!(pf->has_width && pf->flag & 1 << ZERO_FLAG) || pf->has_precision)
	{
		if (pf->flag & 1 << SIGN_FLAG && nb >= 0)
			padded(pf, 1, '+');
		else if (pf->flag & 1 << SPACE_FLAG && nb >= 0)
			padded(pf, 1, ' ');
		else if (nb < 0)
			padded(pf, 1, '-');
	}
}

static void	set_number(t_printf *pf, size_t length_nb, intmax_t nb)
{
	if (pf->has_precision && (size_t)pf->precision > length_nb)
		padded(pf, pf->precision - length_nb, '0');
	if (pf->has_precision && pf->precision == 0 && nb == 0)
		;
	else if (nb >= 0)
		putunbr_base(pf, nb, "0123456789", 10);
	else
		putunbr_base(pf, -nb, "0123456789", 10);
	if (pf->flag & 1 << LEFT_FLAG && pf->has_width && pf->has_precision
		&& pf->precision == 0 && nb == 0)
		padded(pf, pf->width - !!(pf->flag & 1 << SIGN_FLAG)
			- !!(pf->flag & 1 << SPACE_FLAG), ' ');
	else if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width && pf->has_precision
		&& (size_t)pf->precision > length_nb)
		padded(pf, pf->width - pf->precision - !!(pf->flag & 1 << SIGN_FLAG)
			- !!(pf->flag & 1 << SPACE_FLAG), ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& (size_t)pf->width > length_nb)
		padded(pf, pf->width - length_nb - !!(pf->flag & 1 << SIGN_FLAG)
			- !!(pf->flag & 1 << SPACE_FLAG), ' ');
}

void		func_integer(t_printf *pf)
{
	long	nb;
	size_t	length_nb;

	nb = set_size(pf);
	if (nb < 0)
	{
		pf->flag |= 1 << SIGN_FLAG;
		pf->flag &= ~(1 << SPACE_FLAG);
	}
	length_nb = nb < 0 ? length_unbr_base(-nb, 10) : length_unbr_base(nb, 10);
	set_width(pf, nb, length_nb);
	set_prefix(pf, nb);
	set_number(pf, length_nb, nb);
}
