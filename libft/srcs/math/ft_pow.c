/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 08:58:21 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:15:21 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_bitsize.h"

long	ft_pow(long nb, size_t e)
{
	double	res;

	res = 1;
	while (e--)
		res *= nb;
	return (res);
}
