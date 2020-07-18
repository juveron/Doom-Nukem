/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dist_sq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:45:05 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/14 12:48:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	vec2i_dist_sq(t_vec2i vec1, t_vec2i vec2)
{
	return (vec2i_length_sq(vec2i(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2f_dist_sq(t_vec2f vec1, t_vec2f vec2)
{
	return (vec2f_length_sq(vec2f(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2d_dist_sq(t_vec2d vec1, t_vec2d vec2)
{
	return (vec2d_length_sq(vec2d(vec2.x - vec1.x, vec2.y - vec1.y)));
}

float	vec2ui_dist_sq(t_vec2ui vec1, t_vec2ui vec2)
{
	return (vec2ui_length_sq(vec2ui(vec2.x - vec1.x, vec2.y - vec1.y)));
}
