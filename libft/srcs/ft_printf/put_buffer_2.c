/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_buffer_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:10:17 by thboura           #+#    #+#             */
/*   Updated: 2019/04/22 19:21:59 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

static char		hex(unsigned char u)
{
	if (u < 10)
		return ('0' + u);
	return ('a' + (u - 10));
}

static void		print_hex(t_printf *pf, char c)
{
	unsigned char x;

	x = (unsigned)c;
	pf->buff[pf->pos_buff++] = '\\';
	pf->buff[pf->pos_buff++] = hex(x / 16);
	pf->buff[pf->pos_buff++] = hex(x % 16);
}

static void		check_whitespace(t_printf *pf, char c)
{
	if (c == '\a')
		putstr_buffer(pf, "\\a", 2);
	else if (c == '\b')
		putstr_buffer(pf, "\\b", 2);
	else if (c == '\t')
		putstr_buffer(pf, "\\t", 2);
	else if (c == '\n')
		putstr_buffer(pf, "\\n", 2);
	else if (c == '\v')
		putstr_buffer(pf, "\\v", 2);
	else if (c == '\f')
		putstr_buffer(pf, "\\f", 2);
	else if (c == '\r')
		putstr_buffer(pf, "\\r", 2);
	else if (c == '\e')
		putstr_buffer(pf, "\\e", 2);
	else
		print_hex(pf, c);
}

void			put_buffer_2(t_printf *pf, char c)
{
	if (!(ft_isprint(c)))
		check_whitespace(pf, c);
	else
	{
		pf->buff[pf->pos_buff] = c;
		pf->pos_buff++;
	}
	if (pf->pos_buff == PRINTF_BUFFER_SIZE)
		ft_flush(pf);
}
