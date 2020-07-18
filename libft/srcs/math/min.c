/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:19:48 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/04 16:49:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	minl(long a, long b)
{
	return (a < b ? a : b);
}

int		mini(int a, int b)
{
	return (a < b ? a : b);
}

float	minf(float a, float b)
{
	return (a < b ? a : b);
}
