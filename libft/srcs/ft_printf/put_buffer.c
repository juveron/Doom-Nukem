/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:15:28 by kguibout          #+#    #+#             */
/*   Updated: 2019/04/22 19:10:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void			put_buffer(t_printf *pf, char c)
{
	pf->buff[pf->pos_buff] = c;
	pf->pos_buff++;
	if (pf->pos_buff == PRINTF_BUFFER_SIZE)
		ft_flush(pf);
}
