/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:47:49 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/14 14:08:11 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	func_wchar(t_printf *pf)
{
	wchar_t	c;
	size_t	length_c;

	c = va_arg(pf->arg, wchar_t);
	length_c = wcharlen(c);
	if (!(pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - length_c, ' ');
	putwchar(pf, c);
	if (pf->flag & 1 << LEFT_FLAG)
		padded(pf, pf->width - length_c, ' ');
}
