/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:53:54 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/19 15:39:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec2i		vec2i_normal(t_vec2i vec1)
{
	return ((t_vec2i){-vec1.y, vec1.x});
}

t_vec2f		vec2f_normal(t_vec2f vec1)
{
	return ((t_vec2f){-vec1.y, vec1.x});
}

t_vec2d		vec2d_normal(t_vec2d vec1)
{
	return ((t_vec2d){-vec1.y, vec1.x});
}

t_vec2ui	vec2ui_normal(t_vec2ui vec1)
{
	return ((t_vec2ui){-vec1.y, vec1.x});
}
