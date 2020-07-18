/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:18:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 14:18:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

/*
**	TODO: This technic is not good ; need to upgrade this by returning something
**		for a stop if the buffer of sn is over.
*/

static void	sn_flush(t_printf *pf)
{
	if (pf->size_out + 1 == pf->size_max_sn)
	{
		pf->pos_buff = 0;
		pf->sn_no_space = true;
	}
	else
	{
		if (pf->size_out + pf->pos_buff >= pf->size_max_sn)
			pf->pos_buff -= pf->size_out + pf->pos_buff - pf->size_max_sn + 1;
		ft_strncpy(pf->out + pf->size_out, pf->buff, pf->pos_buff);
		pf->out[pf->size_out + pf->pos_buff] = '\0';
		pf->size_out += pf->pos_buff;
		pf->ret += pf->pos_buff;
		pf->pos_buff = 0;
	}
}

void		ft_flush(t_printf *pf)
{
	if (!pf->as && !pf->sn)
	{
		write(pf->fd, pf->buff, pf->pos_buff);
		pf->ret += pf->pos_buff;
		pf->pos_buff = 0;
	}
	else if (pf->as)
	{
		pf->out = ft_memrealloc(pf->out, pf->size_out, pf->size_out
				+ pf->pos_buff + 1);
		ft_strncpy(pf->out + pf->size_out, pf->buff, pf->pos_buff);
		pf->out[pf->size_out + pf->pos_buff] = '\0';
		pf->size_out += pf->pos_buff;
		pf->ret += pf->pos_buff;
		pf->pos_buff = 0;
	}
	else
		sn_flush(pf);
}
