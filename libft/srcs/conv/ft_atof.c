/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 22:28:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static void	set_mantissa(t_atof *s)
{
	while (1)
	{
		s->c = *s->p;
		if (!ft_isdigit(s->c))
		{
			if ((s->c != '.') || (s->decimal_point >= 0))
				break ;
			s->decimal_point = s->mantissa_size;
		}
		++s->mantissa_size;
		++s->p;
	}
	s->p_exp = s->p;
	s->p -= s->mantissa_size;
	if (s->decimal_point < 0)
		s->decimal_point = s->mantissa_size;
	else
		--s->mantissa_size;
	if (s->mantissa_size > 18)
	{
		s->frac_exp = s->decimal_point - 18;
		s->mantissa_size = 18;
	}
	else
		s->frac_exp = s->decimal_point - s->mantissa_size;
}

static void	init_atof(const char *str, t_atof *s)
{
	s->exp = 0;
	s->exp_sign = 0;
	s->p = (char *)str;
	while (*s->p == ' ')
		++s->p;
	if (*s->p == '-')
	{
		s->sign = true;
		++s->p;
	}
	else
	{
		if (*s->p == '+')
			++s->p;
		s->sign = false;
	}
	s->decimal_point = -1;
	s->mantissa_size = 0;
	set_mantissa(s);
	s->frac1 = 0;
	s->frac2 = 0;
	s->flt_exp = 1.0;
	s->mul = 1;
}

static void	compute_mantissa(t_atof *s)
{
	while (s->mantissa_size > 9)
	{
		s->c = *s->p;
		++s->p;
		if (s->c == '.')
		{
			s->c = *s->p;
			++s->p;
		}
		s->frac1 = 10 * s->frac1 + (s->c - '0');
		--s->mantissa_size;
	}
	while (s->mantissa_size > 0)
	{
		s->c = *s->p;
		++s->p;
		if (s->c == '.')
		{
			s->c = *s->p;
			++s->p;
		}
		s->frac2 = 10 * s->frac2 + (s->c - '0');
		--s->mantissa_size;
	}
}

static void	compute_exp(t_atof *s)
{
	while (s->frac_exp != 0)
	{
		if (s->frac_exp & 01)
			s->flt_exp *= pow(10.0, s->mul);
		s->frac_exp >>= 1;
		s->mul *= 2.0;
	}
}

float		ft_atof(const char *str)
{
	t_atof	s;

	init_atof(str, &s);
	if (s.mantissa_size == 0)
		return (0.0);
	compute_mantissa(&s);
	s.fraction = (1.0e9 * s.frac1) + s.frac2;
	if (s.frac_exp < 0)
	{
		s.exp_sign = true;
		s.frac_exp = -s.frac_exp;
	}
	else
		s.exp_sign = false;
	if (s.frac_exp > 511)
		s.frac_exp = 511;
	compute_exp(&s);
	if (s.exp_sign)
		s.fraction /= s.flt_exp;
	else
		s.fraction *= s.flt_exp;
	if (s.sign)
		return (-s.fraction);
	else
		return (s.fraction);
}
