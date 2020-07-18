/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:49:00 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/04 17:01:12 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

int		check_nan_inf(t_printf *pf, t_string_float *string,
	t_float_func *float_func)
{
	if ((float_func->exp == 0x7FF && float_func->nb_bits == 64)
		|| (float_func->exp == 0x7FFF && float_func->nb_bits == 128))
	{
		pf->flag &= ~(1 << PREFIX_FLAG);
		pf->flag &= ~(1 << ZERO_FLAG);
		string->sign = float_func->sign;
		string->size_exponent = 3;
		string->size_str = 3;
		pf->precision = 0;
		if (float_func->mant == 0)
			ft_strcpy(string->str, "inf");
		else
		{
			ft_strcpy(string->str, "nan");
			pf->flag &= ~(1 << SIGN_FLAG);
			pf->flag &= ~(1 << SPACE_FLAG);
		}
		return (1);
	}
	return (0);
}

void	enable_sign(t_printf *pf)
{
	pf->flag |= 1 << SIGN_FLAG;
	pf->flag &= ~(1 << SPACE_FLAG);
}

void	execute_func(t_printf *pf, t_string_float *string,
	t_float_func *float_func)
{
	if (check_nan_inf(pf, string, float_func))
		;
	else if (pf->size == LONG)
		func_double128(float_func->float128.ldvalue, maxi(0, mini(pf->precision,
					16400)), string);
	else
		func_double64(float_func->float64.dvalue, maxi(0, mini(pf->precision,
					16400)), string);
}
