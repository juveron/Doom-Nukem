/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 12:38:07 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 14:33:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"
#include "ft_printf.h"

void	normalize_scale(t_format_float *f)
{
	t_u64	hi_block;
	t_u32	hi_block_log2;
	t_u32	shift;

	hi_block = f->scale.block[f->scale.length - 1];
	if (hi_block < 8 || hi_block > 1844674407370955161)
	{
		hi_block_log2 = ft_log2(hi_block);
		shift = (64 + 59 - hi_block_log2) % 64;
		bigint_bsl(&f->scale, shift, &f->scale);
		bigint_bsl(&f->scaled_value, shift, &f->scaled_value);
	}
}

void	compute_float(t_format_float *f)
{
	f->tmp2 = f->digit_exponent;
	while (1)
	{
		--f->tmp2;
		f->output_digit = bigint_div(&f->scaled_value, &f->scale);
		if ((f->scaled_value.length == 1 && f->scaled_value.block[0] == 0)
			|| (f->tmp2 == f->cutoff_exponent))
			break ;
		*f->current_digit = (char)('0' + f->output_digit);
		++f->current_digit;
		bigint_mul10(&f->scaled_value);
	}
	f->last_digit = f->current_digit - 1;
}

void	add_digit_exp(t_format_float *f)
{
	t_bigint		tmp;
	t_bigint		tmp2;

	if (f->digit_exponent > 0)
	{
		bigint_pow10(f->digit_exponent, &tmp);
		bigint_mul(&f->scale, &tmp, &tmp2);
		f->scale = tmp2;
	}
	else if (f->digit_exponent < 0)
	{
		bigint_pow10(-f->digit_exponent, &tmp);
		bigint_mul(&f->scaled_value, &tmp, &tmp2);
		f->scaled_value = tmp2;
	}
	if (bigint_cmp(&f->scaled_value, &f->scale) >= 0)
		++f->digit_exponent;
	else
		bigint_mul10(&f->scaled_value);
	f->string->size_exponent = f->digit_exponent > 0 ? f->digit_exponent
		: 1;
}
