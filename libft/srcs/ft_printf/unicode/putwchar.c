/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 09:28:43 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/14 10:00:18 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	putwchar(t_printf *pf, wchar_t c)
{
	if (c <= 0x7F)
		put_buffer(pf, c);
	else if (c <= 0x7FF)
	{
		put_buffer(pf, (c >> 6) + 0xC0);
		put_buffer(pf, (c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		put_buffer(pf, (c >> 12) + 0xE0);
		put_buffer(pf, ((c >> 6) & 0x3F) + 0x80);
		put_buffer(pf, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		put_buffer(pf, (c >> 18) + 0xF0);
		put_buffer(pf, ((c >> 12) & 0x3F) + 0x80);
		put_buffer(pf, ((c >> 6) & 0x3F) + 0x80);
		put_buffer(pf, (c & 0x3F) + 0x80);
	}
}
