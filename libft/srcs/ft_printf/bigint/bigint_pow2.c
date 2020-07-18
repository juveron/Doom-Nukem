/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_pow2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 09:03:59 by kguibout          #+#    #+#             */
/*   Updated: 2019/06/18 13:05:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"
#include "ft_printf.h"

void	bigint_pow2(t_u32 pow, t_bigint *ret)
{
	t_bigint tmp;

	tmp.block[0] = 1;
	tmp.length = 1;
	bigint_bsl(&tmp, pow, ret);
}
