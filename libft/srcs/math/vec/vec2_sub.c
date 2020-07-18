/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:55:26 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/12 16:02:01 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec2i		vec2i_sub(t_vec2i vec1, t_vec2i vec2)
{
	return ((t_vec2i){vec1.x - vec2.x, vec1.y - vec2.y});
}

t_vec2f		vec2f_sub(t_vec2f vec1, t_vec2f vec2)
{
	return ((t_vec2f){vec1.x - vec2.x, vec1.y - vec2.y});
}

t_vec2d		vec2d_sub(t_vec2d vec1, t_vec2d vec2)
{
	return ((t_vec2d){vec1.x - vec2.x, vec1.y - vec2.y});
}

t_vec2ui	vec2ui_sub(t_vec2ui vec1, t_vec2ui vec2)
{
	return ((t_vec2ui){vec1.x - vec2.x, vec1.y - vec2.y});
}
