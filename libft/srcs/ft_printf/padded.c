/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padded.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:14:21 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/11 22:56:11 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	padded(t_printf *pf, int length, char pad_char)
{
	int		i;

	i = 0;
	while (i < length)
	{
		put_buffer(pf, pad_char);
		i++;
	}
}
