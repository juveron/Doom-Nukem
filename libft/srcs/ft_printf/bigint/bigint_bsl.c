/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_bsl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:53:40 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 13:07:36 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static void	multi_bit(t_bigint *bigint, size_t bits, int offset,
	t_bigint *ret)
{
	t_bigint	tmp;
	t_u64		hb;
	t_u64		lb;
	int			i;

	i = 0;
	hb = 0;
	lb = bigint->block[bigint->length - 1] >> (64 - bits);
	tmp.length = bigint->length + offset + 1;
	while (bigint->length - 1 - i > 0)
	{
		tmp.block[bigint->length + offset - i] = hb | lb;
		hb = bigint->block[bigint->length - 1 - i] << bits;
		i++;
		lb = bigint->block[bigint->length - 1 - i] >> (64 - bits);
	}
	tmp.block[bigint->length + offset - i] = hb | lb;
	tmp.block[bigint->length + offset - i - 1] = bigint->block[bigint->length
			- 1 - i] << bits;
	i = 0;
	while (i < offset)
		tmp.block[i++] = 0;
	if (tmp.block[tmp.length - 1] == 0)
		--tmp.length;
	*ret = tmp;
}

static void	zero_bit(t_bigint *bigint, t_bigint *ret, int offset)
{
	int			i;
	t_bigint	tmp;

	i = bigint->length - 1;
	tmp.length = bigint->length;
	while (i >= 0)
	{
		tmp.block[i + offset] = bigint->block[i];
		i--;
	}
	i = 0;
	while (i < offset)
		tmp.block[i++] = 0;
	*ret = tmp;
	ret->length += offset;
}

void		bigint_bsl(t_bigint *bigint, int bits, t_bigint *ret)
{
	int	offset;

	offset = bits / 64;
	bits %= 64;
	if (bits == 0)
		zero_bit(bigint, ret, offset);
	else
		multi_bit(bigint, bits, offset, ret);
}
