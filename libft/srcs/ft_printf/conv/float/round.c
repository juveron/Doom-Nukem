/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:08:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"
#include "ft_printf.h"

static void	round_up(t_format_float *f)
{
	while (1)
	{
		if (f->current_digit == f->string->str)
		{
			*f->current_digit = '1';
			++f->current_digit;
			f->string->out_exponent++;
			f->string->size_exponent++;
			break ;
		}
		--f->current_digit;
		if (*f->current_digit != '9')
		{
			(*f->current_digit)++;
			f->current_digit++;
			break ;
		}
	}
}

void		round_float(t_format_float *f)
{
	t_s32	compare;
	bool	round_down;

	bigint_mul2(&f->scaled_value);
	compare = bigint_cmp(&f->scaled_value, &f->scale);
	round_down = compare < 0;
	if (compare == 0)
		round_down = (f->output_digit & 1) == 0;
	if (round_down)
	{
		*f->current_digit = '0' + f->output_digit;
		++f->current_digit;
	}
	else
	{
		if (f->output_digit == 9)
		{
			round_up(f);
		}
		else
		{
			*f->current_digit = '0' + f->output_digit + 1;
			f->current_digit++;
		}
	}
}
