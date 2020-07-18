/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:55:56 by kguibout          #+#    #+#             */
/*   Updated: 2019/04/04 16:44:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

int		bigint_cmp(t_bigint *a, t_bigint *b)
{
	long	i;

	if (a->length != b->length)
		return ((int)a->length - (int)b->length);
	i = a->length - 1;
	while (i + 1 > 0)
	{
		if (a->block[i] > b->block[i])
			return (1);
		else if (a->block[i] < b->block[i])
			return (-1);
		else if (a->block[i] == b->block[i])
			i--;
	}
	return (0);
}
