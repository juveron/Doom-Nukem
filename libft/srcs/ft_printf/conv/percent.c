/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:38:57 by thboura           #+#    #+#             */
/*   Updated: 2019/03/14 10:13:22 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void		func_percent(t_printf *pf)
{
	char	c;

	c = '%';
	if (pf->has_width && !(pf->flag & 1 << LEFT_FLAG))
	{
		if (pf->flag & 1 << ZERO_FLAG)
		{
			padded(pf, pf->width - 1, '0');
		}
		else
			padded(pf, pf->width - 1, ' ');
	}
	put_buffer(pf, c);
	if (pf->has_width && (pf->flag & 1 << LEFT_FLAG))
		padded(pf, pf->width - 1, ' ');
}
