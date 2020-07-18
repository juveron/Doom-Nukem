/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_unbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:54:40 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/11 13:56:20 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <inttypes.h>

size_t	length_unbr_base(uintmax_t nb, size_t length_base)
{
	size_t	size;

	size = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= length_base;
		size++;
	}
	return (size);
}
