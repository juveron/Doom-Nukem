/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 09:24:02 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 10:41:08 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"
#include "ft_printf.h"
#include "bigint.h"

static t_format_float	convert_float(double dvalue, t_string_float *string)
{
	t_float64		value;
	t_format_float	f;

	value.dvalue = dvalue;
	f.string = string;
	string->sign = value.struct64.sign;
	if (value.struct64.exp != 0)
	{
		f.mant = (1ul << 52) | value.struct64.mant;
		f.exp = value.struct64.exp - 1023 - 52;
		f.mant_index = 52;
	}
	else
	{
		f.mant = value.struct64.mant;
		f.exp = 1 - 1023 - 52;
		f.mant_index = ft_log2(value.struct64.mant);
	}
	return (f);
}

static void				add_exp(t_format_float *f)
{
	if (f->exp > 0)
	{
		bigint_new(&f->scaled_value, 1, 2 * f->mant);
		bigint_bsl(&f->scaled_value, f->exp, &f->scaled_value);
		bigint_new(&f->scale, 1, 2);
	}
	else
	{
		bigint_new(&f->scaled_value, 1, 2 * f->mant);
		bigint_pow2(-f->exp + 1, &f->scale);
	}
}

static void				mant_zero(t_format_float *f, t_string_float *string,
	int precision)
{
	*f->current_digit = '0';
	string->size_exponent = 1;
	string->size_fraction = 0;
	if (precision)
		*(f->current_digit + 1) = '.';
	string->size_str = ft_strlen(string->str);
}

void					func_double64(double dvalue,
	int precision, t_string_float *string)
{
	t_format_float	f;

	f = convert_float(dvalue, string);
	f.current_digit = f.string->str;
	if (!f.mant)
	{
		mant_zero(&f, string, precision);
		return ;
	}
	add_exp(&f);
	f.digit_exponent = ((t_s64)f.mant_index + f.exp) * LOG10_2 + LOG10_2;
	if (f.digit_exponent <= -precision)
		f.digit_exponent = -precision + 1;
	add_digit_exp(&f);
	f.cutoff_exponent = f.digit_exponent - 22000;
	if (-precision > f.cutoff_exponent)
		f.cutoff_exponent = -precision;
	f.string->size_fraction = precision;
	f.string->out_exponent = f.digit_exponent - 1;
	normalize_scale(&f);
	compute_float(&f);
	round_float(&f);
	string->size_str = f.current_digit - f.string->str;
	add_point(&f, precision);
}
