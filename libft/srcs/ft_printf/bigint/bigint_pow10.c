/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_pow10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 09:52:29 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/01 20:41:43 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"
#include "ft_printf.h"

void	bigint_pow10(t_u32 pow, t_bigint *ret)
{
	t_u32		i;

	i = 0;
	bigint_new(ret, 1, 1);
	while (i < pow)
	{
		bigint_mul10(ret);
		i++;
	}
}
