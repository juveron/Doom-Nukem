/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:22:51 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:32:44 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	putunbr_base(t_printf *pf, uintmax_t nb, char *base,
	uintmax_t size_base)
{
	if (nb > size_base - 1)
		putunbr_base(pf, nb / size_base, base, size_base);
	put_buffer(pf, base[nb % size_base]);
}
