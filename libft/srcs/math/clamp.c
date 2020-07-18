/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:49:46 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/04 17:00:06 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

long	clampl(long a, long min, long max)
{
	return (minl(maxl(a, min), max));
}

int		clampi(int a, int min, int max)
{
	return (mini(maxi(a, min), max));
}

float	clampf(float a, float min, float max)
{
	return (minf(maxf(a, min), max));
}
