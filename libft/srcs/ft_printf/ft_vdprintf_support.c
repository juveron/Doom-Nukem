/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf_support.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 10:50:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	check_flag(t_printf *pf)
{
	if (pf->flag & 1 << SPACE_FLAG && pf->flag & 1 << SIGN_FLAG)
		pf->flag &= ~(1 << SPACE_FLAG);
	if (pf->flag & 1 << ZERO_FLAG && pf->flag & 1 << LEFT_FLAG)
		pf->flag &= ~(1 << ZERO_FLAG);
}

void	get_flag(t_printf *pf)
{
	while (*pf->format)
	{
		if (*pf->format == '#')
			pf->flag |= 1 << PREFIX_FLAG;
		else if (*pf->format == '0')
			pf->flag |= 1 << ZERO_FLAG;
		else if (*pf->format == '-')
			pf->flag |= 1 << LEFT_FLAG;
		else if (*pf->format == ' ')
			pf->flag |= 1 << SPACE_FLAG;
		else if (*pf->format == '+')
			pf->flag |= 1 << SIGN_FLAG;
		else
			break ;
		pf->format++;
	}
	check_flag(pf);
}

int		get_width(t_printf *pf)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(*pf->format))
	{
		pf->has_width = true;
		ret *= 10;
		ret += *pf->format - 48;
		pf->format++;
	}
	if (ret < 0)
		pf->has_width = false;
	else
		pf->width = ret;
	if (pf->width == 0 && (*pf->format == '*'))
		ft_width_star(pf);
	return (1);
}

int		get_precision(t_printf *pf)
{
	int	ret;

	if (*pf->format == '.')
	{
		pf->has_precision = true;
		pf->format++;
		ret = 0;
		while (ft_isdigit(*pf->format))
		{
			ret *= 10;
			ret += *pf->format - 48;
			pf->format++;
		}
		if (ret < 0)
			pf->has_precision = false;
		else
			pf->precision = ret;
		if (pf->precision == 0 && (*pf->format == '*'))
			if (!ft_precision_star(pf))
				return (0);
	}
	return (1);
}

void	get_size(t_printf *pf)
{
	if (ft_isalpha(*pf->format))
	{
		if (*pf->format == 'h')
		{
			pf->size = *(pf->format + 1) == 'h' ? HH : H;
			if (*(pf->format + 1) == 'h')
				pf->format++;
		}
		else if (*pf->format == 'l')
		{
			pf->size = *(pf->format + 1) == 'l' ? LL : L;
			if (*(pf->format + 1) == 'l')
				pf->format++;
		}
		else if (*pf->format == 'L')
			pf->size = LONG;
		else if (*pf->format == 'j')
			pf->size = J;
		else if (*pf->format == 'z')
			pf->size = Z;
		else
			return ;
		pf->format++;
	}
}
