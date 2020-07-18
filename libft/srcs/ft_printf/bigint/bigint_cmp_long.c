/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_cmp_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:29:55 by kguibout          #+#    #+#             */
/*   Updated: 2019/04/05 20:23:24 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

int		bigint_cmp_long(t_bigint *a, t_u64 b)
{
	if (a->length > 1)
		return ((int)a->length);
	if (a->block[0] > b)
		return (1);
	else if (a->block[0] < b)
		return (-1);
	else
		return (0);
}
