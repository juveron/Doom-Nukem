/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:01:17 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/12 16:59:03 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2i		vec2i_mul(t_vec2i vec1, int mul)
{
	return ((t_vec2i){vec1.x * mul, vec1.y * mul});
}

t_vec2ui	vec2ui_mul(t_vec2ui vec1, t_u32 mul)
{
	return ((t_vec2ui){vec1.x * mul, vec1.y * mul});
}

t_vec2f		vec2f_mul(t_vec2f vec1, float mul)
{
	return ((t_vec2f){vec1.x * mul, vec1.y * mul});
}

t_vec2d		vec2d_mul(t_vec2d vec1, double mul)
{
	return ((t_vec2d){vec1.x * mul, vec1.y * mul});
}
