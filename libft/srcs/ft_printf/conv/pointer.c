/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:29:11 by thboura           #+#    #+#             */
/*   Updated: 2019/05/10 10:19:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void		func_pointer(t_printf *pf)
{
	void	*p;
	size_t	length_p;
	size_t	length_full;

	p = va_arg(pf->arg, void *);
	length_p = (p == NULL && pf->has_precision && !(pf->precision)) ? 0
		: length_unbr_base((uintmax_t)p, 16);
	length_full = length_p + 2;
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - length_full, ' ');
	put_buffer(pf, '0');
	put_buffer(pf, 'x');
	if (p == NULL && pf->has_precision && !(pf->precision))
		;
	else
		putunbr_base(pf, (uintmax_t)p, "0123456789abcdef", 16);
	if (pf->has_width && (pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - length_full, ' ');
}
