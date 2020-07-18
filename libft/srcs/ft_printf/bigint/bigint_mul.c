/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 14:09:45 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 10:41:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

static void	set_bigint(t_mul *mul_struct, t_bigint *a, t_bigint *b,
	t_bigint *ret)
{
	if (a->length < b->length)
	{
		mul_struct->small = a;
		mul_struct->large = b;
	}
	else
	{
		mul_struct->small = b;
		mul_struct->large = a;
	}
	mul_struct->size_max = mul_struct->small->length
		+ mul_struct->large->length;
	ft_bzero(ret->block, mul_struct->size_max * sizeof(*ret->block));
}

static void	compute_mul(t_mul *mul_struct, t_bigint *ret)
{
	if (mul_struct->mul != 0)
	{
		mul_struct->j = 0;
		mul_struct->carry = 0;
		while (mul_struct->j < mul_struct->large->length)
		{
			mul_struct->sum = (t_u128)ret->block[mul_struct->j]
				+ (t_u128)mul_struct->large->block[mul_struct->j]
				* (t_u128)mul_struct->mul + mul_struct->carry;
			mul_struct->carry = mul_struct->sum >> 64;
			ret->block[mul_struct->j] = mul_struct->sum & 0xFFFFFFFFFFFFFFFF;
			mul_struct->j++;
		}
		ret->block[mul_struct->j] = (t_u64)(mul_struct->carry
				& 0xFFFFFFFFFFFFFFFF);
	}
}

void		bigint_mul(t_bigint *a, t_bigint *b, t_bigint *ret)
{
	t_mul	mul_struct;

	set_bigint(&mul_struct, a, b, ret);
	mul_struct.i = 0;
	while (mul_struct.i < mul_struct.small->length)
	{
		mul_struct.mul = mul_struct.small->block[mul_struct.i];
		compute_mul(&mul_struct, ret);
		mul_struct.i++;
	}
	if (mul_struct.size_max > 0 && ret->block[mul_struct.size_max - 1] == 0)
		ret->length = mul_struct.size_max - 1;
	else
		ret->length = mul_struct.size_max;
}

void		bigint_mul10(t_bigint *ret)
{
	size_t	i;
	t_u128	carry;
	t_u128	sum;

	i = 0;
	carry = 0;
	while (i < ret->length)
	{
		sum = (t_u128)ret->block[i] * (t_u128)10 + carry;
		carry = sum >> 64;
		ret->block[i] = sum & 0xFFFFFFFFFFFFFFFF;
		i++;
	}
	if (carry != 0)
	{
		ret->block[i] = carry;
		ret->length++;
	}
}

void		bigint_mul2(t_bigint *ret)
{
	size_t	i;
	t_u64	carry;
	t_u64	sum;

	i = 0;
	carry = 0;
	while (i < ret->length)
	{
		sum = ret->block[i];
		ret->block[i] = (sum << 1) | carry;
		carry = sum >> 63;
		i++;
	}
	if (carry != 0)
	{
		ret->block[i] = carry;
		ret->length++;
	}
}
