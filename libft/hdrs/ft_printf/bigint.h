/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 09:00:53 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:28:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# include "libft.h"

# define MAX_BLOCK 260

typedef struct	s_bigint
{
	size_t	length;
	t_u64	block[MAX_BLOCK];
}				t_bigint;

typedef struct	s_mul
{
	size_t		size_max;
	size_t		i;
	size_t		j;
	t_u128		carry;
	t_u128		sum;
	t_u64		mul;
	t_bigint	*small;
	t_bigint	*large;
}				t_mul;

/*
**	bigint_new.c
*/

void			bigint_new(t_bigint *bigint, size_t size, t_u64	default_value);

t_bigint		*pbigint_new(size_t size);

/*
**	bigint_trim.c
*/

void			bigint_trim(t_bigint *bigint);

/*
**	bigint_add.c
*/

void			bigint_add(t_bigint *a, t_bigint *b, t_bigint *ret);

/*
**	bigint_bsl.c
*/

void			bigint_bsl(t_bigint *bigint, int bits, t_bigint *ret);

/*
**	bigint_mul.c
*/

void			bigint_mul(t_bigint *a, t_bigint *b, t_bigint *ret);
void			bigint_mul10(t_bigint *ret);
void			bigint_mul2(t_bigint *ret);

/*
**	bigint_cmp.c
*/

int				bigint_cmp(t_bigint *a, t_bigint *b);

/*
**	bigint_and.c
*/

void			bigint_and(t_bigint *a, t_bigint *b, t_bigint *ret);

/*
**	bigint_xor.c
*/

void			bigint_xor(t_bigint *a, t_bigint *b, t_bigint *ret);

/*
**	bigint_pow.c
*/

void			bigint_pow10(t_u32 pow, t_bigint *ret);

/*
**	bigint_not.c
*/

t_bigint		*bigint_not(t_bigint *bigint, t_bigint *ret);

/*
**	bigint_sub.c
*/

void			bigint_sub(t_bigint *a, t_bigint *b, t_bigint *ret);

/*
**	bigint_divmod.c
*/

void			bigint_divmod(t_bigint *dividend, t_bigint *divisor,
	t_bigint *div, t_bigint *mod);
t_u64			bigint_div(t_bigint *dividend, t_bigint *divisor);

/*
**	bigint_log10.c
*/

t_u32			bigint_log10(t_bigint *bigint);

/*
**	bigint_print.c
*/

void			bigint_print(t_bigint *bigint);

/*
**	bigint_log2.c
*/

t_u32			bigint_log2(t_bigint *bigint);

/*
**	bigint_pow2.c
*/

void			bigint_pow2(t_u32 pow, t_bigint *ret);

/*
**	bigint_cmp_long.c
*/

int				bigint_cmp_long(t_bigint *a, t_u64 b);

#endif
