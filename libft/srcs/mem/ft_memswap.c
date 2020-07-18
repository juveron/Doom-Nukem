/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:33:38 by kguibout          #+#    #+#             */
/*   Updated: 2019/07/31 18:34:01 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memswap(void *a, void *b, size_t n)
{
	t_u8	*a_tmp;
	t_u8	*b_tmp;
	t_u8	*end;
	t_u8	tmp;

	a_tmp = a;
	b_tmp = b;
	end = (t_u8 *)a + n;
	while (a_tmp < end)
	{
		tmp = *a_tmp;
		*a_tmp = *b_tmp;
		*b_tmp = tmp;
		++a_tmp;
		++b_tmp;
	}
}
