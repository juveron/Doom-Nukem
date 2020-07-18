/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:05:19 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:11:34 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static void	add_zero(t_format_float *f, t_s32 *num_digits)
{
	t_s32	num_zero;
	int		i;

	num_zero = -f->string->out_exponent - 1;
	*num_digits = f->string->size_str;
	ft_memmove(f->string->str + num_zero + 2, f->string->str, *num_digits);
	i = 2;
	while (i < num_zero + 2)
		f->string->str[i++] = '0';
	*num_digits += num_zero;
	f->string->size_str = *num_digits;
	f->string->str[0] = '0';
	f->string->str[1] = '.';
	f->string->size_str += 2;
}

static void	add_dot_in_string(t_format_float *f, t_s32 *num_digits)
{
	t_s32	num_exp;

	num_exp = f->string->out_exponent + 1;
	if (f->string->size_str < num_exp)
	{
		while (f->string->size_str < num_exp)
			f->string->str[f->string->size_str++] = '0';
	}
	else if (f->string->size_str > num_exp)
	{
		*num_digits = f->string->size_str - num_exp;
		ft_memmove(f->string->str + num_exp + 1, f->string->str
			+ num_exp, *num_digits);
		f->string->str[num_exp] = '.';
		f->string->size_str = num_exp + 1 + *num_digits;
	}
}

void		add_point(t_format_float *f, int precision)
{
	t_s32	num_digits;
	t_s32	total_digit;

	num_digits = 0;
	if (f->string->out_exponent >= 0)
		add_dot_in_string(f, &num_digits);
	else
		add_zero(f, &num_digits);
	if (precision > num_digits)
	{
		if (!num_digits)
			f->string->str[f->string->size_str++] = '.';
		total_digit = f->string->size_str + (precision - num_digits);
		while (f->string->size_str < total_digit)
			f->string->str[f->string->size_str++] = '0';
	}
}
