/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:39:27 by thboura           #+#    #+#             */
/*   Updated: 2019/04/10 14:43:00 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

void	putnbr_buffer(t_printf *pf, int n)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = (unsigned int)-n;
		put_buffer(pf, '-');
	}
	else
		nb = (unsigned int)n;
	if (nb > 9)
		putnbr_buffer(pf, nb / 10);
	put_buffer(pf, nb % 10 + 48);
}
