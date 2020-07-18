/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:59:25 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/02 13:09:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void	bigint_new(t_bigint *bigint, size_t size, t_u64 default_value)
{
	size_t		i;

	i = 0;
	bigint->length = size;
	if (default_value)
		bigint->block[i++] = default_value;
	while (i < size)
		bigint->block[i++] = 0;
}
