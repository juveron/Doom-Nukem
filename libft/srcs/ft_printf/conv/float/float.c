/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:28:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:09:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"
#include "ft_printf.h"
#include "libft.h"
#include "float_p2.h"

static void	set_width(t_printf *pf, t_string_float *string)
{
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
	{
		if (pf->flag & 1 << ZERO_FLAG)
		{
			if (pf->flag & 1 << SIGN_FLAG && !string->sign)
				padded(pf, 1, '+');
			else if (!string->sign && (pf->flag & 1 << SPACE_FLAG))
				padded(pf, 1, ' ');
			else if (string->sign)
				padded(pf, 1, '-');
			padded(pf, pf->width - string->final_size_str
				- !!(pf->flag & 1 << SIGN_FLAG) - !!(pf->flag
					& 1 << PREFIX_FLAG) - !!(pf->flag & 1 << SPACE_FLAG), '0');
		}
		else if (pf->has_precision && pf->precision > string->final_size_str)
			padded(pf, pf->width - pf->precision - string->size_str
				- !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), ' ');
		else
			padded(pf, pf->width - string->final_size_str
				- !!(pf->flag & 1 << SIGN_FLAG)
				- !!(pf->flag & 1 << PREFIX_FLAG)
				- !!(pf->flag & 1 << SPACE_FLAG), ' ');
	}
}

static void	set_right_padded(t_printf *pf, t_string_float *string)
{
	if (pf->has_precision && pf->precision > string->size_fraction)
		padded(pf, pf->precision - string->size_fraction, '0');
	else if (pf->has_precision && pf->precision == 0
		&& (pf->flag & 1 << PREFIX_FLAG))
		padded(pf, 1, '.');
	if (!!(pf->flag & 1 << LEFT_FLAG) && pf->has_width && pf->has_precision
		&& pf->width > string->final_size_str)
		padded(pf, pf->width - string->final_size_str
			- !!(pf->flag & 1 << SIGN_FLAG)
			- !!(pf->flag & 1 << SPACE_FLAG), ' ');
	else if (pf->flag & 1 << LEFT_FLAG && pf->has_width
		&& pf->width > string->final_size_str)
		padded(pf, pf->width - string->final_size_str
			- !!(pf->flag & 1 << SIGN_FLAG)
			- !!(pf->flag & 1 << PREFIX_FLAG)
			- !!(pf->flag & 1 << SPACE_FLAG), ' ');
}

static void	set_prefix(t_printf *pf, int sign)
{
	if (!(pf->has_width && pf->flag & 1 << ZERO_FLAG))
	{
		if (pf->flag & 1 << SIGN_FLAG && !sign)
			padded(pf, 1, '+');
		else if (pf->flag & 1 << SPACE_FLAG && !sign)
			padded(pf, 1, ' ');
		else if (sign)
			padded(pf, 1, '-');
	}
}

void		convert_float(t_printf *pf, t_float_func *float_func)
{
	if (pf->size == LONG)
	{
		float_func->float128.ldvalue = va_arg(pf->arg, long double);
		float_func->mant = float_func->float128.struct128.mant;
		float_func->exp = float_func->float128.struct128.exp;
		float_func->sign = float_func->float128.struct128.sign;
		float_func->nb_bits = 128;
	}
	else
	{
		float_func->float64.dvalue = va_arg(pf->arg, double);
		float_func->mant = float_func->float64.struct64.mant;
		float_func->exp = float_func->float64.struct64.exp;
		float_func->sign = float_func->float64.struct64.sign;
		float_func->nb_bits = 64;
	}
}

void		func_float(t_printf *pf)
{
	t_string_float	string;
	t_float_func	float_func;

	convert_float(pf, &float_func);
	ft_bzero(&string, sizeof(string));
	if (!pf->has_precision)
	{
		pf->has_precision = true;
		pf->precision = 6;
	}
	execute_func(pf, &string, &float_func);
	string.final_size_str = string.size_exponent + !!(pf->precision)
		+ pf->precision;
	if (string.sign)
		enable_sign(pf);
	if (pf->precision != 0)
		pf->flag &= ~(1 << PREFIX_FLAG);
	set_width(pf, &string);
	set_prefix(pf, string.sign);
	putstr_buffer(pf, string.str, string.size_str);
	set_right_padded(pf, &string);
}
