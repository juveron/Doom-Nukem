/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_star.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:13:19 by thboura           #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	ft_width_star(t_printf *pf)
{
	pf->format++;
	pf->width = va_arg(pf->arg, int);
	if (pf->width < 0)
	{
		if (pf->width == INT32_MIN)
			return ;
		pf->width *= -1;
		pf->flag |= 1 << LEFT_FLAG;
	}
	pf->has_width = true;
}

int		ft_precision_star(t_printf *pf)
{
	if (ft_isdigit(*(pf->format - 1)))
	{
		pf->ret = -1;
		return (0);
	}
	pf->format++;
	if ((pf->precision = va_arg(pf->arg, int)) < 0)
		pf->has_precision = false;
	return (1);
}
