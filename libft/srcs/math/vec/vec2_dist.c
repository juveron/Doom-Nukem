/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:59:31 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/14 11:26:59 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	vec2i_dist(t_vec2i vec1, t_vec2i vec2)
{
	return (vec2i_length(vec2i(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2f_dist(t_vec2f vec1, t_vec2f vec2)
{
	return (vec2f_length(vec2f(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2d_dist(t_vec2d vec1, t_vec2d vec2)
{
	return (vec2d_length(vec2d(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2ui_dist(t_vec2ui vec1, t_vec2ui vec2)
{
	return (vec2ui_length(vec2ui(vec2.x - vec1.x, vec2.y - vec1.y)));
}
