/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 08:38:00 by kguibout          #+#    #+#             */
/*   Updated: 2019/04/02 09:40:18 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u64	reverse_bits(t_u64 value)
{
	size_t	i;
	t_u64	reverse_value;

	i = 63;
	reverse_value = value;
	value >>= 1;
	while (value)
	{
		reverse_value <<= 1;
		reverse_value |= value & 1;
		value >>= 1;
		i--;
	}
	reverse_value <<= i;
	return (reverse_value);
}
