/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:31:11 by thboura           #+#    #+#             */
/*   Updated: 2019/05/05 17:58:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void		func_char(t_printf *pf)
{
	unsigned char	c;

	if (pf->size == L)
	{
		func_wchar(pf);
		return ;
	}
	c = (unsigned char)va_arg(pf->arg, int);
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - 1, ' ');
	put_buffer(pf, c);
	if (pf->has_width && (pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - 1, ' ');
}
