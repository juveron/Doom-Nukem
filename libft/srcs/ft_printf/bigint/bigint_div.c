/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:41:37 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 13:08:03 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"
#include "ft_printf.h"

static void	divide_quotient(t_u64 quotient, t_bigint *dividend,
	t_bigint *divisor)
{
	size_t	i;
	t_u128	borrow;
	t_u128	carry;
	t_u128	product;
	t_u128	diff;

	borrow = 0;
	carry = 0;
	i = 0;
	while (i < divisor->length)
	{
		product = (t_u128)divisor->block[i] * (t_u128)quotient + carry;
		carry = product >> 64;
		diff = (t_u128)dividend->block[i] - (product & 0xFFFFFFFFFFFFFFFF)
			- borrow;
		borrow = (diff >> 64) & 1;
		dividend->block[i] = diff & 0xFFFFFFFFFFFFFFFF;
		i++;
	}
}

static void	sub(t_bigint *dividend, t_bigint *divisor)
{
	t_u128	borrow;
	t_u128	diff;
	size_t	i;

	i = 0;
	borrow = 0;
	while (i < divisor->length)
	{
		diff = (t_u128)dividend->block[i] - (t_u128)divisor->block[i] - borrow;
		borrow = (diff >> 64) & 1;
		dividend->block[i] = diff & 0xFFFFFFFFFFFFFFFF;
		i++;
	}
}

t_u64		bigint_div(t_bigint *dividend, t_bigint *divisor)
{
	t_u64	quotient;
	size_t	length;

	length = divisor->length;
	if (dividend->length < divisor->length)
		return (0);
	quotient = dividend->block[length - 1] / (divisor->block[length - 1] + 1);
	if (quotient != 0)
	{
		divide_quotient(quotient, dividend, divisor);
		while (length > 0 && dividend->block[length - 1] == 0)
			--length;
		dividend->length = length;
	}
	if (bigint_cmp(dividend, divisor) >= 0)
	{
		++quotient;
		sub(dividend, divisor);
		while (length > 0 && dividend->block[length - 1] == 0)
			--length;
		dividend->length = length;
	}
	return (quotient);
}
